// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

#include "zprpc/include/rpc_channel.h"

#include <zest/net/tcp_client.h>
#include <zest/base/logging.h>

#include "zprpc/include/rpc_controller.h"
#include "zprpc/pb/rpc_protocol.pb.h"


namespace zprpc
{

void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                            google::protobuf::RpcController* controller,
                            const google::protobuf::Message* request,
                            google::protobuf::Message* response,
                            google::protobuf::Closure* done)
{
  zprpc::RpcController *zprpc_controller = 
      reinterpret_cast<zprpc::RpcController*>(controller);

  // 获取服务名和方法名
  auto service_desc = method->service();
  std::string service_name = service_desc->name();
  std::string method_name = method->name();

  // 序列化请求
  std::string args_str;
  if (request->SerializeToString(&args_str) == false) {
    zprpc_controller->SetFailed("serialize request body failed");
    return;
  }

  // 填充请求头
  RequestHeader req_header_pb;
  req_header_pb.set_service_name(service_name);
  req_header_pb.set_method_name(method_name);
  req_header_pb.set_args_size(args_str.size());

  // 序列化请求头
  std::string req_header_str;
  if (req_header_pb.SerializeToString(&req_header_str) == false) {
    zprpc_controller->SetFailed("serialize request header failed");
    return;
  }

  // 组织待发送的字符串
  uint32_t header_size = req_header_str.size();
  std::string send_buf((char*)&header_size, 4);
  send_buf += req_header_str;
  send_buf += args_str;

  // TODO: 服务提供者的地址怎么确定？
  zest::net::InetAddress server_addr("127.0.0.1", 12345);
  zest::net::TcpClient client(server_addr);

  // 连接建立后立刻发送RPC请求
  client.setOnConnectionCallback(
    [&send_buf](zest::net::TcpConnection &conn){
      conn.send(send_buf);
    }
  );
  // 发送完数据后等待服务器响应
  client.connection().setWriteCompleteCallback(
    [](zest::net::TcpConnection &conn){
      conn.waitForMessage();
      LOG_DEBUG << "wait for message";
    }
  );
  // 解析读取到的数据
  client.connection().setMessageCallback(
    [&client, this, response, zprpc_controller](zest::net::TcpConnection &conn){
      this->parseResponse(conn, response, zprpc_controller);
      if (zprpc_controller->Failed()) {
        client.stop();
        return;
      }
      if (zprpc_controller->IsFinished()) {
        client.stop();
        return;
      }
    }
  );
  // 一旦服务器断开连接则终止客户端
  client.connection().setCloseCallback(
    [&client](zest::net::TcpConnection &conn){
      client.stop();
      LOG_DEBUG << "disconnect with server";
    }
  );
  // 添加超时定时器
  client.addTimer(
    1000,
    [&client, zprpc_controller](){
      client.stop();
      zprpc_controller->SetFailed("RPC time out");
      LOG_ERROR << "RPC time out";
    }
  );

  // 启动RPC客户端，等待请求响应完成或者失败
  client.start();

  if (done) done->Run();
}

void RpcChannel::parseResponse(zest::net::TcpConnection &conn,
                               google::protobuf::Message *response,
                               zprpc::RpcController *controller)
{
  if (conn.dataSize() < 4)
    return;
  std::string recv_data = conn.data();
  LOG_DEBUG << "recv " << recv_data.size() << "bytes date from server";

  // 计算 RpcHeader 的长度
  uint32_t header_size;
  memcpy(&header_size, recv_data.c_str(), 4);
  if (recv_data.size() < 4 + header_size)
    return;

  // 解析RPC响应头
  std::string rsp_header_pb_str = recv_data.substr(4, header_size);
  ResponseHeader rsp_header_pb;
  if (rsp_header_pb.ParseFromString(rsp_header_pb_str) == false) {
    LOG_ERROR << "RPC header deserialize error";
    controller->SetFailed("parse response header failed");
    return;
  }
  // 状态码非0表示出错
  if (rsp_header_pb.status_code() != 0) {
    LOG_ERROR << "RPC request failed, error_info: " << rsp_header_pb.error_info();
    controller->SetFailed(rsp_header_pb.error_info());
    return;
  }
  uint32_t args_size = rsp_header_pb.args_size();
  // 判断RPC响应数据是否全部到达
  if (recv_data.size() < 4 + header_size + args_size)
    return;
  conn.clearData();

  // 解析RPC响应
  if (response->ParseFromString(recv_data.substr(4+header_size, args_size)) == false) {
    LOG_ERROR << "RPC response deserialize error";
    controller->SetFailed("parse response body failed");
    return;
  }
  controller->SetFinished();
}

} // namespace zprpc

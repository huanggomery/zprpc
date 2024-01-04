// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

#include "zprpc/include/rpc_channel.h"

#include <zest/net/tcp_client.h>

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
  client.setTimer(1000);

  // 连接建立后立刻发送RPC请求
  if (client.connect() == false) {
    LOG_ERROR << "connect failed";
    zprpc_controller->SetFailed("client connect failed");
    return;
  }
  if (client.send(send_buf) == false) {
    LOG_ERROR << "send failed";
    zprpc_controller->SetFailed("client send failed");
    return;
  }

  std::string recv_data;   // 存储所有收到的数据
  while (1) {
    std::string str;
    if (client.recv(str) == false) {
      zprpc_controller->SetFailed("client recv failed");
      client.disconnect();
      return;
    }
    recv_data += str;
    // 解析读到的所有数据
    if (parseResponse(recv_data, response, zprpc_controller)) {
      LOG_DEBUG << "rpc finished!";
      client.disconnect();
      return;
    }
    else {
      if (zprpc_controller->Failed()) {
        LOG_DEBUG << "parse failed";
        client.disconnect();
        return;
      }
      else {
        /* wait for more data */
      }
    }
  }
}

bool RpcChannel::parseResponse(const std::string &recv_data,
                               google::protobuf::Message *response,
                               zprpc::RpcController *controller)
{
  if (recv_data.size() < 4)
    return false;

  // 计算 RpcHeader 的长度
  uint32_t header_size;
  memcpy(&header_size, recv_data.c_str(), 4);
  if (recv_data.size() < 4 + header_size)
    return false;

  // 解析RPC响应头
  std::string rsp_header_pb_str = recv_data.substr(4, header_size);
  ResponseHeader rsp_header_pb;
  if (rsp_header_pb.ParseFromString(rsp_header_pb_str) == false) {
    LOG_ERROR << "RPC header deserialize error";
    controller->SetFailed("parse response header failed");
    return false;
  }
  // 状态码非0表示出错
  if (rsp_header_pb.status_code() != 0) {
    LOG_ERROR << "RPC request failed, error_info: " << rsp_header_pb.error_info();
    controller->SetFailed(rsp_header_pb.error_info());
    return false;
  }
  uint32_t args_size = rsp_header_pb.args_size();
  // 判断RPC响应数据是否全部到达
  if (recv_data.size() < 4 + header_size + args_size)
    return false;

  // 解析RPC响应
  if (response->ParseFromString(recv_data.substr(4+header_size, args_size)) == false) {
    LOG_ERROR << "RPC response deserialize error";
    controller->SetFailed("parse response body failed");
    return false;
  }
  controller->SetFinished();
  return true;
}

} // namespace zprpc

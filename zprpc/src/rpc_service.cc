// 提供RPC服务

// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

#include "zprpc/include/rpc_service.h"

#include <string.h>

#include <functional>
#include <memory>

#include <google/protobuf/message.h>
#include <zest/net/inet_addr.h>
#include <zest/net/tcp_server.h>

#include "zprpc/include/rpc_closure.h"
#include "zprpc/include/rpc_config.h"
#include "zprpc/pb/rpc_protocol.pb.h"

using std::placeholders::_1;


namespace zprpc
{

extern RpcConfig *kRpcConfig;

void RpcService::Register(google::protobuf::Service* service)
{
  if (!service)
    return;
  std::string service_name = service->GetDescriptor()->name();
  if (service_map_.find(service_name) != service_map_.end())
    return;
  service_map_.insert({service_name, service});
  LOG_INFO << "register service: [" << service_name << "] successfully";
}

void RpcService::Run()
{
  if (!kRpcConfig) {
    std::cerr << "The RPC service hasn't been initialized yet. Please call:" << std::endl;
    std::cerr << "RpcConfig::Init()" << std::endl;
    return;
  }

  // 创建TcpServer
  std::string server_ip = RpcConfig::Get("ip");
  std::string server_port = RpcConfig::Get("port");
  std::string thread_num = RpcConfig::Get("thread_num");
  if (server_ip.empty() || server_port.empty()) {
    LOG_FATAL << "The configuration file lacks the IP and port information. The server startup has failed.";
    return;
  }
  int thread_num_ = thread_num.empty() ? 4 : std::stoi(thread_num);

  zest::net::InetAddress server_addr(server_ip, std::stoi(server_port));
  zest::net::TcpServer server(server_addr, thread_num_);

  // 绑定回调函数
  server.setOnConnectionCallback(std::bind(&RpcService::onConnection, this, _1));
  server.setMessageCallback(std::bind(&RpcService::onMessage, this, _1));
  server.setWriteCompleteCallback(std::bind(&RpcService::writeComplete, this, _1));

  // 启动TCP服务器
  LOG_INFO << "Start RPC service at " << server_addr.to_string();
  server.start();
}

void RpcService::onConnection(zest::net::TcpConnection &conn)
{
  conn.waitForMessage();
}

void RpcService::onMessage(zest::net::TcpConnection &conn)
{
  if (conn.dataSize() < 4)
    return;
  std::string recv_data = conn.data();

  // 计算 RpcHeader 的长度
  uint32_t header_size;
  memcpy(&header_size, recv_data.c_str(), 4);
  if (recv_data.size() < 4 + header_size)
    return;

  auto done = std::make_shared<RpcClosure>(conn);
  auto rsp_header = std::make_shared<ResponseHeader>();
  rsp_header->set_status_code(RPC_OK);
  rsp_header->mutable_error_info()->clear();
  rsp_header->set_args_size(0);
  done->setResponseHeader(rsp_header.get());

  // 解析 RpcHeader
  std::string req_header_pb_str = recv_data.substr(4, header_size);
  RequestHeader req_header_pb;
  if (req_header_pb.ParseFromString(req_header_pb_str) == false) {
    LOG_ERROR << "RPC header deserialize error";
    rsp_header->set_status_code(RPC_DESERIALIZE_FAILED);
    rsp_header->set_error_info("parse header error");
    rsp_header->mutable_error_info()->clear();
    done->Run();
    return;
  }
  std::string service_name = req_header_pb.service_name();
  std::string method_name = req_header_pb.method_name();
  uint32_t args_size = req_header_pb.args_size();
  // 打印调试信息
  // std::cout << "============================================" << std::endl;
  // std::cout << "header_size: " << header_size << std::endl; 
  // std::cout << "service_name: " << service_name << std::endl; 
  // std::cout << "method_name: " << method_name << std::endl; 
  // std::cout << "args_size: " << args_size << std::endl; 
  // std::cout << "============================================" << std::endl;
  if (recv_data.size() < 4 + header_size + args_size)
    return;
  conn.clearData();
  done->setServiceName(service_name);
  done->setMethodName(method_name);

  // 根据服务名，从注册的服务中获取服务
  auto it = service_map_.find(service_name);
  if (it == service_map_.end()) {
    LOG_ERROR << "service name [" << service_name << "] not found";
    rsp_header->set_status_code(RPC_SERVICE_NOT_FOUND);
    rsp_header->set_error_info("service not found");
    rsp_header->mutable_error_info()->clear();
    done->Run();
    return;
  }
  google::protobuf::Service *service = it->second;
  
  // 根据方法名，从服务中获取方法
  auto method_desc = service->GetDescriptor()->FindMethodByName(method_name);
  if (method_desc == nullptr) {
    LOG_ERROR << "method name [" << method_name << "] is not found in service [" << service_name << "]";
    rsp_header->set_status_code(RPC_SERVICE_NOT_FOUND);
    rsp_header->set_error_info("method not found");
    rsp_header->mutable_error_info()->clear();
    done->Run();
    return;
  }
  LOG_DEBUG << "get request for " << service_name << ":" << method_name << " from " << conn.peerAddress().to_string();

  // 构造出方法的请求对象，即函数的输入参数
  std::shared_ptr<google::protobuf::Message> req_msg(service->GetRequestPrototype(method_desc).New());
  if (req_msg->ParseFromString(recv_data.substr(4+header_size, args_size)) == false) {
    LOG_ERROR << service_name << " : " << method_name << " RPC request deserialize error";
    rsp_header->set_status_code(RPC_DESERIALIZE_FAILED);
    rsp_header->set_error_info("parse request message error");
    rsp_header->mutable_error_info()->clear();
    done->Run();
    return;
  }
  
  // 构造出方法的响应对象，即函数的输出
  std::shared_ptr<google::protobuf::Message> rsp_msg(service->GetResponsePrototype(method_desc).New());
  done->setResponseMessage(rsp_msg.get());

  // ------------------ 真正的RPC调用 ---------------------- 
  service->CallMethod(method_desc, nullptr, req_msg.get(), rsp_msg.get(), done.get());
}



void RpcService::writeComplete(zest::net::TcpConnection &conn)
{
  // TODO: 目前仅支持短连接，后续可以考虑支持长短连接
  conn.shutdown();
}
  
} // namespace zprpc

// 提供RPC服务

// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

// This is a public header file, it must only include public header files.

#ifndef ZPRPC_INCLUDE_RPC_SERVICE_H
#define ZPRPC_INCLUDE_RPC_SERVICE_H

#include <string>
#include <unordered_map>

#include <google/protobuf/service.h>
#include <zest/base/logging.h>
#include <zest/base/noncopyable.h>
#include <zest/net/tcp_connection.h>

#include "zprpc/include/rpc_config.h"


namespace zprpc
{

// RPC状态码
const int32_t RPC_OK = 0;
const int32_t RPC_SERIALIZE_FAILED = 1;
const int32_t RPC_DESERIALIZE_FAILED = 2;
const int32_t RPC_SERVICE_NOT_FOUND = 3;
const int32_t RPC_METHOD_NOT_FOUND = 3;

class RpcService: public zest::noncopyable
{
 public:
  RpcService() = default;
  ~RpcService() = default;

  // 注册RPC服务
  void Register(google::protobuf::Service* service);

  // 启动RPC服务节点
  void Run();

 private:
  void onConnection(zest::net::TcpConnection &conn);
  void onMessage(zest::net::TcpConnection &conn);
  void writeComplete(zest::net::TcpConnection &conn);
  
 private:
  std::unordered_map<std::string, google::protobuf::Service*> service_map_;
};
  
} // namespace zprpc

#endif // ZPRPC_INCLUDE_RPC_SERVICE_H

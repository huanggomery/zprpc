// CallMethod的回调

// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

// This is an internal header file, you should not include this.

#ifndef ZPRPC_INCLUDE_RPC_CLOSURE_H
#define ZPRPC_INCLUDE_RPC_CLOSURE_H

#include <google/protobuf/message.h>
#include <zest/net/tcp_connection.h>

namespace zprpc
{

class ResponseHeader;
  
class RpcClosure: public google::protobuf::Closure
{
 public:
  RpcClosure() = delete;
  RpcClosure(zest::net::TcpConnection &conn);
  ~RpcClosure() = default;
  void Run() override;


  void setServiceName(const std::string &name)
  { service_name_ = name; }

  void setMethodName(const std::string &name)
  { method_name_ = name; }

  void setResponseHeader(ResponseHeader *rsp_header)
  { rsp_header_ = rsp_header; }

  void setResponseMessage(google::protobuf::Message *rsp_message)
  { rsp_message_ = rsp_message; }

 private:
  void handleError();

 private:
  zest::net::TcpConnection &conn_;
  std::string service_name_;
  std::string method_name_;
  ResponseHeader *rsp_header_ = nullptr;
  google::protobuf::Message *rsp_message_ = nullptr;
};

} // namespace zprpc

#endif // ZPRPC_INCLUDE_RPC_CLOSURE_H

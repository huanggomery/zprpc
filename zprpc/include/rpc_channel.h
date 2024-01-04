// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

// This is a public header file, it must only include public header files.

#ifndef ZPRPC_INCLUDE_RPC_CHANNEL_H
#define ZPRPC_INCLUDE_RPC_CHANNEL_H

#include <google/protobuf/message.h>
#include <google/protobuf/service.h>
#include <zest/base/logging.h>
#include <zest/net/tcp_connection.h>

namespace zprpc
{

class RpcController;
  
class RpcChannel: public google::protobuf::RpcChannel
{
 public:
  // 通过stub对象调用RPC函数，都会用到这个函数
  // RPC请求序列化，网络发送和接收
  void CallMethod(const google::protobuf::MethodDescriptor* method,
                  google::protobuf::RpcController* controller,
                  const google::protobuf::Message* request,
                  google::protobuf::Message* response,
                  google::protobuf::Closure* done) override;

 private:
  bool parseResponse(const std::string &recv_data,
                     google::protobuf::Message *response,
                     zprpc::RpcController *controller);
};

} // namespace zprpc

#endif // ZPRPC_INCLUDE_RPC_CHANNEL_H

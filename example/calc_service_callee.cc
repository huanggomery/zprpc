#include <iostream>
#include <stdlib.h>
#include "example/pb/calculate.pb.h"
#include "zprpc/include/rpc_service.h"


class CalcRequestImpl: public zprpc::CalcService
{
 public:
  void Add(google::protobuf::RpcController* controller,
           const ::zprpc::CalcRequest* request,
           ::zprpc::CalcResponse* response,
           ::google::protobuf::Closure* done) override
  {
    LOG_DEBUG << "add: " << request->num1() << " + " << request->num2();
    response->set_result(request->num1() + request->num2());
    if (done)
      done->Run();
  }

  void Multiply(google::protobuf::RpcController* controller,
                const ::zprpc::CalcRequest* request,
                ::zprpc::CalcResponse* response,
                ::google::protobuf::Closure* done) override
  {
    LOG_DEBUG << "multiply: " << request->num1() << " * " << request->num2();
    response->set_result(request->num1() * request->num2());
    if (done)
      done->Run();
  }                
};


int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Please input config file" << std::endl;
    exit(-1);
  }

  // 用文件初始化RPC框架
  zprpc::RpcConfig::Init(argv[1]);
  // 创建一个RPC服务提供者
  zprpc::RpcService rpc_service;
  // 注册一个RPC服务
  rpc_service.Register(new CalcRequestImpl());
  // 启动RPC服务节点
  rpc_service.Run();

  return 0;
}
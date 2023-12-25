#include <iostream>
#include <stdlib.h>
#include "example/pb/calculate.pb.h"
#include "zprpc/include/rpc_channel.h"
#include "zprpc/include/rpc_config.h"
#include "zprpc/include/rpc_controller.h"


int main()
{
  zprpc::RpcConfig::Init("../example/rpc_client.cfg");
  zprpc::CalcService_Stub calc_stub(new zprpc::RpcChannel());
  zprpc::CalcRequest req_pb;
  zprpc::CalcResponse rsp_pb;
  zprpc::RpcController controller;

  for (int i = 0; i < 100; ++i) {
    int n1 = rand() % 100, n2 = rand() % 100;
    req_pb.set_num1(n1);
    req_pb.set_num2(n2);
    int choic = rand() % 2;
    if (choic == 0) {
      // 用加法
      calc_stub.Add(&controller, &req_pb, &rsp_pb, nullptr);
      if (controller.Failed()) {
        std::cerr << "RPC failed, error info: " << controller.ErrorText() << std::endl;
        exit(-1);
      }
      if (n1 + n2 != rsp_pb.result()) {
        std::cerr << n1 << " + " << n2 << " != " << rsp_pb.result() << std::endl;
        exit(-1);
      }
    }
    else {
      // 用乘法
      calc_stub.Multiply(&controller, &req_pb, &rsp_pb, nullptr);
      if (controller.Failed()) {
        std::cerr << "RPC failed, error info: " << controller.ErrorText() << std::endl;
        exit(-1);
      }
      if (n1 * n2 != rsp_pb.result()) {
        std::cerr << n1 << " * " << n2 << " != " << rsp_pb.result() << std::endl;
        exit(-1);
      }
    }
  }
}
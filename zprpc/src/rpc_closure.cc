// CallMethod的回调

// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

#include "zprpc/include/rpc_closure.h"
#include <string.h>
#include <zest/base/logging.h>
#include "zprpc/pb/rpc_protocol.pb.h"
#include "zprpc/include/rpc_service.h"

namespace zprpc
{

RpcClosure::RpcClosure(zest::net::TcpConnection &conn): conn_(conn)
{
  /* do nothing */
}

void RpcClosure::Run()
{
  if (rsp_header_->status_code() != 0) {
    handleError();
    return;
  }

  std::string rsp_str;
  if (rsp_message_->SerializeToString(&rsp_str) == false) {
    LOG_ERROR << service_name_ << " : " << method_name_ << " serialize response_str failed";
    rsp_header_->set_status_code(RPC_SERIALIZE_FAILED);
    rsp_header_->set_error_info("SerializeToString failed");
    rsp_header_->set_args_size(0);
    handleError();
    return;
  }

  uint32_t rsp_size = rsp_str.size();
  rsp_header_->set_args_size(rsp_size);
  rsp_header_->set_status_code(RPC_OK);
  rsp_header_->mutable_error_info()->clear();

  std::string rsp_header_str;
  rsp_header_->SerializeToString(&rsp_header_str);
  uint32_t header_size = rsp_header_str.size();
  std::string send_buf((char*)&header_size, 4);
  send_buf += rsp_header_str;
  send_buf += rsp_str;

  conn_.send(send_buf);
  LOG_DEBUG << "send " << send_buf.size() << " bytes message to caller";
}

void RpcClosure::handleError()
{
  std::string rsp_header_str;
  rsp_header_->SerializeToString(&rsp_header_str);
  uint32_t header_size = rsp_header_str.size();
  std::string send_buf((char*)&header_size, 4);
  send_buf += rsp_header_str;
  conn_.send(send_buf);
}

} // namespace zprpc

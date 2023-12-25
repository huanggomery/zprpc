// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

#include "zprpc/include/rpc_controller.h"


namespace zprpc
{
  
void RpcController::Reset()
{
  failed_ = false;
  canceled_ = false;
  finished_ = false;
  error_text_.clear();
}

bool RpcController::Failed() const
{
  return failed_;
}

std::string RpcController::ErrorText() const
{
  return error_text_;
}

void RpcController::StartCancel()
{

}

void RpcController::SetFailed(const std::string& reason)
{
  failed_ = true;
  error_text_ = reason;
}

bool RpcController::IsCanceled() const
{
  return canceled_;
}

void RpcController::NotifyOnCancel(google::protobuf::Closure* callback)
{

}

void RpcController::SetFinished()
{
  finished_ = true;
}

bool RpcController::IsFinished() const
{
  return finished_;
}
  
} // namespace zprpc

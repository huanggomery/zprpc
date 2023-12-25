// RPC服务配置

// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

// This is a public header file, it must only include public header files.

#ifndef ZPRPC_INCLUDE_RPC_CONFIG_H
#define ZPRPC_INCLUDE_RPC_CONFIG_H

#include <string>
#include <unordered_map>

#include <zest/base/noncopyable.h>


namespace zprpc
{

class RpcConfig
{
 public:
  RpcConfig() = default;
  ~RpcConfig() = default;
  
  static void Init(const std::string &config_file);
  static std::string Get(const std::string &key);
  
 private:
  // 去除字符串首尾的空格
  static void trim(std::string &str);

 private:
  std::unordered_map<std::string, std::string> config_map_;
};

} // namespace zprpc

#endif // ZPRPC_INCLUDE_RPC_CONFIG_H

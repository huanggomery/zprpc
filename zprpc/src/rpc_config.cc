// RPC服务配置

// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

#include "zprpc/include/rpc_config.h"

#include <stdlib.h>

#include <fstream>
#include <iostream>

#include <zest/base/logging.h>

namespace zprpc
{

RpcConfig *kRpcConfig = nullptr;

void RpcConfig::Init(const std::string &config_file)
{
  if (kRpcConfig)
    return;

  kRpcConfig = new RpcConfig();
  std::ifstream ifs(config_file);

  // 检查文件是否打开
  if (!ifs.is_open()) {
    std::cerr << "Can't open file " << config_file << std::endl;
    exit(-1);
  }

  std::string line;
  // 一行一行读取
  while (std::getline(ifs, line)) {
    trim(line);

    // 检查是否是注释或者空行
    if (line[0] == '#' || line.empty())
      continue;
    
    // 解析配置项
    int idx = line.find('=');
    if (idx == std::string::npos)  // 配置项不合法
      continue;
    std::string key = line.substr(0, idx);
    std::string value = line.substr(idx+1, line.size()-idx-1);
    trim(key);
    trim(value);
    kRpcConfig->config_map_.insert({key, value});
  }
  ifs.close();

  // 初始化日志系统
  std::string log_level = RpcConfig::Get("log_level");
  std::string log_file_name = RpcConfig::Get("log_file_name");
  std::string log_file_path = RpcConfig::Get("log_file_path");
  std::string max_log_size = RpcConfig::Get("max_log_size");
  std::string log_sync_interval = RpcConfig::Get("log_sync_interval");

  log_level = log_level.empty() ? "INFO" : log_level;
  log_file_name = log_file_name.empty() ? "rpc_service" : log_file_name;
  log_file_path = log_file_path.empty() ? "../logs/" : log_file_path;
  int max_log_size_ = max_log_size.empty() ? 500000 : std::stoi(max_log_size);
  int log_sync_interval_ = log_sync_interval.empty() ? 1000 : std::stoi(log_sync_interval);

  zest::Logger::InitGlobalLogger(log_level,
                                 log_file_name,
                                 log_file_path,
                                 max_log_size_,
                                 log_sync_interval_);
}

std::string RpcConfig::Get(const std::string &key)
{
  if (!kRpcConfig) {
    std::cerr << "The RPC service hasn't been initialized yet. Please call:" << std::endl;
    std::cerr << "RpcConfig::Init()" << std::endl;
    exit(-1);
  }
  auto it = kRpcConfig->config_map_.find(key);
  if (it == kRpcConfig->config_map_.end())
    return std::string();
  return it->second;
}

void RpcConfig::trim(std::string &str)
{
  // 去除前空格
  int low = str.find_first_not_of(' ');
  if (low != std::string::npos) {
    str = str.substr(low);
  }
  // 去除注释后的内容
  int comment = str.find_first_of('#');
  if (comment != std::string::npos) {
    str = str.substr(0, comment);
  }
  // 去除后空格
  int high = str.find_last_not_of(' ');
  if (high != std::string::npos) {
    str = str.substr(0, high+1);
  }
}
  
} // namespace zprpc

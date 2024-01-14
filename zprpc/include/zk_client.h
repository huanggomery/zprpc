// zookeeper client

// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

// This is an internal header file, you should not include this.

#ifndef ZPRPC_INCLUDE_ZK_CLIENT_H
#define ZPRPC_INCLUDE_ZK_CLIENT_H

#include <string>
#include <zookeeper/zookeeper.h>

namespace zprpc
{

class ZkClient
{
 public:
  ZkClient();
  ~ZkClient();
  void Start();
  void Create(const std::string &path, const std::string &data, int state=0);
  std::string GetData(const std::string &path);

 private:
  zhandle_t *m_zk_handle;
};
  
} // namespace zprpc

#endif // ZPRPC_INCLUDE_ZK_CLIENT_H

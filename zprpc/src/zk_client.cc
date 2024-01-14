// Copyright 2023, Huanggomery. All rights reserved.
// Author: Huanggomery (huanggomery@gmail.com)

#include "zprpc/include/zk_client.h"

#include <semaphore.h>
#include <stdlib.h>

#include <functional>
#include <zest/base/logging.h>

#include "zprpc/include/rpc_config.h"

namespace zprpc
{

void watcherCallback(zhandle_t *zh, int type, int state,
                    const char *path, void *watcherCtx)
{
  if (type == ZOO_SESSION_EVENT && state == ZOO_CONNECTED_STATE) {
    sem_t *sem = nullptr;
    while ((sem = (sem_t*)zoo_get_context(zh)) == nullptr) {}
    sem_post(sem);
  }
}

ZkClient::ZkClient(): m_zk_handle(nullptr)
{
  /* do nothing */
}

ZkClient::~ZkClient()
{
  if (m_zk_handle) {
    zookeeper_close(m_zk_handle);
    m_zk_handle = nullptr;
  }
}

void ZkClient::Start()
{
  /*
	 * zookeeper_mt：多线程版本
	 * zookeeper的API客户端程序提供了三个线程:
	 *   1.API调用线程 
	 *   2.网络I/O线程  pthread_create  poll
	 *   3.watcher回调线程 pthread_create
	 */

  sem_t sem;
  sem_init(&sem, 0, 0);

  zoo_set_debug_level(ZOO_LOG_LEVEL_ERROR);
  std::string zk_ip = RpcConfig::Get("zookeeper_ip");
  std::string zk_port = RpcConfig::Get("zookeeper_port");
  std::string zk_host = zk_ip + ":" + zk_port;
  m_zk_handle = zookeeper_init(
    zk_host.c_str(),
    watcherCallback,
    3000, nullptr, nullptr, 0);

  zoo_set_context(m_zk_handle, &sem);
  sem_wait(&sem);
  sem_destroy(&sem);
}

void ZkClient::Create(const std::string &path, const std::string &data, int state)
{
  if (zoo_exists(m_zk_handle, path.c_str(), 0, nullptr) == ZNONODE) {
    int rt = zoo_create(m_zk_handle, path.c_str(), data.c_str(), data.size(),
                        &ZOO_OPEN_ACL_UNSAFE, state, nullptr, 0);
    if (rt == ZOK) {
      LOG_INFO << "znode create success, path: " << path;
    }
    else {
      LOG_FATAL << "znode create failed, path: " << path;
      exit(-1);
    }
  }
}

std::string ZkClient::GetData(const std::string &path)
{
  char buf[64];
  int buf_len = sizeof(buf);
  int rt = zoo_get(m_zk_handle, path.c_str(), 0, buf, &buf_len, nullptr);
  if (rt != ZOK) {
    LOG_ERROR << "get znode data failed, path: " << path;
    return std::string();
  }
  else {
    return std::string(buf);
  }
}

} // namespace zprpc

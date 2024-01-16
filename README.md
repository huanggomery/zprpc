# zprpc
## 介绍

zprpc是一个轻量的RPC框架，使用google的protobuf作为序列化工具，使用zookeeper注册和获取RPC方法的地址，并使用我自己的zest网络库。

## 环境

+ Linux kernel version 5.15.0-83-generic

## 依赖

+ g++ 9.4.0

  Linux中最常用的C++编译器

+ xmake

  跨平台自动构建工具，如果你还没有安装xmake，请访问 https://xmake.io 查看如何下载安装。

+ protobuf3

  序列化和反序列化工具，也用来定义RPC服务和方法。

+ zookeeper

  开源的分布式应用程序协调服务器。在本项目中用于注册和获取RPC方法对应的服务器IP地址。

+ zest

  我自己的网络库，提供网络服务、线程调度、日志等功能。详见 https://github.com/huanggomery/zest 了解详细的安装和使用方法。

## 构建

首先确保你已经安装了所有的依赖项。

然后，clone本项目，并进入目录

```shell
git clone https://github.com/huanggomery/zprpc.git
cd zprpc
```

接着，运行

```shell
./build.sh
```

你也可以自己指定安装路径（默认是安装到 `/usr/local`）

```shell
./build.sh /your/specify/path/
```

## RPC协议

zprpc使用的RPC请求和响应的数据格式如图所示。其中Header和Args Body都是使用protobuf序列化的数据，接受方通过protobuf反序列化得到原始数据结构。

<img src="./pic/rpc_protocol.png" style="zoom: 67%;" />

## 示例

在 `example` 目录中，提供了一个使用zprpc来实现RPC服务的例子。

### 定义RPC服务和方法

首先，新建一个proto文件，定义RPC方法请求和响应的数据类型，以及RPC服务和方法

```protobuf
// calculate.proto

// RPC方法的请求数据类型
message CalcRequest
{
  double num1 = 1;
  double num2 = 2;
}

// RPC方法的响应数据类型
message CalcResponse
{
  double result = 1;
}

// RPC服务和方法，在CalcService服务中有Add和Multiply两个方法
service CalcService
{
  rpc Add(CalcRequest) returns(CalcResponse);
  rpc Multiply(CalcRequest) returns(CalcResponse);
}
```

然后，用protoc编译生成`calculate.pb.h`和`calculate.pb.cc`两个文件。

### 实现RPC方法的函数

定义一个类，继承自proto文件中定义的服务类（本例中为zprpc::CalcService），实现所有该服务下的方法的函数。

**注意函数返回前必须调用`done->Run()`，该函数用于向客户端发送RPC响应。**

```c++
// #include "calculate.pb.h"

class CalcRequestImpl: public zprpc::CalcService
{
 public:
  void Add(google::protobuf::RpcController* controller,
           const ::zprpc::CalcRequest* request,
           ::zprpc::CalcResponse* response,
           ::google::protobuf::Closure* done) override
  {
    response->set_result(request->num1() + request->num2());
    if (done)
      done->Run();
  }

  void Multiply(google::protobuf::RpcController* controller,
                const ::zprpc::CalcRequest* request,
                ::zprpc::CalcResponse* response,
                ::google::protobuf::Closure* done) override
  {
    response->set_result(request->num1() * request->num2());
    if (done)
      done->Run();
  }                
};
```

### 配置文件

RPC的提供方和调用方都必须有配置文件，配置项如下：

```
# RPC提供方的配置信息

# 日志相关，非必要
log_level = DEBUG
log_file_name = rpc_server
log_file_path = ../logs/
max_log_size = 500000
log_sync_interval = 1000

# 服务器地址
ip = 127.0.0.1
port = 12345
thread_num = 4

# zookeeper地址
zookeeper_ip = 127.0.0.1
zookeeper_port = 2181
```

```
# RPC调用方的配置信息

# 日志相关，非必要
log_level = DEBUG
log_file_name = rpc_client
log_file_path = ../logs/
max_log_size = 500000
log_sync_interval = 1000

# zookeeper地址
zookeeper_ip = 127.0.0.1
zookeeper_port = 2181
```

### 创建RPC提供方

仿照示例代码，即可创建并运行RPC提供方

```c++
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
```

### 调用RPC服务

初始化RPC框架，创建一个RPC服务的Stub，创建请求对象、响应对象和RPC控制器，即可发起RPC请求：

```c++
int main()
{
  // 初始化RPC框架
  zprpc::RpcConfig::Init("../example/rpc_client.cfg");
  // 创建RPC服务的Stub
  zprpc::CalcService_Stub calc_stub(new zprpc::RpcChannel());
  // 创建请求对象、响应对象和RPC控制器
  zprpc::CalcRequest req_pb;
  req_pb.set_num1(10);
  req_pb.set_num2(20);
  zprpc::CalcResponse rsp_pb;
  zprpc::RpcController controller;
  // 发起RPC调用
  calc_stub.Add(&controller, &req_pb, &rsp_pb, nullptr);
  calc_stub.Multiply(&controller, &req_pb, &rsp_pb, nullptr);
}
```

## 常见问题

### 1. Protobuf 在本项目中的作用

1. 序列化和反序列化

   RPC请求和响应都是结构体数据，但是网络传输是字节流，因此需要把结构体转换成字节流发送，在对端将接受到的字节流恢复成结构体。

2. 为RPC方法提供接口

   **RPC服务提供方：**

   在proto文件中定义的RPC服务和方法，编译后会生成.pb.h和.pb.cc文件。RPC提供方需要定义一个新类，继承自pb生成的RPC服务类，并重写几个RPC方法的虚函数。RPC服务最终都是通过调用 `CallMethod` 函数：

   ```c++
   service->CallMethod(method_desc, nullptr, req_msg.get(), rsp_msg.get(), done.get());
   ```

   **RPC服务调用方：**

   生成的pb文件中有相应RPC服务的“存根”，即Stub。调用方都是通过Stub发起RPC请求，实际上都是调用的 `RpcChannel::CallMethod`

   ```c++
   // calculate.pb.cc
   void CalcService_Stub::Add(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                                 const ::zprpc::CalcRequest* request,
                                 ::zprpc::CalcResponse* response,
                                 ::google::protobuf::Closure* done) {
     channel_->CallMethod(descriptor()->method(0),
                          controller, request, response, done);
   }
   void CalcService_Stub::Multiply(::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                                 const ::zprpc::CalcRequest* request,
                                 ::zprpc::CalcResponse* response,
                                 ::google::protobuf::Closure* done) {
     channel_->CallMethod(descriptor()->method(1),
                          controller, request, response, done);
   }
   ```

   

### 2. zookeeper 在本项目中的作用

zookeeper是一个开源的分布式应用程序协调服务器。通常，RPC服务的调用方和提供方是不同的机器，因此RPC调用方需要知道所调用的服务在哪台机器上，即获取RPC提供方的IP地址。

如图所示，RPC提供方将自己的服务名、方法名和IP地址登记到zookeeper服务器上（实际上就是建立一个临时znode节点），并不断向服务器发送脉搏。RPC调用方先从zookeeper服务器上获取相应服务的IP地址，然后才发起RPC请求。

![](/home/huangchen/Project/zprpc/pic/zookeeper.png)

```c++
// RPC提供方，向zookeeper服务器登记RPC服务

// 向zookeeper发布服务
ZkClient zk_client;
zk_client.Start();
// 遍历所有注册的服务
for (const auto &p : service_map_) {
  const google::protobuf::ServiceDescriptor *service_desc = (p.second)->GetDescriptor();
  std::string service_name = "/" + service_desc->name();
  zk_client.Create(service_name, "", 0);

  // 遍历服务中所有的方法
  int method_count = service_desc->method_count();
  for (int i = 0; i < method_count; ++i) {
    const google::protobuf::MethodDescriptor *method_desc = service_desc->method(i);
    std::string method_name = method_desc->name();
    std::string znode_path = service_name + "/" + method_name;
    zk_client.Create(znode_path, server_addr.to_string(), ZOO_EPHEMERAL);
  }
}
```

```c++
// RPC服务调用方，向zookeeper服务器获取RPC服务所在的机器IP地址

// 从zookeeper获得服务提供者的地址
ZkClient zk_client;
zk_client.Start();
std::string znode_path = "/" + service_name + "/" + method_name;
std::string provider_addr = zk_client.GetData(znode_path);
// 无法查询到该服务
if (provider_addr == "") {
  LOG_ERROR << "method doesn't exist";
  zprpc_controller->SetFailed("method doesn't exist");
  return;
}
```

### 3. RPC提供方挂掉，或者zookeeper服务器挂掉，会发生什么？

RPC提供方向zookeeper服务器登记服务后，就会定期向zookeeper服务器发送脉搏。一旦RPC提供方挂掉，zookeeper服务器一段时间没收到脉搏，则认定RPC提供方已经挂掉了，删除登记的RPC服务。

zookeeper服务器一旦挂掉，则RPC提供方和调用方都不能正常工作。后续考虑能够配置多个zookeeper服务器，增加系统可靠性。

### 4. 发生RPC超时怎么办

可以在调用方的配置文件中配置RPC请求的超时时间，默认是1000ms。当发生超时的时候，RPC请求会失败。

但是，RPC超时不应该用这样简单粗暴的方法处理，因为无法判断此时究竟进行到哪一步了，是请求根本没发到对方？还是对方没处理完？还是对方没有回包？所以后续考虑优化一下。

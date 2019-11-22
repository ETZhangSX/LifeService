# 调用服务接口
在[创建第一个Tars应用](/docs/QuickStart.md)中，我们创建了我们的第一个Tars应用`FirstApp`，包含服务`HelloServer`，并添加了一个接口`hello`。

接下来，我们来创建一个服务，并调用`hello`接口，这里我们同样以TarsCpp为例。

## 服务创建
为了更直观的展示，我们创建一个Http服务，使用TarsCpp中的脚本`create_http_server.sh`来创建项目
```sh
sh /usr/local/tars/cpp/script/create_http_server.sh FirstApp HttpServer Http
```
会创建如下文件
```
FirstApp
└── HttpServer
    ├── HttpImp.cpp
    ├── HttpImp.h
    ├── HttpServer.cpp
    ├── HttpServer.h
    └── makefile
```
可以发现和创建tars服务不同，没有生成tars接口文件，因为该服务使用的是http协议而不是tars协议。

## 引入tars文件

由于本服务需要调用`HelloServer`的接口，因此我们需要引入`HelloServer`的tars接口文件。

我们将`Hello.tars`复制到本目录中，然后转化为对应的C++文件`Hello.h`
```sh
/usr/local/tars/cpp/tools/tars2cpp Hello.tars
```

最后项目目录如下
```
FirstApp
└── HttpServer
    ├── HttpImp.cpp
    ├── HttpImp.h
    ├── HttpServer.cpp
    ├── HttpServer.h
    ├── Hello.tars
    ├── Hello.h
    └── makefile
```

## 接口调用
### 获取通信器
使用tars协议的服务之间通过通信器进行通信，在服务启动时，需要获取一个通信器对象。通过通信器，生成特定服务的代理，服务或客户端可以使用该代理调用特定服务的接口。

在服务中，可以通过`Application::getCommunicator()`获取通信器。

### 生成代理
首先，我们在`HttpImp.h`中包含`Hello.h`，并添加服务者`Hello`的代理类的变量`_pHello`，如下

#### HttpImp.h
```cpp
#ifndef _HttpImp_H_
#define _HttpImp_H_

#include "servant/Application.h"
#include "Hello.h"

class HttpImp : public Servant
{
public:
    virtual ~HttpImp() {}

    virtual void initialize();

    virtual void destroy();

    int doRequest(TarsCurrentPtr current, vector<char> buffer);

private:
    int doRequest(const TC_HttpRequest &req, TC_HttpResponse &rsp);
    FirstApp::HelloPrx _pHello;
};
/////////////////////////////////////////////////////
#endif
```


然后，在`HttpImp.cpp`的`initialize()`中获取通信器，并使用通信器初始化该代理对象，如下

```cpp
...

void HttpImp::initialize()
{
    _pHello = Application::getCommunicator()->stringToProxy<FirstApp::HelloPrx>("FirstApp.HelloServer.HelloObj");
}

...
```

### 通过代理调用接口
我们可以在`HttpImp.cpp`中发现两个`doRequest`函数，分别为
```cpp
int HttpImp::doRequest(TarsCurrentPtr current, vector<char> &buffer)
```
和
```cpp
int HttpImp::doRequest(const TC_HttpRequest &req, TC_HttpResponse &rsp)
```
前者为服务使用非TARS协议时需要定义的函数，这里已经帮我们定义好了，因此我们不需要修改。

后者为Http服务的具体逻辑，因此我们在这里添加接口调用逻辑，如下
```cpp
int HttpImp::doRequest(const TC_HttpRequest &req, TC_HttpResponse &rsp)
{
    string msg = "Hello Tars!";
    /**调用hello接口***/
    string helloMsg;
    int ret = _pHello->hello(helloMsg);
    if (ret == 0)
    {
        msg += "<br>" + helloMsg;
    }
    /****************/
    rsp.setContentType("html/text");
    rsp.setResponse(msg.c_str(), msg.size());
    return 0;
}
```
中间添加的部分为调用`hello`接口的逻辑，if语句的作用是如果调用服务没有出错（返回 0），则将返回的字符串`helloMsg`添加到输出的`msg`中。

同时还需要修改`rsp.setContentType("html/text")`中的`html/text`为`text/html`，脚本自动生成的是错误的，未修改会导致浏览器直接下载页面。

修改后的`HttpImp.cpp`如下
```cpp
#include "HttpImp.h"
#include "servant/Application.h"

using namespace std;

//////////////////////////////////////////////////////
void HttpImp::initialize()
{
    _pHello = Application::getCommunicator()->stringToProxy<FirstApp::HelloPrx>("FirstApp.HelloServer.HelloObj");
}

//////////////////////////////////////////////////////
void HttpImp::destroy()
{
}

int HttpImp::doRequest(TarsCurrentPtr current, vector<char> &buffer)
{
    TC_HttpRequest req;
    TC_HttpResponse rsp;
    // parse request header
    vector<char> v = current->getRequestBuffer();
    string sBuf;
    sBuf.assign(&v[0], v.size());
    req.decode(sBuf);

    int ret = doRequest(req, rsp);

    rsp.encode(buffer);

    return ret;
}

int HttpImp::doRequest(const TC_HttpRequest &req, TC_HttpResponse &rsp)
{
    string msg = "Hello Tars!";
    /**调用hello接口***/
    string helloMsg;
    int ret = _pHello->hello(helloMsg);
    if (ret == 0)
    {
        msg += "<br>" + helloMsg;
    }
    /****************/
    rsp.setContentType("text/html");
    rsp.setResponse(msg.c_str(), msg.size());
    return 0;
}
```
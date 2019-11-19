# <a id="create-first-app"></a>创建第一个Tars应用
安装完Tars基础环境，就可以在Tars框架上部署应用了，如果还未安装，可以参考[Tars部署文档](https://github.com/TarsCloud/Tars/blob/master/shellDeploy/introduction.md)。

那么接下来，我们来创建第一个Tars的Hello World应用吧。由于Tars支持多语言，这里我们以C++为例，使用TarsCpp开发框架创建我们的第一个应用，其他语言大同小异。
## 目录
* [安装TarsCpp开发框架](#install-tarscpp)
* [创建应用](#create-project)
* [添加接口](#add-interface)
* [服务打包](#server-packing)
* [服务部署发布](#server-deploy)
* [接口调试](#interface-debug)

## <a id="install-tarscpp"></a>安装TarsCpp开发框架
要进行Tars应用开发，我们需要安装对应语言的开发框架，我们可以使用如下命令下载、编译并安装TarsCpp
```sh
git clone https://github.com/TarsCloud/TarsCpp.git --recursive
cd TarsCpp
cmake .
make
make install
```
安装的路径为`/usr/local/tars/cpp/`，其中
* 在`/usr/local/tars/cpp/script/`中，提供了用于创建项目的两个脚本`create_tars_server.sh`和`create_http_server.sh`，分别用于创建基于tars协议的应用和基于Http协议(非tars)的应用。
* 在`/usr/local/tars/cpp/tools/`中，提供了多个将tars协议文件转换为对应语言代码的脚本，如`tars2cpp`，将tars文件转换为c++代码，`tars2go`将tars文件转换为go代码。
## <a id="create-project"></a>创建应用
在任意目录下，我们可以运行上节提到的用于创建项目的脚本来创建项目，如下
```sh
sh /usr/local/tars/cpp/script/create_tars_server.sh FirstApp HelloServer Hello
```

> 三个参数`FirstApp`, `HelloServer`, `Hello` 分别为应用名(App)、服务名(Server)、服务者(Servant), 具体含义如下
> * 应用名：标识一组服务的一个小集合，比如本案例是一个名为`LifeService`的应用，包含了多个服务；
> * 服务名：提供服务的进程名称，一般根据业务服务功能命名，如`UserInfoServer`, 即用户信息服务；
> * 服务者：提供服务的接口或实例，包含接口的具体实现
>
> 三者的对应关系为，一个App可以有多个Server，一个Server可以有多个Servant，三者的名字组合，App+Server+Servant，可以唯一确定服务者。

执行脚本后，会在当前目录生成如下目录及文件
```sh
.
└── FirstApp
    └── HelloServer
        ├── HelloServer.h       # 服务实现类
        ├── HelloServer.cpp
        ├── Hello.tars          # tars接口文件
        ├── HelloImp.h          # Servant接口实现类
        ├── HelloImp.cpp
        └── makefile            # make编译文件
```

## <a id="add-interface"></a>添加接口
### tars接口文件
`Hello.tars`是定义服务tars接口的文件，用于使用tars协议的服务，默认生成的文件包含一个接口`test`，如下
```cpp
module FirstApp
{
    interface Hello
    {
        int test();
    }
}
```
我们定义一个`hello`接口，传回一个`string`类型的参数，添加后的`Hello.tars`文件如下
```cpp
module FirstApp
{
    interface Hello
    {
        int test();
        int hello(out string res);
    }
}
```
然后使用`tars2cpp`脚本生成对应的C++文件`hello.h`，命令如下
```sh
/usr/local/tars/cpp/tools/tars2cpp hello.tars
```
执行后目录结构如下
```sh
FirstApp
└── HelloServer
    ├── HelloServer.h       # 服务实现类
    ├── HelloServer.cpp
    ├── Hello.tars          # tars接口文件
    ├── Hello.h             # tars接口文件生成的c++代码
    ├── HelloImp.h          # Servant接口实现类
    ├── HelloImp.cpp
    └── makefile            # make编译文件
```
### 在 `HelloImp` 接口实现类中添加 `hello` 接口的实现
`HelloImp`是接口实现类，包含了对`tars`接口文件中定义的接口的实现。我们现在在其中添加`hello`接口的实现。

首先在`HelloImp.h`中添加对应接口的声明
```cpp
#ifndef _HelloImp_H_
#define _HelloImp_H_

#include "servant/Application.h"
#include "Hello.h"
/**
 * HelloImp继承hello.h中定义的Hello对象
 */
class HelloImp : public TestApp::Hello
{
public:
    virtual ~HelloImp() {}

    /**
     * 初始化，Hello的虚拟函数，HelloImp初始化时调用
     */
    virtual void initialize();

    /**
     * 析构，Hello的虚拟函数，服务析构HelloImp退出时调用
     */
    virtual void destroy();

    /**
     * 实现tars文件中定义的test接口
     */
    virtual int test(tars::TarsCurrentPtr current) { return 0;};
    // hello接口声明
    virtual int hello(std::string &res, tars::TarsCurrentPtr current);
};
/////////////////////////////////////////////////////
#endif
```
然后在`HelloImp.cpp`中添加`hello`接口的定义
```cpp
#include "HelloImp.h"
#include "servant/Application.h"

#include <string>

using namespace std;

//////////////////////////////////////////////////////
void HelloImp::initialize()
{
    //initialize servant here:
}

//////////////////////////////////////////////////////
void HelloImp::destroy()
{
    //destroy servant here:
}
//////////////////////////////////////////////////////
// hello接口实现
int HelloImp::hello(string &res, tars::TarsCurrentPtr current)
{
    res = "Hello World";  // 输出参数设为Hello World
    return 0;
}
```
这样我们就完成了`hello`接口的添加和实现

## <a id="server-packing"></a>服务打包
### 编译打包
执行编译和打包命令
```sh
make
make tar
```
就会在当前目录下生成`HelloServer`的发布包`HelloServer.tgz`

### 发布包下载
如果使用的是有**图形界面**的虚拟机且带有**浏览器**，可以跳过下载步骤，直接到发布的步骤，使用虚拟机中的浏览器发布

* 如果是使用Windows，连接服务器时使用的是PuTTY的话，可以使用`pscp`命令下载
```sh
pscp -scp root@1.2.3.4:${应用路径}/FirstApp/HelloServer/HelloServer.tgz ./
```
* 如果使用的是Xshell，可以使用`sz`命令，需要现在服务器上安装该命令`yum install -y lrzsz`，然后下载到本地
```sh
sz HelloServer.tgz
```
* Mac和Linux下可以直接使用scp命令
```sh
scp root@1.2.3.4:${应用路径}/FirstApp/HelloServer/HelloServer.tgz ./
```

## <a id="server-deploy"></a>服务部署发布

### 服务部署
打开浏览器，进入Tars Web管理平台(访问服务器或虚拟机的3000端口，即`${服务器IP或域名}:3000`，如`1.2.3.4:3000`)

![](/ReadMePicture/QuickStartTarsWeb.png)

打开`运维管理>服务部署`，填写如下服务信息
* 服务基本信息：
    * 应用名称：FirstApp
    * 服务名称：HelloServer
    * 服务类型：tars_cpp
    * 模板名称：tars.default
* Obj部署信息：
    * OBJ名称：HelloObj
    * 协议类型：TARS
    * 端口：自动生成

其中`OBJ`名对应我们创建项目时的`Servant`名，为`Servant`名+`Obj`，如这里我们的`Servant`名为`Hello`，`OBJ`名则为`HelloObj`。

节点填写自己部署服务的服务器IP，端口可以点击`获取端口`自动生成即可
![](/ReadMePicture/QuickStartServerDeploy.png)

点击确定，提交服务部署申请，即可在`服务管理`页面看到我们刚刚部署的应用
![](/ReadMePicture/QuickStartServerManage.png)

### 服务发布
服务部署的过程相当于给要发布的服务申请了一个位置，还没有对应的业务代码，因此我们需要把我们前面生成的发布包上传

打开Tars Web管理平台页面，在`服务管理`页左边菜单选择我们刚刚部署的服务`FirstApp > HelloServer`，这里展示的是服务列表和服务实时状态信息
![](/ReadMePicture/QuickStartHelloServer.png)

点击顶部Tab栏的`发布管理`，选中服务节点，点击`发布选中节点`
![](/ReadMePicture/QuickStartDeployManage_0.png)

然后

1. 点击`上传发布包`，将下载的发布包上传
2. 在`发布版本`，选择我们刚刚上传的版本
3. 点击`发布`，完成服务发布

![](/ReadMePicture/QuickStartDeployManage.png)

回到`服务管理`，我们可以看到服务发布成功，状态为`Active`，还有发布成功的日志显示在`服务实时状态`中
![](/ReadMePicture/QuickStartServerDeploySucc.png)

## <a id="interface-debug"></a>接口调试
接下来我们来测试我们新增的接口是否可用

点击`接口调试`，然后
1. 点击`添加`上传服务的tars接口文件`Hello.tars`，如下，会新增一条tars文件记录
2. 点击`调试`，进入接口调试页面
![](/ReadMePicture/QuickStartUploadTarsFile.png)

在调试页面
1. 选择要调试的接口，`FirstApp/Hello/hello`
2. 点击`调试`

然后可以在右侧文本框中看到返回的数据，`"res":"Hello World"`就是`hello`接口返回的参数。左侧文本框用于输入传入参数，`hello`
接口无传入参数，因此无需输入
![](/ReadMePicture/QuickStartDebuge.png)

到这里，我们的第一个Tars应用就完成啦。
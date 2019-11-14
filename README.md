# Tars案例--大学生活服务平台

本案例是一个简单的大学生活服务平台小程序应用，包含了简单的用户登录、社团活动管理和表白墙的功能。本文会介绍包括如何购买服务器、连接服务器、环境部署和服务部署的内容。

## 目录
* [项目简介](#introduction)
    * [功能](#introduction-function)
    * [项目结构](#introduction-structure)
    * [项目逻辑架构](#introduction-logic-architecture)
    * [项目部署架构](#introduction-deploy-architecture)
* [上云](#cloud)
    * [云服务器购买](#server-purchase)
        * [腾讯云](#server-purchase-tencent-cloud)
        * [阿里云](#server-purchase-aliyun)
    * [连接服务器](#connect-server)
* [Tars基础环境搭建](#tars-framework-installation)
* [创建第一个Tars应用](#create-first-app)
    * [安装TarsCpp开发框架](#install-tarscpp)
    * [创建应用](#create-project)
    * [添加接口](#add-interface)
    * [服务打包发布](#server-deploy)
* [TARS GO安装](#tarsgo-installation)
    * [安装Go](#install-go)
    * [安装TarsGo](#install-tarsgo)
<!-- * [后端服务代码下载和编译](#main-chapter-6)
* [后端服务通过Tars部署](#main-chapter-7) -->


## <a id="introduction"></a>项目简介
学生校园生活服务平台小程序，前端为微信小程序（WePY框架和vant组件）；后端使用了Tars微服务框架 (TarsNode.js, TarsGo, TarsCpp)；数据库使用了MySQL。

### <a id="introduction-function"></a>功能
小程序可以分为三个功能模块，用户模块、表白墙、社团活动，各模块包含的具体功能如下
<!-- ![](/ReadMePicture/IntroductionFunction.png) -->
<img width="400" src="https://github.com/ETZhangSX/LifeService/blob/master/ReadMePicture/IntroductionFunction.png?raw=true">

小程序UI效果图：

![](/ReadMePicture/IntroductionUI.png)

### <a id="introduction-structure"></a>项目结构
```sh
.
├── DataServer          # 数据访问服务
├── ClubActivityServer  # 社团活动服务
├── UserInfoServer      # 用户信息服务
├── MessageWallServer   # 表白墙服务
├── InterfaceServer     # 接入服务
├── ReadMePicture       # 文档图片
└── README.md
```

### <a id="introduction-logic-architecture"></a>项目逻辑架构
小程序的前后端逻辑架构如下

![image](/ReadMePicture/logicArchitecture.png)

小程序端各模块的功能通过HTTPS请求和接入层交互，其中用户模块中的微信登录功能通过接入层的微信API代理调用微信API获取用户openID，其它功能通过接入服务调用服务层的服务接口。
### <a id="introduction-deploy-architecture"></a>项目部署架构
实际部署部署，采用普通PC做为前端设备，将具体应用部署在两台服务器上。 其中蓝色表示部署前端小程序, 橘黄色表示部署的应用服务, 绿色表示Tars服务框架.
其中值得说明的是: 我们将`ClubActivityServer`, `MessageWallServer`, `UserInfoServer` 三个服务分别部署在2台服务器上, 实现业务符合分担和高可靠谱性. 
![image](/ReadMePicture/DataArchitecture.jpg)

管理面交互情况如下：
![image](/ReadMePicture/ManagementArchitecture.jpg)

## <a id="cloud"></a>上云
Tars框架和应用需要运行在Linux上，同时小程序的发布、上线也需要有符合要求的云环境，本节会讲述一个上云的完整流程。如果不打算上线发布应用，只想在本地服务器中尝试的话，可以跳过本部分，使用虚拟机代替。
### <a id="server-purchase"></a>云服务器购买
#### <a id="server-purchase-tencent-cloud"></a>腾讯云
##### 登录
* 首先我们进入腾讯云首页(https://cloud.tencent.com)
![image](/ReadMePicture/TencentCloudIndex.png)
* 点击右上角的登录，可以使用QQ或微信登录

##### 学生购买
* 如果是学生，可以点击中间的`云+校园扶持计划`，按照要求完成学生认证即可购买，学生每月只需要10元。
![](/ReadMePicture/TencentCloudCampus.png)
* 地域根据自己需求选择即可，可以选择离自己最近的，系统选择`CentOS 7.5 64位`，配置不可选择，默认学生配置为`1核2GB`，已经足够使用了。
* 购买时长，可以根据自己需求，本案例中因为使用了小程序，需要备案，因此购买时长需要大于三个月

##### 非学生购买
* 非学生的话，需要通过主页顶部菜单栏的`产品>基础>计算>云服务器`进入云服务器页面，点击`立即选购`进入购买页面
![](/ReadMePicture/TencentCloudBuyCvm.png)
* 机型配置方面，最低需要`1核2GB`，系统我们选择`CentOS 7.2`
* 购买时长，可以根据自己需求，本案例中因为使用了小程序，需要备案，因此购买时长需要大于三个月

##### 密码重置
* 服务器初始化使用的是随机生成的密码，我们可以重置服务器登录密码
* 点击主页右上角的`控制台`，可以进入自己的控制台看到自己购买的服务器信息
* 点击左侧Tab栏的`实例`，右侧会显示自己的服务实例
![](/ReadMePicture/TencentCloudConsoleCvm.png)
* 点击实例的`操作>更多>密码/密钥>重置密码`，即可重置实例的root用户密码

#### <a id="server-purchase-aliyun"></a>阿里云

##### 登录
* 进入阿里云首页(https://www.aliyun.com)
![](/ReadMePicture/AliyunIndex.png)
* 点击上方的登录进入登录页，可以使用淘宝、支付宝等账号登录

##### 学生购买
* 进入[云翼计划](https://promotion.aliyun.com/ntms/act/campus2018.html)页面
![](/ReadMePicture/AliyunCampus.png)
* 完成学生认证即可购买，每月9.5元
* 系统选择`CentOS 7.3 64`，地域根据自己需求选择，可以选择离自己较近的
* 默认配置为`1核2G`

##### 非学生购买
* 点击首页顶部`产品分类>云计算基础>弹性计算>云服务器>云服务器 ECS`，进入云服务器页面点击`立即购买`进入购买选择页
![](/ReadMePicture/AliyunBuyEcs.png)
* 系统类型选择`CentOS`，版本选择7以上即可
* 配置上，选择内存2G以上的实例即可

##### 密码重置
* 点击顶部的控制台进入控制台页面
* 点击左侧Tab的`云服务器 ECS`，进入云服务器管理页面
* 点击左侧Tab栏中的`实例`，右侧展示自己的实例信息
![](/ReadMePicture/AliyunConsole.png)
* 点击实例的`操作>更多>密码/密钥>重置实例密码`，即可重置实例密码
![](/ReadMePicture/AliyunConsoleEcs.png)

### <a id="connect-server"></a>连接服务器

服务器可以使用`ssh`协议来远程连接，不同的系统使用的工具不太一样

#### Windows 连接到服务器

由于Win10以前的Windows版本没有内置OpenSSH，连接服务器时需要使用额外的连接工具，工具的种类也有很多，比如`XShell`, `PuTTY`等，使用上基本大同小异，可以搜索一下使用方法。

在进行连接时，在主机名(Host Name或IP Address)栏中填写服务器的公网IP，端口一般为默认的`22`，用户名一般为`root`，密码即为上一节中我们购买服务器后重置的密码，然后连接就能够进入服务器的终端界面了。

#### MacOS, Linux连接到服务器

在macOS和Linux中，我们只需要打开终端(Terminal)，使用`ssh`命令连接服务器即可，如下（Win10中也可以在CMD中使用相同的命令连接）
```sh
ssh root@${IP地址} -p ${端口}
```
例如连接到公网IP为`1.2.3.4`的服务器，`ssh`使用的端口是`3366`
```sh
ssh root@1.2.3.4 -p 3366
```
回车后输入密码即可进入服务器终端，进行Tars框架安装、应用开发、部署等操作。

## <a id="tars-framework-installation"></a>Tars基础环境搭建 
参见：
https://github.com/TarsCloud/Tars/blob/master/shellDeploy/introduction.md
使用一键部署脚本，完成Tars基础环境的部署。
![image](/ReadMePicture/tarsFrameworkBasicPic.png)

## <a id="create-first-app"></a>创建第一个Tars应用
安装完Tars基础环境，就可以在Tars框架上部署应用了。接下来我们来创建第一个Tars的Hello World应用吧。由于Tars支持多语言，这里我们以C++为例，使用TarsCpp开发框架创建我们的第一个应用，其他语言大同小异。

### <a id="install-tarscpp"></a>安装TarsCpp开发框架
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
### <a id="create-project"></a>创建应用
在任意目录下，我们可以运行上节提到的用于创建项目的脚本来创建项目，如下
```sh
sh /usr/local/tars/cpp/script/create_tars_server.sh FirstApp HelloServer Hello
```
<!--
> 三个参数`FirstApp`, `HelloServer`, `Hello` 分别为应用名(App)、服务名(Server)、服务者(Servant), 具体含义如下
> * 应用名：标识一组服务的一个小集合，比如本案例就是一个名为`LifeService`的应用，包含了多个服务；
> * 服务名：提供服务的进程名称，一般根据业务服务功能命名，如`UserInfoServer`,即用户信息服务
> * 服务者：提供服务的接口或实例，包含接口的具体实现
>
> 三者的对应关系为，一个App可以有多个Server，一个Server可以有多个Servant，三者的名字组合，App+Server+Servant，可以唯一确定服务者。
-->
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
### <a id="add-interface"></a>添加接口
#### tars接口文件
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
#### 在 `HelloImp` 接口实现类中添加 `hello` 接口的实现
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

### <a id="server-deploy"></a>服务打包发布
#### 编译打包
执行编译和打包命令
```sh
make
make tar
```
就会在当前目录下生成`HelloServer`的发布包`HelloServer.tgz`，然后将发布包从开发容器下载到本地

#### 发布包下载
如果使用的是有**图形界面**的虚拟机且带有**浏览器**，可以跳过下载步骤，直接到发布的步骤

* 如果是使用Windows，连接服务器时使用的是PuTTY的话，可以使用pscp命令下载
```sh
pscp -scp root@1.2.3.4:${应用路径}/FirstApp/HelloServer/HelloServer.tgz ./
```
* 如果使用的是Xshell，可以使用sz命令，需要现在服务器上安装该命令`yum install -y lrzsz`，然后下载到本地
```sh
sz HelloServer.tgz
```
* Mac和Linux下可以直接使用scp命令
```sh
scp root@1.2.3.4:${应用路径}/FirstApp/HelloServer/HelloServer.tgz ./
```

#### 服务发布
待续……

## <a id="tarsgo-installation"></a> Tars Go安装
### <a id="install-go"></a>Go环境安装
https://golang.org/doc/install  下载其中：Linux  X86 64位版本

Go下载和解压
- 下载go1.13.1.linux-amd64.tar.gz 

```sh
wget https://dl.google.com/go/go1.13.1.linux-amd64.tar.gz
```

- 然后：
```sh
mkdir -p /usr/local/go
cd /usr/local
tar -C /usr/local -xzf go1.13.1.linux-amd64.tar.gz
```


配置环境变量
- 在/etc/profile中，增加：
```vim
export PATH=$PATH:/usr/local/go/bin 
export GOPATH=$HOME/go 
export GOROOT=/usr/local/go
```
- 然后保存，并执行
```sh
source /etc/profile
```

### <a id="install-tarsgo"></a> 安装Tars Go

使用如下命令安装Tars Go
```sh
go get github.com/TarsCloud/TarsGo/tars
```

编译tars协议转Golang的脚本工具
```sh
cd $GOPATH/src/github.com/TarsCloud/TarsGo/tars/tools/tars2go && go build . 
cp tars2go $GOPATH/bin/
```

<!-- ## <a id="main-chapter-4"></a> 后端服务代码下载和编译

Fork 如下Git链接（后续会合入Tars主要分支）

https://github.com/qiuxin/MessageWallServer

https://github.com/qiuxin/UserInfoServer

https://github.com/qiuxin/ClubActivityServer


```sh
mkdir -p /root/go/src/
```

然后进入/root/go/src/目录，将如上代码下载到该目录：

```sh
git clone https://github.com/qiuxin/MessageWallServer

git clone https://github.com/qiuxin/UserInfoServer

git clone https://github.com/qiuxin/ClubActivityServer
```

分别进入ClubActivityServer，MessageWallServer，UserInfoServer目录，执行`make tar`.

可以看到在三个目录下，分别生成ClubActivityServer.tgz，MessageWallServer.tgz， UserInfoServer.tgz三个文件。  -->





<!-- ## <a id="main-chapter-4"></a> 后端服务通过Tars部署
将生成的ClubActivityServer.tgz，MessageWallServer.tgz， UserInfoServer.tgz三个文件传到本地电脑上，进行部署。

部署时候，需要使用的参数如下：

| 部署服务      | 应用名称     | 服务名称     | Obj名称     | 服务类型     |模板     |
| ---------- | :-----------:  | :-----------: |:-----------: |:-----------: |:-----------: |
| UserInfoServery     | LifeService    | UserInfoServer     |UserInfoServiceObj     |Tars Go     |默认模板     |
| ClubActivityServer     | LifeService     | ClubActivityServer     |ClubActivityManagerObj     |Tars Go     |默认模板     |
| MessageWallServer     | LifeService     | MessageWallServer     |MessageWallObj     |Tars Go     |默认模板     |


通过“运维管理”界面进行部署，以UserInfoServer为例部署填写参数如下，其余服务发布按照上表修改参数即可。
![image](/ReadMePicture/ServiceDeploy.png)

部署完成之后， 在“服务管理” 下面的“发布管理”中上传发布包，进行发布。
![image](/ReadMePicture/ServiceDistribution.png)

发布成功之后，可以看到如下界面：
![image](/ReadMePicture/OneServiceDeployAndDisSuccessful.png)

以此类推，同样的方法，发布另外2个服务。发布完成之后，效果如下图：
![image](/ReadMePicture/MultipleServiceDeployAndDisSuccessful.png) -->

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
* [Tars基础环境搭建](#main-chapter-3)
* [Go环境安装](#main-chapter-4)
* [TAR GO安装](#main-chapter-5)
* [后端服务代码下载和编译](#main-chapter-6)
* [后端服务通过Tars部署](#main-chapter-7)


## <a id="introduction"></a>项目简介
学生校园生活服务平台小程序，前端为微信小程序（WePY框架和vant组件）；后端使用了Tars微服务框架 (TarsNode.js, TarsGo, TarsCpp)；数据库使用了MySQL。

### <a id="introduction-function"></a>功能
小程序可以分为三个功能模块，用户模块、表白墙、社团活动，各模块包含的具体功能如下
![](/ReadMePicture/IntroductionFunction.png)

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

## <a id="main-chapter-3"></a>Tars基础环境搭建 
参见：
https://github.com/TarsCloud/Tars/blob/master/shellDeploy/introduction.md
使用一键部署脚本，完成Tars基础环境的部署。
![image](/ReadMePicture/tarsFrameworkBasicPic.png)


## <a id="main-chapter-4"></a>Go环境安装
https://golang.org/doc/install  下载其中：Linux  X86 64位版本

GO下载和解压
- 在/usr/local/下载go1.13.1.linux-amd64.tar.gz 

```
wget https://dl.google.com/go/go1.13.1.linux-amd64.tar.gz
```

- 然后：
```
mkdir -p /usr/local/go
cd /usr/local
tar -C /usr/local -xzf go1.13.1.linux-amd64.tar.gz
```


配置环境变量
- 在/etc/profile中，增加：
```
export PATH=$PATH:/usr/local/go/bin 
export GOPATH=$HOME/go 
export GOROOT=/usr/local/go
```

然后保存，并执行
```
source /etc/profile
```

## <a id="main-chapter-4"></a> TAR GO安装
安装tars： 
```
go get github.com/TarsCloud/TarsGo/tars
```


编译tars协议转Golang工具：
```
cd $GOPATH/src/github.com/TarsCloud/TarsGo/tars/tools/tars2go && go build . 
cp tars2go $GOPATH/bin/
```

## <a id="main-chapter-4"></a> 后端服务代码下载和编译

Fork 如下Git链接（后续会合入Tars主要分支）

https://github.com/qiuxin/MessageWallServer

https://github.com/qiuxin/UserInfoServer

https://github.com/qiuxin/ClubActivityServer


```
mkdir -p /root/go/src/
```

然后进入/root/go/src/目录，将如上代码下载到该目录：

```
git clone https://github.com/qiuxin/MessageWallServer

git clone https://github.com/qiuxin/UserInfoServer

git clone https://github.com/qiuxin/ClubActivityServer
```

分别进入ClubActivityServer，MessageWallServer，UserInfoServer目录，执行make tar.

可以看到在三个目录下，分别生成ClubActivityServer.tgz，MessageWallServer.tgz， UserInfoServer.tgz三个文件。 





## <a id="main-chapter-4"></a> 后端服务通过Tars部署
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
![image](/ReadMePicture/MultipleServiceDeployAndDisSuccessful.png)

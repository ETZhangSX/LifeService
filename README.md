# Tars案例--大学生活服务平台

本案例是一个简单的大学生活服务平台小程序应用，包含了简单的用户登录、社团活动管理和表白墙的功能。前端小程序使用了WEPY框架和vant组件，后端服务使用了Tars框架进行开发。

关于本应用的具体功能及架构信息，参考[项目简介](/docs/Introduction.md)。

## 基础环境
* 应用后端使用Tars框架，目前支持的平台是Linux，可以选择运行Linux的云服务器或虚拟机。如果需要将应用部署到云上，可以参考[上云流程](/docs/CloudMigration.md)。
* Tars基础环境安装可以参考[Tars部署安装文档](https://github.com/TarsCloud/Tars/blob/master/Install.zh.md)或[Shell脚本安装Tars](https://github.com/TarsCloud/Tars/blob/master/shellDeploy/introduction.md)
* 使用的语言：
    * C++
    * Go
    * Node.js

## 案例实践
- 还没有使用过Tars开发应用？没关系，我们来学习如何[创建第一个Tars应用](/docs/QuickStart.md)
- 不知道怎么调用服务接口？问题不大，看这一篇就够了--[如何调用服务接口](/docs/HowToUseRPC.md)
- 已经使用过Tars？那么可以来尝试[部署本案例的服务](/docs/DeployDemo.md)

<!-- ## 目录
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
``` -->

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

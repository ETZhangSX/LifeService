# LifeService
# 目录
> * [1.项目逻辑架构](#main-chapter-1)
> * [2.项目部署架构](#main-chapter-2)
> * [3.Tars基础环境搭建](#main-chapter-3)
> * [4.Go环境安装](#main-chapter-4)
> * [5.TAR GO安装](#main-chapter-5)
> * [6.后端服务代码下载和编译](#main-chapter-6)
> * [7.后端服务通过Tars部署](#main-chapter-7)


# 1. <a id="main-chapter-1"></a>项目逻辑架构
整个小程序的逻辑架构如下：
![image](https://github.com/qiuxin/LifeService/blob/master/ReadMePicture/logicArchitecture.png)

# 2. <a id="main-chapter-2"></a>项目部署架构
实际部署部署，采用普通PC做为前端设备，　将具体应用部署在两台服务器上。 其中蓝色表示部署前端小程序, 橘黄色表示部署的应用服务, 绿色表示Tars服务框架.
其中值得说明的是: 我们将ClubActivityServer, MessageWallServer, UserInfoServer三个服务分别部署在2台服务器上, 实现业务符合分担和高可靠谱性. 
![image](https://github.com/qiuxin/LifeService/blob/master/ReadMePicture/DataArchitecture.jpg)

管理面交互情况如下：
![image](https://github.com/qiuxin/LifeService/blob/master/ReadMePicture/ManagementArchitecture.jpg)

# 3. <a id="main-chapter-3"></a>Tars基础环境搭建 
参见：
https://github.com/TarsCloud/Tars/blob/master/shellDeploy/introduction.md
使用一键部署脚本，完成Tars基础环境的部署。
![image](https://github.com/qiuxin/LifeService/blob/master/ReadMePicture/tarsFrameworkBasicPic.png)


# 4. <a id="main-chapter-4"></a>Go环境安装
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

# 5. <a id="main-chapter-4"></a> TAR GO安装
安装tars： 
```
go get github.com/TarsCloud/TarsGo/tars
```


编译tars协议转Golang工具：
```
cd $GOPATH/src/github.com/TarsCloud/TarsGo/tars/tools/tars2go && go build . 
cp tars2go $GOPATH/bin/
```

# 6. <a id="main-chapter-4"></a> 后端服务代码下载和编译

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





# 7. <a id="main-chapter-4"></a> 后端服务通过Tars部署
将生成的ClubActivityServer.tgz，MessageWallServer.tgz， UserInfoServer.tgz三个文件传到本地电脑上，进行部署。

部署时候，需要使用的参数如下：
- UserInfoServery    	LifeService	UserInfoServer	UserInfoServiceObj	Tars Go	默认模板
- ClubActivityServer	LifeService	ClubActivityServer	ClubActivityManagerObj	Tars Go	默认模板
- MessageWallServer	LifeService	MessageWallServer	MessageWallObj	Tars Go	默认模板

通过“运维管理”界面进行部署，以UserInfoServer为例部署填写参数如下，其余服务发布按照上表修改参数即可。
![image](https://github.com/qiuxin/LifeService/blob/master/ReadMePicture/ServiceDeploy.png)

部署完成之后， 在“服务管理” 下面的“发布管理”中上传发布包，进行发布。
![image](https://github.com/qiuxin/LifeService/blob/master/ReadMePicture/ServiceDistribution.png)

发布成功之后，可以看到如下界面：
![image](https://github.com/qiuxin/LifeService/blob/master/ReadMePicture/OneServiceDeployAndDisSuccessful.png)

以此类推，同样的方法，发布另外2个服务。发布完成之后，效果如下图：
![image](https://github.com/qiuxin/LifeService/blob/master/ReadMePicture/MultipleServiceDeployAndDisSuccessful.png)

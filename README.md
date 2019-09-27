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
-  该脚本用于快速部署Tars环境，用户仅需使用“脚本+IP地址”即可快速构建Tars Framework环境

# 2. <a id="main-chapter-2"></a>项目部署架构
该脚本仅仅使用于物理机部署和虚拟机部署（包括云主机），不适用于容器部署（systemctl start 等语句在容器环境运行会出现错误）
-  操作系统 CentOS 7
-  硬件要求：最低2核2G，建议4核8G
-  网络访问通畅，yum、wget等命令可正常执行

# 3. <a id="main-chapter-3"></a>Tars基础环境搭建 
文件夹中的三个脚本的说明：
-  shellDeploy.sh 为主入口脚本， 进行绝大部分安装操作。 shellDeploy.sh调用了mysqlConfig.sh以及importTarsWebSql.sh
-  mysqlConfig.sh 主要用于mysql数据库的配置，包括：用户名，密码，权限，数据库表项导入等等
-  importTarsWebSql.sh 用于导入TarsWeb的数据库表项

# 4. <a id="main-chapter-4"></a>Go环境安装
-  该脚本运行时候，需要使用本机的IP地址做为入参，请先查看本机IP地址。如果是云环境的话，请输入小网IP地址。
-  该脚本中使用Mysql安装环境中的默认密码tars2015作为默认密码，仅供学习和演示使用。实际应用场景，请大家自行修改密码。
-  运行方式：
```
Step1： yum install -y git
Step2： mkdir -p /usr/local/tarscode
Step3： cd /usr/local/tarscode/
Step4： git clone https://github.com/TarsCloud/Tars.git
Step5： cd Tars
Step6： git submodule update --init --recursive
Step7： cd /usr/local/tarscode/Tars/shellDeploy
Step8:  chmod 777 *
Step9:  ./shellDeploy $LocalIPAddr, 其中LocalIPAddr为机器IP地址。例：./shellDeploy 192.168.0.1
```
-  执行完如上脚本之后，tars framework的核心组件已经安装完成，已经可以登入web界面（IP：3000）。
注：启动Tars Web界面后，会遇到错误弹出，发布完tarsnotify即可消失。详见issue: https://github.com/TarsCloud/Tars/issues/456
-  之后将$CodePath/Tars/framework/build路径下的tarsstat.tgz、tarsnotify.tgz、tarsproperty.tgz、tarslog.tgz、tarsquerystat.tgz、tarsqueryproperty.tgz传到本地电脑上，通过web界面进行发布即可。
-  该脚本中使用Mysql安装环境中的默认密码tars2015作为默认密码，仅供学习和演示使用。实际应用场景，请大家自行修改密码。

# 5. <a id="main-chapter-4"></a> TAR GO安装
-  该脚本运行时，会在/usr/local/tarscode/Tars/shellDeploy目录下生成deploy_log文件，该文件中记录了脚本运行过程中的诊断信息，便于故障的定位和解决。

# 6. <a id="main-chapter-4"></a> 后端服务代码下载和编译
-  该脚本运行时，会在/usr/local/tarscode/Tars/shellDeploy目录下生成deploy_log文件，该文件中记录了脚本运行过程中的诊断信息，便于故障的定位和解决。



# 7. <a id="main-chapter-4"></a> 后端服务通过Tars部署
-  该脚本运行时，会在/usr/local/tarscode/Tars/shellDeploy目录下生成deploy_log文件，该文件中记录了脚本运行过程中的诊断信息，便于故障的定位和解决。

# DataServer
案例C++后端，用于直接操作数据库，对其他服务提供数据操作接口

## 构建方式
将项目clone到任意目录下，修改`Config.h`中的数据库配置为自己的数据库配置，然后使用下列命令构建项目，生成发布包

```sh
make
make tar
```

将生成的发布包通过TarsWeb管理页面部署上传发布即可, 同时需要在服务配置中添加如下配置，没有添加会直接使用`Config.h`中填写的值

```xml
<LifeService>
    usPortConfig=3306
    strDbHostConfig=xxx.xxx.xxx.xxx
    strUserNameConfig=yourusername
    strPassWordConfig=yourpassword
    strDbNameConfig=yourdbname
    maxMatch=2000
</LifeService>
```

## 项目结构
```sh
.
├── Config.h                #配置文件
├── DataServer.cpp          #服务实现
├── DataServer.h
├── DataServiceImp.cpp      #接口实现
├── DataServiceImp.h        #接口定义
├── DataService.tars        #tars协议文件
├── DbHandle.cpp            #DbHandle实现
├── DbHandle.h              #数据库模型
├── makefile
├── MysqlHandler.cpp        #MysqlHandler实现
├── MysqlHandler.h          #Mysql操作
├── README.md
├── test
│   └── test_util.cpp       #工具类测试
├── util.cpp                #util实现
└── util.h                  #Mysql语句组装工具
```
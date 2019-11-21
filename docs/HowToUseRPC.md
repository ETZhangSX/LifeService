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



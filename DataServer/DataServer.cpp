#include "DataServer.h"
#include "DataServiceImp.h"
#include "Config.h"
#include "DbHandle.h"
#include "MysqlHandler.h"

using namespace std;

DataServer g_app;

/////////////////////////////////////////////////////////////////
void
DataServer::initialize()
{
    //initialize application here:
    //...

    // 添加配置文件
    addConfig(ServerConfig::ServerName + ".conf");
    // 获取配置文件路径
    const std::string strConfFileName = ServerConfig::BasePath + ServerConfig::ServerName + ".conf";
    LOG->debug() << "conf: " << strConfFileName << endl;
    // 拉取配置文件
    SConfig::getInstance()->LoadConfig(strConfFileName);

    // 加载用户数据和社团数据
    UserHandle::getInstance()->LoadDataFromDb();
    ClubHandle::getInstance()->LoadDataFromDb();

    addServant<DataServiceImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".DataServiceObj");
}
/////////////////////////////////////////////////////////////////
void
DataServer::destroyApp()
{
    //destroy application here:
    //...
}
/////////////////////////////////////////////////////////////////
int
main(int argc, char* argv[])
{
    try
    {
        g_app.main(argc, argv);
        // 初始化MDbExecuteRecord
        if (!MDbExecuteRecord::getInstance()->Init())
        {
            LOG->error() << "db config update thread init error" << endl;
            return -1;
        }
        // 运行MDbExecuteRecord
        MDbExecuteRecord::getInstance()->start();
        g_app.waitForShutdown();
    }
    catch (std::exception& e)
    {
        cerr << "std::exception:" << e.what() << std::endl;
    }
    catch (...)
    {
        cerr << "unknown exception." << std::endl;
    }
    return -1;
}
/////////////////////////////////////////////////////////////////

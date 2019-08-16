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
    addConfig(ServerConfig::ServerName + ".conf");
    const std::string strConfFileName = ServerConfig::BasePath + ServerConfig::ServerName + ".conf";
    LOG->debug() << "conf: " << strConfFileName << endl;
    SConfig::getInstance()->LoadConfig(strConfFileName);

    UserHandle::getInstance()->LoadDataFromDb();

    // InitDbConf(SConfig::getInstance()->strDbHost.c_str(),
    //            SConfig::getInstance()->usPort,
    //            SConfig::getInstance()->strUserName.c_str(),
    //            SConfig::getInstance()->strPassWord.c_str(),
    //            SConfig::getInstance()->strDbName.c_str());

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
        if (!MDbExecuteRecord::getInstance()->Init())
        {
            LOG->error() << "db config update thread init error" << endl;
            return -1;
        }
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

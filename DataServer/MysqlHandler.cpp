#include "MysqlHandler.h"
#include "servant/Application.h"
#include "Config.h"
#include "util.h"

using namespace std;

tars::TC_Mysql * MDbQueryRecord::GetMysqlObject()
{
    unsigned int uiThreadId = (unsigned int) pthread_self();
    // 查询此线程是否存在Mysql对象, 存在则返回; 不存在则新建并保存
    if (MysqlMap.find(uiThreadId) != MysqlMap.end())
    {
        return MysqlMap[uiThreadId];
    }
    else
    {
        tars::TC_Mysql * ptrMysql = new tars::TC_Mysql();

        _tcDbConfig._port     = SConfig::getInstance()->usPort;
        _tcDbConfig._host     = SConfig::getInstance()->strDbHost;
        _tcDbConfig._user     = SConfig::getInstance()->strUserName;
        _tcDbConfig._password = SConfig::getInstance()->strPassWord;
        _tcDbConfig._database = SConfig::getInstance()->strDbName;
        _tcDbConfig._charset  = "utf8";

        try
        {
            ptrMysql->init(_tcDbConfig);
            ptrMysql->connect();
        }
        catch (exception &e)
        {
            // 向Notify节点报告异常
            TarsRemoteNotify::getInstance()->report("CONNECT_MDB_ERROR");
            LOG->error() << "MDbTbUpdateThread::GetMysqlObject exception: " << e.what() << endl;
            delete ptrMysql;    
            return NULL;
        }
        // 将对象存储在map中
        MysqlMap[uiThreadId] = ptrMysql;
        return ptrMysql;
    }
}

void MDbQueryRecord::InsertData(const string &tableName,const vector<LifeService::Column> &columns)
{
    map<string, pair<TC_Mysql::FT, string>> mpColumns;

    for (size_t i = 0; i < columns.size(); i++) 
    {
        if (columns[i].DBInt)
            mpColumns.insert(make_pair(columns[i].columnName, make_pair(TC_Mysql::DB_INT, columns[i].columnValue)));
        else
            mpColumns.insert(make_pair(columns[i].columnName, make_pair(TC_Mysql::DB_STR, columns[i].columnValue)));
    }

    string sql = GetMysqlObject()->buildInsertSQL(tableName, mpColumns);
    LOG->debug() << "Insert report info: " << sql << endl;
    MDbExecuteRecord::getInstance()->AddExecuteSql(sql);
}

// 初始化
bool MDbExecuteRecord::Init()
{
    _tcDbConfig._port     = SConfig::getInstance()->usPort;
    _tcDbConfig._host     = SConfig::getInstance()->strDbHost;
    _tcDbConfig._user     = SConfig::getInstance()->strUserName;
    _tcDbConfig._password = SConfig::getInstance()->strPassWord;
    _tcDbConfig._database = SConfig::getInstance()->strDbName;
    _tcDbConfig._charset = "utf8";

    try
    {
        _pMysql = TC_SharedPtr<TC_Mysql>(new TC_Mysql);
        _pMysql->init(_tcDbConfig);
        _pMysql->connect();
    }
    catch (exception & e)
    {
        LOG->error() << "MDbExcuteRecord::Init exception:" << e.what() << endl;
        return false;
    }
    return true;
}

// 添加SQL语句到队列中
void MDbExecuteRecord::AddExecuteSql(const string& strSql)
{
    TC_ThreadLock::Lock lock(_pLocker);
    _qeWaitExeSql.push(strSql);
}

// 执行队列中的SQL语句
void MDbExecuteRecord::Execute()
{
    string strSql;
    while(!_qeWaitExeSql.empty())
    {
        {
            TC_ThreadLock::Lock lock(_pLocker);
            strSql = _qeWaitExeSql.front();
            _qeWaitExeSql.pop();
        }
        try
        {
            _pMysql->execute(strSql);
            FDLOG("DBLog: ") << strSql << endl;
        }
        catch(exception& e)
        {
            string errMsg(e.what());
            LOG->error() << "MDbExcuteRecord::Excute:" << strSql
                         << " exception:" << errMsg << endl;
            TarsRemoteNotify::getInstance()->report("MysqlExcuteError: " + errMsg);
        }
    }
}

// 每0.1s执行一次
void MDbExecuteRecord::run()
{
    while(true)
    {
        Execute();
        usleep(100000);
    }
}
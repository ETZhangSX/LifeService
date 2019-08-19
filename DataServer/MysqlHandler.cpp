#include "MysqlHandler.h"
#include "servant/Application.h"
#include "Config.h"
#include "util.h"

using namespace std;

tars::TC_Mysql * MDbQueryRecord::GetMysqlObject()
{
    unsigned int uiThreadId = (unsigned int) pthread_self();
    if (MysqlMap.find(uiThreadId) != MysqlMap.end())
    {
        return MysqlMap[uiThreadId];
    }
    else
    {
        tars::TC_Mysql * ptrMysql = new tars::TC_Mysql();

        _tcDbConfig._port = SConfig::getInstance()->usPort;
        _tcDbConfig._host = SConfig::getInstance()->strDbHost;
        _tcDbConfig._user = SConfig::getInstance()->strUserName;
        _tcDbConfig._password = SConfig::getInstance()->strPassWord;
        _tcDbConfig._database = SConfig::getInstance()->strDbName;
        _tcDbConfig._charset = "utf8";

        try
        {
            ptrMysql->init(_tcDbConfig);
            ptrMysql->connect();
        }
        catch (exception &e)
        {
            TarsRemoteNotify::getInstance()->report("CONNECT_MDB_ERROR");
            LOG->error() << "MDbTbUpdateThread::GetMysqlObject exception: " << e.what() << endl;
            delete ptrMysql;
            return NULL;
        }
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

void MDbQueryRecord::InsertData(const string &tableName,const map<string, pair<TC_Mysql::FT, string>> &columns)
{
    string sql = GetMysqlObject()->buildInsertSQL(tableName, columns);
    LOG->debug() << "Insert report info: " << sql << endl;
    MDbExecuteRecord::getInstance()->AddExecuteSql(sql);
}

// TC_Mysql::MysqlData MDbQueryRecord::QueryData(const string &tableName, const vector<string> &columns, const string &conditions)
// {
//     string sql = buildSelectSQL(tableName, columns, conditions);
//     LOG->debug() << "Select report info: " << sql << endl;

// }

bool MDbExecuteRecord::Init()
{
    _tcDbConfig._port = SConfig::getInstance()->usPort;
    _tcDbConfig._host = SConfig::getInstance()->strDbHost;
    _tcDbConfig._user = SConfig::getInstance()->strUserName;
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


void MDbExecuteRecord::AddExecuteSql(const string& strSql)
{
    TC_ThreadLock::Lock lock(_pLocker);
    _qeWaitExeSql.push(strSql);
}

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
            LOG->error() << "MDbExcuteRecord::Excute:" << strSql
                         << " exception:" << e.what() << endl;
            TarsRemoteNotify::getInstance()->report("MysqlExcuteError");
        }
    }
}

void MDbExecuteRecord::run()
{
    while(true)
    {
        Execute();
        usleep(100000);
    }
}
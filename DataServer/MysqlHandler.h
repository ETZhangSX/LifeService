#ifndef _LIFESERVICE_MYSQLHANDLER_
#define _LIFESERVICE_MYSQLHANDLER_

#include "util/tc_thread.h"
#include "util/tc_mysql.h"
#include "util/tc_singleton.h"
#include "util/tc_shared_ptr.h"
#include "util/tc_thread_rwlock.h"
#include "util/tc_lock.h"
#include "util/tc_monitor.h"
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <map>
#include "DataService.h"

using namespace tars;

class MDbQueryRecord: public TC_Singleton<MDbQueryRecord>
{
public:
    tars::TC_Mysql * GetMysqlObject();

    void InsertData(const std::string &tableName,const vector<LifeService::Column> &columns);
    // TC_Mysql::MysqlData QueryData(const std::string &tableName, const vector<std::string> &columns, const std::string &conditions);
private:
    tars::TC_DBConf                     _tcDbConfig;
    tars::TC_SharedPtr<tars::TC_Mysql>  _pMysql;

    map<unsigned int, tars::TC_Mysql *> MysqlMap;
};

class MDbExecuteRecord: public tars::TC_Thread, public tars::TC_Singleton<MDbExecuteRecord>
{
public:
    bool Init();
    void AddExecuteSql(const string &strSql);
    void Execute();

protected:
    virtual void run();

private:
    tars::TC_DBConf                     _tcDbConfig;
    queue<string>                       _qeWaitExeSql;
    tars::TC_SharedPtr<tars::TC_Mysql>  _pMysql;
    tars::TC_ThreadLock                 _pLocker;
};

#endif
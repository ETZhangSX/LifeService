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

/**
 * @brief MySQL工具单件类，用于获取TC_Mysql对象
 */
class MDbQueryRecord: public TC_Singleton<MDbQueryRecord>
{
public:
    /** 
     * @brief 获取所在线程的TC_Mysql对象
     * @return TC_Mysql对象
     */
    tars::TC_Mysql * GetMysqlObject();

    /**
     * @brief 插入数据
     * @param tableName string 表名
     * @param columns   vector 列
     */
    void InsertData(const std::string &tableName,const vector<LifeService::Column> &columns);
private:
    
    tars::TC_DBConf _tcDbConfig;                        // 数据库配置接口
    map<unsigned int, tars::TC_Mysql *> MysqlMap;       // 线程id对应的TC_Mysql对象
};

/**
 * @brief MySQL工具单件类，用于顺序执行SQL语句，所有通过该类的执行操作，
 *        对应的SQL语句都会放到队列中，定期执行队列中的所有SQL语句，因此
 *        无法获取SQL语句执行状态，执行错误通过LOG打印和向Notify节点汇报
 */
class MDbExecuteRecord: public tars::TC_Thread, public tars::TC_Singleton<MDbExecuteRecord>
{
public:
    /**
     * @brief 类初始化函数
     */
    bool Init();
    /**
     * @brief 添加要执行的SQL语句
     */
    void AddExecuteSql(const string &strSql);
    /**
     * @brief 执行队列中所有的SQL语句
     */
    void Execute();

protected:
     /**
     * @brief 定期执行Execute
     */
    virtual void run();

private:
    tars::TC_DBConf                     _tcDbConfig;    // 数据库配置接口
    queue<string>                       _qeWaitExeSql;  // 待执行SQL语句队列
    tars::TC_SharedPtr<tars::TC_Mysql>  _pMysql;        // TC_Mysql对象
    tars::TC_ThreadLock                 _pLocker;       // 线程锁
};

#endif
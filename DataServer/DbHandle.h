#ifndef _LIFESERVICE_DBHANDLE_
#define _LIFESERVICE_DBHANDLE_

#include "util/tc_singleton.h"
#include "util/tc_thread_rwlock.h"
#include "util/tc_shared_ptr.h"
#include "util/tc_thread.h"
#include "util/tc_mysql.h"
#include <vector>
#include <string>
#include <map>
#include "DataService.h"

using namespace std;

class UserHandle: public tars::TC_Singleton<UserHandle>
{
public:
    /**
     * @brief 从数据加载数据到内存
     */
    int LoadDataFromDb();
    /**
     * @brief 新增数据到内存中
     * @param wx_id     用户wx_id
     * @param userInfo  用户信息
     */
    int InsertUserData(const string &wx_id, const LifeService::UserInfo &userInfo);
    bool hasUser(const string &wx_id);
public:
    map<string, LifeService::UserInfo>  mUserInfo;
    map<tars::Int32, string>            mGroupInfo;
private:
    tars::TC_ThreadLock _pLocker;
};

#endif
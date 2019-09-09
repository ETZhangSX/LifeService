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

// 用户
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
    int InsertUserData(const std::string &wx_id, const LifeService::UserInfo &userInfo);
    bool hasUser(const std::string &wx_id);
public:
    map<string, LifeService::UserInfo>  mUserInfo;
    map<tars::Int32, string>            mGroupInfo;
private:
    tars::TC_ThreadLock _pLocker;
};

// 社团
class ClubHandle: public tars::TC_Singleton<ClubHandle>
{
public:
    /**
     * @brief 从数据加载数据到内存
     */
    int LoadDataFromDb();
    /**
     * @brief 新建社团信息
     */
    int InsertClubData(const LifeService::ClubInfo &clubInfo);
    int GetClubList(const int &index, const int &batch, const std::string &wx_id, int &nextIndex, vector<LifeService::ClubInfo> &clubInfoList);
    int GetApplyListByClubId(const std::string &club_id, int index, int batch, int apply_status, int &nextIndex, vector<LifeService::ApplyInfo> &applyList);
    int GetApplyListByUserId(const std::string &wx_id, int index, int batch, int apply_status, int &nextIndex, vector<LifeService::ApplyInfo> &applyList);
    int SetApplyStatus(const std::string &wx_id, const std::string &club_id, int apply_status);
    int DeleteApply(const std::string &wx_id, const std::string &club_id);
public:
    map<string, int> mClub;
    vector<LifeService::ClubInfo> vClubInfo;
private:
    tars::TC_ThreadLock _pLocker;
};

// 活动
class ActivityHandle: public tars::TC_Singleton<ActivityHandle>
{
public:
    int GetActivityList(const int &index, const int &batch, const std::string &wx_id, const std::string &club_id, int &nextIndex, vector<map<std::string, std::string>> &activityList);
    int DeleteActivity(const std::string &activity_id);
};

// 表白墙
class MsgWallHandle: public tars::TC_Singleton<MsgWallHandle>
{
public:
    int InsertMessage(const LifeService::Message &msg);
    int GetMsgList(const int &index, const int &batch, const std::string &date, const std::string wx_id, int &nextIndex, vector<LifeService::Message> &msgList);
    int AddLike(const std::string &message_id);
    int GetLike(const std::string &message_id, int &like_count);
};

#endif
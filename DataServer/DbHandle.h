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

// 用户信息操作类
class UserHandle: public tars::TC_Singleton<UserHandle>
{
public:
    /**
     * @brief 从数据库加载数据到内存
     */
    int LoadDataFromDb();
    // 插入用户信息
    int InsertUserData(const std::string &wx_id, const LifeService::UserInfo &userInfo);
    // 判断用户是否存在
    bool hasUser(const std::string &wx_id);
public:
    // 用户信息
    map<string, LifeService::UserInfo>  mUserInfo;
    // 权限组信息
    map<tars::Int32, string>            mGroupInfo;
private:
    tars::TC_ThreadLock _pLocker;
};

// 社团信息操作类
class ClubHandle: public tars::TC_Singleton<ClubHandle>
{
public:
    /**
     * @brief 从数据库加载数据到内存
     */
    int LoadDataFromDb();
    // 插入社团管理者
    int InsertClubManager(const std::string &wx_id, const std::string &club_id);
    // 插入社团信息
    int InsertClubData(LifeService::ClubInfo clubInfo, std::string &club_id);
    // 获取社团列表
    int GetClubList(int index, int batch, const std::string &wx_id, int &nextIndex, vector<LifeService::ClubInfo> &clubInfoList);
    // 获取管理社团列表
    int GetManagerClubList(int index, int batch, const std::string &wx_id, int &nextIndex, vector<LifeService::ClubInfo> &clubInfoList);
    // 获取特定社团的申请
    int GetApplyListByClubId(const std::string &club_id, int index, int batch, int apply_status, int &nextIndex, vector<LifeService::ApplyInfo> &applyList);
    // 获取特定用户的申请
    int GetApplyListByUserId(const std::string &wx_id, int index, int batch, int apply_status, int &nextIndex, vector<LifeService::ApplyInfo> &applyList);
    // 设置申请状态
    int SetApplyStatus(const std::string &wx_id, const std::string &club_id, int apply_status);
    // 删除申请
    int DeleteApply(const std::string &wx_id, const std::string &club_id);
public:
    // 存储club_id对应的vClubInfo下标
    map<string, int> mClub;
    // 社团信息
    vector<LifeService::ClubInfo> vClubInfo;
private:
    tars::TC_ThreadLock _pLocker;
};

// 活动信息操作类
class ActivityHandle: public tars::TC_Singleton<ActivityHandle>
{
public:
    int CreateActivity();
    // 获取活动列表
    int GetActivityList(const int &index, const int &batch, const std::string &wx_id, const std::string &club_id, int &nextIndex, vector<map<std::string, std::string>> &activityList);
    // 更新活动信息
    int UpdateActivity(const LifeService::ActivityInfo &activityInfo);
    // 删除活动
    int DeleteActivity(const std::string &activity_id);
    // 获取活动参与记录
    int GetActivityRecords(int index, int batch, const std::string &activity_id, int &nextIndex, vector<LifeService::ActivityRecord> &recordList);
};

// 表白墙信息操作类
class MsgWallHandle: public tars::TC_Singleton<MsgWallHandle>
{
public:
    // 插入新留言信息
    int InsertMessage(const LifeService::Message &msg);
    // 获取留言列表
    int GetMsgList(const int &index, const int &batch, const std::string &date, const std::string wx_id, int &nextIndex, vector<LifeService::Message> &msgList);
    // 点赞
    int AddLike(const std::string &message_id);
    // 获取点赞数
    int GetLike(const std::string &message_id, int &like_count);
};

#endif
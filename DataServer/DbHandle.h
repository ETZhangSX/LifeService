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

/**
 * @brief 用户信息操作类
 */
class UserHandle: public tars::TC_Singleton<UserHandle>
{
public:
    /**
     * @brief 从数据库加载数据到内存
     */
    int LoadDataFromDb();
    // 插入用户信息
    int InsertUserData(const std::string &wx_id, const LifeService::UserInfo &userInfo);
    
    /**线程安全的数据获取接口, 避免直接读取数据**/ 
    // 判断用户是否存在
    bool hasUser(const std::string &wx_id);
    // 判断手机号是否存在
    bool hasPhone(const std::string &phone);
    // 通过wx_id获取用户姓名
    std::string getUserNameById(const std::string &wx_id);
    // 通过wx_id获取用户信息对象
    LifeService::UserInfo getUserInfoById(const std::string &wx_id);
public:
    // 用户信息
    map<string, LifeService::UserInfo>  mUserInfo;
    // 手机号码到用户id的map
    map<string, string> mPhoneToWxId;
    // 权限组信息
    map<tars::Int32, std::string> mGroupInfo;
private:
    // 读写锁
    tars::TC_ThreadRWLocker _pRWLocker;
};

/**
 * @brief 社团信息操作类
 */
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
    // 获取社团管理者记录数
    int GetClubManagerCount(const std::string &wx_id, const std::string &club_id);
    // 删除社团
    int DeleteClub(const std::string &club_id);
    // 删除管理员
    int DeleteClubManager(const std::string &wx_id, const std::string &club_id);
    // 插入社团申请信息
    int InsertApplyData(const std::string &wx_id, const std::string &club_id);
    // 获取特定社团的申请
    int GetApplyListByClubId(const std::string &club_id, int index, int batch, int apply_status, int &nextIndex, vector<LifeService::ApplyInfo> &applyList);
    // 获取特定用户的申请
    int GetApplyListByUserId(const std::string &wx_id, int index, int batch, int apply_status, int &nextIndex, vector<LifeService::ApplyInfo> &applyList);
    // 设置申请状态
    int SetApplyStatus(const std::string &wx_id, const std::string &club_id, int apply_status);
    // 获取社团申请数
    int GetApplyCount(const std::string &wx_id, const std::string &club_id, int apply_status);
    // 删除申请
    int DeleteApply(const std::string &wx_id, const std::string &club_id);
public:
    // 通过id获取club名
    std::string getClubNameById(const std::string &club_id);
    // 存储club_id对应的vClubInfo下标
    map<string, int> mClub;
    // 社团信息
    vector<LifeService::ClubInfo> vClubInfo;
private:
    tars::TC_ThreadRWLocker _pRWLocker;
};

/**
 * @brief 活动信息操作类
 */
class ActivityHandle: public tars::TC_Singleton<ActivityHandle>
{
public:
    // 插入活动信息
    int InsertActivityData(const LifeService::ActivityInfo activityInfo);
    // 获取活动列表
    int GetActivityList(int index, int batch, const std::string &wx_id, const std::string &club_id, int &nextIndex, vector<map<std::string, std::string>> &activityList);
    // 更新活动信息
    int UpdateActivity(const LifeService::ActivityInfo &activityInfo);
    // 删除活动
    int DeleteActivity(const std::string &activity_id);
    // 获取活动信息
    int GetActivityInfo(const std::string &activity_id, LifeService::ActivityInfo &activityInfo);
    // 插入活动记录
    int InsertActivityRecord(const std::string &wx_id, const std::string &activity_id);
    // 获取活动参与记录
    int GetActivityRecords(int index, int batch, const std::string &activity_id, int &nextIndex, vector<LifeService::ActivityRecord> &recordList);
    // 获取活动记录数
    int GetRecordCount(const std::string &wx_id, const std::string &activity_id);
};

/**
 * @brief 表白墙信息操作类
 */
class MsgWallHandle: public tars::TC_Singleton<MsgWallHandle>
{
public:
    // 插入新留言信息
    int InsertMessage(const LifeService::Message &msg);
    // 获取留言列表
    int GetMsgList(int index, int batch, const std::string &date, const std::string wx_id, int &nextIndex, vector<LifeService::Message> &msgList);
    // 点赞
    int AddLike(const std::string &message_id);
    // 获取点赞数
    int GetLike(const std::string &message_id, int &like_count);
};

#endif
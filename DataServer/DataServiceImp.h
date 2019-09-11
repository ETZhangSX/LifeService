#ifndef _DataServiceImp_H_
#define _DataServiceImp_H_

#include "servant/Application.h"
#include "DataService.h"
#include <map>

/**
 *
 *
 */
class DataServiceImp : public LifeService::DataService
{
public:
    /**
     *
     */
    virtual ~DataServiceImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     * @brief 判断用户是否存在
     */
    virtual int hasUser(const std::string &wx_id, bool &sRsp, tars::TarsCurrentPtr current);

    /**
     * @brief 创建用户
     */
    virtual int createUser(const std::string &wx_id, const LifeService::UserInfo &userInfo, tars::TarsCurrentPtr current);
    
    /**
     * @brief 获取用户信息
     */
    virtual int getUserInfo(const std::string &wx_id, LifeService::UserInfo &sRsp, tars::TarsCurrentPtr current);

    /**
     * @brief 获取分组信息
     */
    virtual int getGroupInfo(map<tars::Int32, std::string> &groupInfo, tars::TarsCurrentPtr current);

    /**
     * @brief 通过用户id查询用户分组权限
     */
    virtual int getGroupByUserId(const std::string &wx_id, std::string &group, tars::TarsCurrentPtr current);

    /**
     * @brief 通过分组id查询分组
     */
    virtual int getGroupByGroupId(tars::Int32 groupId, std::string &group, tars::TarsCurrentPtr current);
    
    /**
     * @brief 创建社团
     */
    virtual int createClub(const LifeService::ClubInfo &clubInfo, tars::Int32 &iRetCode, tars::TarsCurrentPtr current);

    /**
     * @brief 获取社团列表
     */
    virtual int getClubList(tars::Int32 index, tars::Int32 batch, const std::string &wx_id, tars::Int32 &nextIndex, vector<LifeService::ClubInfo> &clubInfoList, tars::TarsCurrentPtr current);
    virtual int getManagerClubList(tars::Int32 index, tars::Int32 batch, const std::string &wx_id, tars::Int32 &nextIndex, vector<LifeService::ClubInfo> &clubInfoList, tars::TarsCurrentPtr current);
    virtual int getApplyListByClubId(const std::string &club_id, tars::Int32 index, tars::Int32 batch, tars::Int32 apply_status, tars::Int32 &nextIndex, vector<LifeService::ApplyInfo> &applyList, tars::TarsCurrentPtr current);
    virtual int getApplyListByUserId(const std::string &wx_id, tars::Int32 index, tars::Int32 batch, tars::Int32 apply_status, tars::Int32 &nextIndex, vector<LifeService::ApplyInfo> &applyList, tars::TarsCurrentPtr current);
    virtual int setApplyStatus(const std::string &wx_id, const std::string &club_id, tars::Int32 apply_status, tars::Int32 &iRetCode, tars::TarsCurrentPtr current);
    virtual int deleteApply(const std::string &wx_id, const std::string &club_id, tars::Int32 &iRetCode, tars::TarsCurrentPtr current);

    // virtual int createActivity(const LifeService::ActivityInfo &activityInfo, tars::Int32 &iRetCode, tars::TarsCurrentPtr current);
    /**
     * @brief 获取活动列表
     */
    virtual int getActivityList(tars::Int32 index, tars::Int32 batch, const std::string &wx_id, const std::string &club_id, tars::Int32 &nextIndex, vector<map<std::string, std::string>> &activityList, tars::TarsCurrentPtr current);
    virtual int updateActivity(const LifeService::ActivityInfo &activityInfo, tars::Int32 &iRetCode, tars::TarsCurrentPtr current);
    virtual int deleteActivity(const std::string &activity_id, tars::Int32 &iRetCode, tars::TarsCurrentPtr current);
    /**
     * @brief 获取活动详情
     */
    // virtual int getActivityDetail(std::string activityId, LifeService::ActivityInfo activityInfo, tars::TarsCurrentPtr current);
    virtual int getActivityRecords(const std::string &activity_id, vector<LifeService::ActivityRecord> &recordList, tars::TarsCurrentPtr current);
    virtual int deleteActivityRecord(const std::string &activity_id, const std::string &wx_id, tars::Int32 &iRetcode, tars::TarsCurrentPtr current);
    /**
     * @brief 插入留言
     */
    virtual int insertMessage(const LifeService::Message &msg, tars::TarsCurrentPtr current);

    virtual int getMsgList(tars::Int32 index, const std::string &date, const std::string &wx_id, tars::Int32 &nextIndex, vector<LifeService::Message> &msgList, tars::TarsCurrentPtr current);

    virtual int addLike(const std::string &message_id, tars::TarsCurrentPtr current);

    virtual int getLike(const std::string &message_id, tars::Int32 &like_count, tars::TarsCurrentPtr current);
    /**
     * @brief 向数据库插入数据
     */
    virtual int insertData(const std::string &sTableName, const vector<LifeService::Column> &sColumns, tars::TarsCurrentPtr current);
    
    /**
     * @brief 查询数据
     */
    virtual int queryData(const std::string &sTableName, const vector<std::string> &sColumns, const std::string &sCondition, vector<map<std::string, std::string>> &sRsp, tars::TarsCurrentPtr current);

    virtual int getRecordCount(const std::string &sTableName, const std::string &sCondition, tars::Int32 &iCount, tars::TarsCurrentPtr current);
};
/////////////////////////////////////////////////////
#endif

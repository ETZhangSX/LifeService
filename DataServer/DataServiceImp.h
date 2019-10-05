#ifndef _DataServiceImp_H_
#define _DataServiceImp_H_

#include "servant/Application.h"
#include "DataService.h"
#include <map>

/**
 * @brief DataService实现类
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
     * @param wx_id     用户微信id
     * @out   userExist true表示存在用户; false表示用户不存在
     */
    virtual int hasUser(const std::string &wx_id, bool &userExist, tars::TarsCurrentPtr current);

    /**
     * @brief 判断手机号是否存在
     * @param phone      手机号
     * @out   phoneExist true表示手机号存在; false表示不存在
     */
    virtual int hasPhone (const std::string &phone, bool &phoneExist, tars::TarsCurrentPtr current);
    /**
     * @brief 创建用户
     * @param wx_id    用户微信id
     * @param userInfo 用户信息, UserInfo(tars文件中定义)
     */
    virtual int createUser(const std::string &wx_id, const LifeService::UserInfo &userInfo, tars::TarsCurrentPtr current);
    
    /**
     * @brief 获取用户信息
     * @param wx_id    用户微信id
     * @out   userInfo 用户信息, UserInfo(tars文件中定义)
     */
    virtual int getUserInfo(const std::string &wx_id, LifeService::UserInfo &userInfo, tars::TarsCurrentPtr current);

    /**
     * @brief 获取分组信息
     * @out   groupInfo 用户权限组(包含所有group_id对应的权限类型)
     */
    virtual int getGroupInfo(map<tars::Int32, std::string> &groupInfo, tars::TarsCurrentPtr current);

    /**
     * @brief 创建社团管理员
     * @param wx_id   用户id
     * @param club_id 社团id
     */
    virtual int createClubManager(const std::string &wx_id, const std::string &club_id, tars::TarsCurrentPtr current);
    
    /**
     * @brief 创建社团
     * @param clubInfo 社团信息, ClubInfo(tars文件中定义)
     * @out   club_id  返回创建社团的id
     */
    virtual int createClub(const LifeService::ClubInfo &clubInfo, std::string &club_id, tars::TarsCurrentPtr current);

    /**
     * @brief 获取社团列表
     * @param index        返回信息索引, 传入0获取第一页, 每次调用传入上一次返回的nextIndex
     * @param batch        返回的信息条数
     * @param wx_id        用户微信id
     * @out   nextIndex    下一页索引
     * @out   clubInfoList 社团信息列表
     */
    virtual int getClubList(tars::Int32 index, tars::Int32 batch, const std::string &wx_id, tars::Int32 &nextIndex, vector<LifeService::ClubInfo> &clubInfoList, tars::TarsCurrentPtr current);
    
    /**
     * @brief 获取管理员社团列表
     * @param index        返回信息索引, 传入0获取第一页, 每次调用传入上一次返回的nextIndex
     * @param batch        返回的信息条数
     * @param wx_id        用户微信id
     * @out   nextIndex    下一页索引
     * @out   clubInfoList 社团信息列表
     */
    virtual int getManagerClubList(tars::Int32 index, tars::Int32 batch, const std::string &wx_id, tars::Int32 &nextIndex, vector<LifeService::ClubInfo> &clubInfoList, tars::TarsCurrentPtr current);
    
    /**
     * @brief 获取社团管理者记录数
     * @param wx_id   用户id
     * @param club_id 社团id
     * @out   count   记录数
     */
    virtual int getClubManagerCount(const std::string &wx_id, const std::string &club_id, tars::Int32 &count, tars::TarsCurrentPtr current);
    
    /**
     * @brief 删除社团
     * @param club_id    社团id
     * @out   affectRows 影响记录数
     */
    virtual int deleteClub(const std::string &club_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current);
    
    /**
     * @brief 删除社团管理
     * @param wx_id      用户id
     * @param club_id    社团id
     * @out   affectRows 影响记录数
     */
    virtual int deleteClubManager(const std::string &wx_id, const std::string &club_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current);

    /**
     * @brief 创建社团申请
     * @param wx_id   用户微信id
     * @param club_id 社团id
     */
    virtual int createApply(const std::string &wx_id, const std::string &club_id, tars::TarsCurrentPtr current);
    
    /**
     * @brief 通过club_id获取社团申请列表
     * @param club_id      社团id
     * @param index        返回信息索引, 传入0获取第一页, 每次调用传入上一次返回的nextIndex
     * @param batch        返回的信息条数
     * @param apply_status 申请状态, 用于筛选特定状态的申请
     * @out   nextIndex    下一页索引
     * @out   applyList    申请信息列表, ApplyInfo(tars文件中定义)
     */
    virtual int getApplyListByClubId(const std::string &club_id, tars::Int32 index, tars::Int32 batch, tars::Int32 apply_status, tars::Int32 &nextIndex, vector<LifeService::ApplyInfo> &applyList, tars::TarsCurrentPtr current);
    
    /**
     * @brief 通过用户id获取社团列表
     * @param wx_id        用户微信id
     * @param index        返回信息索引, 传入0获取第一页, 每次调用传入上一次返回的nextIndex
     * @param batch        返回的信息条数
     * @param apply_status 申请状态, 用于筛选特定状态的申请
     * @out   nextIndex    下一页索引
     * @out   applyList    申请信息列表, ApplyInfo(tars文件中定义)
     */
    virtual int getApplyListByUserId(const std::string &wx_id, tars::Int32 index, tars::Int32 batch, tars::Int32 apply_status, tars::Int32 &nextIndex, vector<LifeService::ApplyInfo> &applyList, tars::TarsCurrentPtr current);
    
    /**
     * @brief 设置申请状态
     * @param wx_id        用户微信id
     * @param club_id      社团id
     * @param apply_status 申请状态
     * @out   affectRows   影响行数
     */
    virtual int setApplyStatus(const std::string &wx_id, const std::string &club_id, tars::Int32 apply_status, tars::Int32 &affectRows, tars::TarsCurrentPtr current);
    
    /**
     * @brief 获取社团申请数量
     * @param wx_id        用户id
     * @param club_id      社团id
     * @param apply_status 申请状态,为正数时返回对应状态记录数;为负数时返回除其绝对值外的状态记录数
     * @out   count        记录数
     */
    virtual int getApplyCount(const std::string &wx_id, const std::string &club_id, tars::Int32 apply_status, tars::Int32 &count, tars::TarsCurrentPtr current);
    /**
     * @brief 删除申请
     * @param wx_id      用户微信id
     * @param club_id    社团id
     * @out   affectRows 影响行数
     */
    virtual int deleteApply(const std::string &wx_id, const std::string &club_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current);

    /**
     * @brief 新建活动
     * @param activityInfo 活动信息, ActivityInfo(在tars文件中定义)
     */
    virtual int createActivity(const LifeService::ActivityInfo &activityInfo, tars::TarsCurrentPtr current);
    
    /**
     * @brief 获取活动列表
     * @param index     返回信息索引, 传入0获取第一页, 每次调用传入上一次返回的nextIndex
     * @param batch     返回的信息条数
     * @param wx_id     微信id
     * @param club_id   社团id
     * @out   nextIndex 下一页索引
     */
    virtual int getActivityList(tars::Int32 index, tars::Int32 batch, const std::string &wx_id, const std::string &club_id, tars::Int32 &nextIndex, vector<map<std::string, std::string>> &activityList, tars::TarsCurrentPtr current);
    
    /**
     * @brief 更新活动信息
     * @param activityInfo 活动信息(tars文件中定义), 只需传入activity_id, name, start_time, stop_time, registry_start_time, registry_stop_time, content。只修改上述除activity_id外的信息
     * @out   affectRows   影响行数
     */
    virtual int updateActivity(const LifeService::ActivityInfo &activityInfo, tars::Int32 &affectRows, tars::TarsCurrentPtr current);
    
    /**
     * @brief 删除活动
     * @param activity_id 活动id
     * @out   affectRows  影响行数
     */
    virtual int deleteActivity(const std::string &activity_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current);
    
    /**
     * @brief 获取活动详情
     * @param activityId   活动id
     * @param activityInfo 活动信息
     */
    virtual int getActivityInfo(const std::string &activity_id, LifeService::ActivityInfo &activityInfo, tars::TarsCurrentPtr current);
    
    /**
     * @brief 新建活动记录
     * @param wx_id       用户微信id
     * @param activity_id 活动id
     */
    virtual int createActivityRecord(const std::string &wx_id, const std::string &activity_id, tars::TarsCurrentPtr current);

    /**
     * @brief 获取活动记录
     * @param index       返回信息索引, 传入0获取第一页, 每次调用传入上一次返回的nextIndex
     * @param batch       返回的信息条数
     * @param activity_id 活动id
     * @out   nextIndex   下一页索引
     * @out   recordList  活动报名记录列表, ActivityRecord在tars文件中定义
     */
    virtual int getActivityRecords(tars::Int32 index, tars::Int32 batch, const std::string &activity_id, tars::Int32 &nextIndex, vector<LifeService::ActivityRecord> &recordList, tars::TarsCurrentPtr current);
    
    /**
     * @brief 获取活动记录数
     * @param wx_id       用户id
     * @param activity_id 活动id
     * @out   count       记录数
     */
    virtual int getRecordCount(const std::string &wx_id, const std::string &activity_id, tars::Int32 &count, tars::TarsCurrentPtr current);

    /**
     * @brief 删除活动记录
     * @param activity_id 活动id
     * @param wx_id       用户微信id
     * @out   affectRows  影响行数
     */
    virtual int deleteActivityRecord(const std::string &activity_id, const std::string &wx_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current);
    /**
     * @brief 插入留言
     * @param msg 表白墙留言信息, Message在tars文件中定义
     */
    virtual int insertMessage(const LifeService::Message &msg, tars::TarsCurrentPtr current);

    /**
     * @brief 获取留言列表
     * @param index     返回信息索引, 传入0获取第一页, 每次调用传入上一次返回的nextIndex
     * @param date      日期, 为空字符串时不对日期进行筛选, 格式YYYY-MM-DD
     * @param wx_id     用户微信id
     * @out   nextIndex 下一页索引
     * @out   msgList   留言列表
     */
    virtual int getMsgList(tars::Int32 index, const std::string &date, const std::string &wx_id, tars::Int32 &nextIndex, vector<LifeService::Message> &msgList, tars::TarsCurrentPtr current);

    /**
     * @brief 点赞+1
     * @param message_id 留言id
     */
    virtual int addLike(const std::string &message_id, tars::TarsCurrentPtr current);

    /**
     * @brief 获取点赞数
     * @param message_id 留言id
     * @out   like_count 点赞数
     */
    virtual int getLike(const std::string &message_id, tars::Int32 &like_count, tars::TarsCurrentPtr current);
    
    /**
     * @brief 向数据库插入数据, 取消权限过高的接口
     * @param sTableName 表名
     * @param vColumns   列名, 值。Column在tars文件中定义, 其中DBInt字段为true时代表不需要转译, false代表需要转译
     */
    // virtual int insertData(const std::string &sTableName, const vector<LifeService::Column> &vColumns, tars::TarsCurrentPtr current);
    
    /**
     * @brief 查询数据, 取消权限过高的接口
     * @param sTableName 表名
     * @param vColumns   列名
     * @param sCondition where域条件
     * @out   vmpResults 查询结果, 类型为map<列名,值> 
     */
    // virtual int queryData(const std::string &sTableName, const vector<std::string> &vColumns, const std::string &sCondition, vector<map<std::string, std::string>> &vmpResults, tars::TarsCurrentPtr current);
};
/////////////////////////////////////////////////////
#endif

#include <algorithm>
#include "DataServiceImp.h"
#include "servant/Application.h"
#include "DbHandle.h"
#include "MysqlHandler.h"
#include "util.h"

using namespace std;

//////////////////////////////////////////////////////
void DataServiceImp::initialize()
{
    //initialize servant here:
    //...
}

//////////////////////////////////////////////////////
void DataServiceImp::destroy()
{
    //destroy servant here:
    //...
}

//////////////////////////////////////////////////////
int DataServiceImp::hasUser(const string &wx_id, bool &userExist, tars::TarsCurrentPtr current)
{
    userExist = UserHandle::getInstance()->hasUser(wx_id);
    if (userExist)
        LOG->debug() << "DataServiceImp::hasUser: User " << wx_id << " exist" << endl;
    else
        LOG->debug() << "DataServiceImp::hasUser: User " << wx_id << " not exist" << endl;
    
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::createUser(const string &wx_id, const LifeService::UserInfo &userInfo, tars::TarsCurrentPtr current)
{
    if (UserHandle::getInstance()->hasUser(wx_id))
    {
        LOG->error() << "createUser: User exist" << endl;
        return -1;
    }
    
    UserHandle::getInstance()->InsertUserData(wx_id, userInfo);
    LOG->debug() << "Create user successfully" << endl;
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getUserInfo(const string &wx_id, LifeService::UserInfo &sRsp, tars::TarsCurrentPtr current)
{
    if (UserHandle::getInstance()->hasUser(wx_id))
    {
        sRsp = UserHandle::getInstance()->mUserInfo[wx_id];
        LOG->debug() << "getUserInfo: " << wx_id << " successfully" << endl;
        return 0;
    }
    LOG->error() << "getUserInfo: User not exist." << endl;
    return -1;
}

//////////////////////////////////////////////////////
int DataServiceImp::getGroupInfo(map<tars::Int32, string> &groupInfo, tars::TarsCurrentPtr current)
{
    groupInfo = UserHandle::getInstance()->mGroupInfo;
    LOG->debug() << "getGroupInfo successfully" << endl;
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getGroupByUserId(const string &wx_id, string &group, tars::TarsCurrentPtr current)
{
    if (UserHandle::getInstance()->hasUser(wx_id))
    {
        int group_id = UserHandle::getInstance()->mUserInfo[wx_id].group;
        if (UserHandle::getInstance()->mGroupInfo.count(group_id) == 0) 
        {
            LOG->error() << "DataServiceImp::getGroupByUserId: No match group" << endl;
            return -1;
        }
        group = UserHandle::getInstance()->mGroupInfo[group_id];
        return 0;
    }
    LOG->error() << "DataServiceImp::getGroupByUserId: User does not exist." << endl;
    return -1;
}

//////////////////////////////////////////////////////
int DataServiceImp::getGroupByGroupId(tars::Int32 groupId, string &group, tars::TarsCurrentPtr current)
{
    if (UserHandle::getInstance()->mGroupInfo.count(groupId) == 0)
    {
        LOG->error() << "DataServiceImp::getGroupByGroupId: No match group" << endl;
        return -1;
    }
    group = UserHandle::getInstance()->mGroupInfo[groupId];
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::createClub(const LifeService::ClubInfo &clubInfo, tars::Int32 &iRetCode, tars::TarsCurrentPtr current)
{
    ClubHandle::getInstance()->InsertClubData(clubInfo);
    iRetCode = 0;
    LOG->debug() << "Create Club Successfully" << endl;
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getClubList(tars::Int32 index, tars::Int32 batch, const string &wx_id, tars::Int32 &nextIndex, vector<LifeService::ClubInfo> &clubInfoList, tars::TarsCurrentPtr current)
{
    int ret = ClubHandle::getInstance()->GetClubList(index, batch, wx_id, nextIndex, clubInfoList);
    return ret;
}

//////////////////////////////////////////////////////
int DataServiceImp::getManagerClubList(tars::Int32 index, tars::Int32 batch, const string &wx_id, tars::Int32 &nextIndex, vector<LifeService::ClubInfo> &clubInfoList, tars::TarsCurrentPtr current)
{
    int ret = ClubHandle::getInstance()->GetManagerClubList(index, batch, wx_id, nextIndex, clubInfoList);
    return ret;
}

//////////////////////////////////////////////////////
int DataServiceImp::getApplyListByClubId(const string &club_id, tars::Int32 index, tars::Int32 batch, tars::Int32 apply_status, tars::Int32 &nextIndex, vector<LifeService::ApplyInfo> &applyList, tars::TarsCurrentPtr current)
{
    int ret = ClubHandle::getInstance()->GetApplyListByClubId(club_id, index, batch, apply_status, nextIndex, applyList);
    return ret;
}

//////////////////////////////////////////////////////
int DataServiceImp::getApplyListByUserId(const string &wx_id, tars::Int32 index, tars::Int32 batch, tars::Int32 apply_status, tars::Int32 &nextIndex, vector<LifeService::ApplyInfo> &applyList, tars::TarsCurrentPtr current)
{
    int ret = ClubHandle::getInstance()->GetApplyListByUserId(wx_id, index, batch, apply_status, nextIndex, applyList);
    return ret;
}

//////////////////////////////////////////////////////
int DataServiceImp::setApplyStatus(const string &wx_id, const string &club_id, tars::Int32 apply_status, tars::Int32 &iRetCode, tars::TarsCurrentPtr current)
{
    iRetCode = ClubHandle::getInstance()->SetApplyStatus(wx_id, club_id, apply_status);
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::deleteApply(const string &wx_id, const string &club_id, tars::Int32 &iRetCode, tars::TarsCurrentPtr current)
{
    iRetCode = ClubHandle::getInstance()->DeleteApply(wx_id, club_id);
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getActivityList(tars::Int32 index, tars::Int32 batch, const string &wx_id, const string &club_id, tars::Int32 &nextIndex, vector<map<string, string>> &activityList, tars::TarsCurrentPtr current)
{
    int ret = ActivityHandle::getInstance()->GetActivityList(index, batch, wx_id, club_id, nextIndex, activityList);
    return ret;
}

//////////////////////////////////////////////////////
int DataServiceImp::updateActivity(const LifeService::ActivityInfo &activityInfo, tars::Int32 &iRetCode, tars::TarsCurrentPtr current)
{
    iRetCode = ActivityHandle::getInstance()->UpdateActivity(activityInfo);
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::deleteActivity(const std::string &activity_id, tars::Int32 &iRetCode, tars::TarsCurrentPtr current)
{
    iRetCode = ActivityHandle::getInstance()->DeleteActivity(activity_id);
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getActivityRecords(const string &activity_id, vector<LifeService::ActivityRecord> &recordList, tars::TarsCurrentPtr current)
{
    string sSql = buildSelectSQL("activity_records", vector<string>{"user_id", "record_time"}, "`activity_id`=" + activity_id);
    TC_Mysql::MysqlData oResults;
    try
    {
        oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sSql);
    }
    catch (exception &e)
    {
        LOG->error() << "DataServiceImp::getActivityRecords error: " << e.what() << endl;
        return -1;
    }
    size_t oResultCount = oResults.size();

    for (size_t i = 0; i < oResultCount; i++)
    {
        LifeService::ActivityRecord record;
        record.wx_id = oResults[i]["user_id"];
        record.record_time = oResults[i]["record_time"];
        record.user_name = UserHandle::getInstance()->mUserInfo[record.wx_id].name;

        recordList.push_back(record);
    }

    LOG->debug() << "DataServiceImp::getActivityRecords Execute SQL: " << sSql << endl;

    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::deleteActivityRecord(const string &activity_id, const string &wx_id, tars::Int32 &iRetCode, tars::TarsCurrentPtr current)
{
    try
    {
        MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("activity_records", "where `user_id`='" + wx_id + "' and `activity_id`=" + activity_id);
    }
    catch(exception &e)
    {
        LOG->error() << "DataServiceImp::deleteActivityRecord error: " << e.what() << endl;
        return -1;
    }
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::insertMessage(const LifeService::Message &msg, tars::TarsCurrentPtr current)
{
    MsgWallHandle::getInstance()->InsertMessage(msg);
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getMsgList(tars::Int32 index, const string &date, const string &wx_id, tars::Int32 &nextIndex, vector<LifeService::Message> &msgList, tars::TarsCurrentPtr current)
{
    int batch = 6;
    int Ret = MsgWallHandle::getInstance()->GetMsgList(index, batch, date, wx_id, nextIndex, msgList);
    return Ret;
}

//////////////////////////////////////////////////////
int DataServiceImp::addLike(const string &message_id, tars::TarsCurrentPtr current)
{
    MsgWallHandle::getInstance()->AddLike(message_id);
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getLike(const string &message_id, tars::Int32 &like_count, tars::TarsCurrentPtr current)
{
    int Ret = MsgWallHandle::getInstance()->GetLike(message_id, like_count);
    return Ret;
}

//////////////////////////////////////////////////////
int DataServiceImp::insertData(const string &sTableName, const vector<LifeService::Column> &vColumns, tars::TarsCurrentPtr current)
{
    MDbQueryRecord::getInstance()->InsertData(sTableName, vColumns);
    LOG->debug() << "DataServiceImp::insertData Execute Table: " << sTableName << endl;
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::queryData(const string &sTableName, const vector<string> &vColumns, const string &sCondition, vector<map<string, string>> &vmpResults, tars::TarsCurrentPtr current)
{
    string sql = buildSelectSQL(sTableName, vColumns, sCondition);
    
    TC_Mysql::MysqlData mysql_data;

    try
    {
        mysql_data = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sql);
    }
    catch (exception &e)
    {
        LOG->error() << "DataServiceImp::queryData: " << e.what() << endl;
        return -1;
    }
    LOG->debug() << "DataServiceImp::queryData: Query Table: " << sTableName << endl;
    vmpResults = mysql_data.data();
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getRecordCount(const string &sTableName, const string &sCondition, tars::Int32 &iCount, tars::TarsCurrentPtr current)
{
    try
    {
        iCount = MDbQueryRecord::getInstance()->GetMysqlObject()->getRecordCount(sTableName, sCondition);
    }
    catch (exception &e)
    {
        LOG->error() << "DataServiceImp::getRecordCount: " << e.what() << endl;
        iCount = -1;
        return -1;
    }
    LOG->debug() << "DataServiceImp::getRecordCount Count Table: " << sTableName << " Condition: " << sCondition << endl;
    return 0;
}
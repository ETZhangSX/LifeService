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

int DataServiceImp::hasPhone(const string &phone, bool &phoneExist, tars::TarsCurrentPtr current)
{
    phoneExist = UserHandle::getInstance()->hasPhone(phone);
    if (phoneExist)
        LOG->debug() << "DataServiceImp::hasPhone: Phone " << phone << " exist" << endl;
    else
        LOG->debug() << "DataServiceImp::hasPhone: Phone " << phone << " not exist" << endl;
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::createUser(const string &wx_id, const LifeService::UserInfo &userInfo, tars::TarsCurrentPtr current)
{   
    int iret = UserHandle::getInstance()->InsertUserData(wx_id, userInfo);
    if (iret == 0)
    {
        LOG->debug() << "DataServiceImp::createUser: Create user:" << wx_id << " successfully" << endl;
        return 0;
    }
    TarsRemoteNotify::getInstance()->report("DataServiceImp::createUser:" + wx_id + " error");
    return -1;
}
//////////////////////////////////////////////////////

int DataServiceImp::getUserInfo(const string &wx_id, LifeService::UserInfo &userInfo, tars::TarsCurrentPtr current)
{
    if (UserHandle::getInstance()->hasUser(wx_id))
    {
        userInfo = UserHandle::getInstance()->getUserInfoById(wx_id);
        LOG->debug() << "DataServiceImp::getUserInfo: " << wx_id << " successfully" << endl;
        return 0;
    }
    LOG->error() << "DataServiceImp::getUserInfo: User not exist." << endl;
    return -1;
}
//////////////////////////////////////////////////////

int DataServiceImp::getGroupInfo(map<tars::Int32, string> &groupInfo, tars::TarsCurrentPtr current)
{
    groupInfo = UserHandle::getInstance()->mGroupInfo;
    LOG->debug() << "DataServiceImp::getGroupInfo successfully" << endl;
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::createClubManager(const string &wx_id, const string &club_id, tars::TarsCurrentPtr current)
{
    int iRet = ClubHandle::getInstance()->InsertClubManager(wx_id, club_id);
    if (iRet != 0)
        return -1;
    return 0;
}
//////////////////////////////////////////////////////
int DataServiceImp::createClub(const LifeService::ClubInfo &clubInfo, string &club_id, tars::TarsCurrentPtr current)
{
    club_id = "";
    int iret = ClubHandle::getInstance()->InsertClubData(clubInfo, club_id);
    if (0 == iret)
    {
        LOG->debug() << "DataServiceImp::createClub: Successful" << endl;
        return 0;
    }
    TarsRemoteNotify::getInstance()->report("DataServiceImp::createClub:" + club_id + " error");
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

int DataServiceImp::getClubManagerCount(const string &wx_id, const string &club_id, tars::Int32 &count, tars::TarsCurrentPtr current)
{
    count = ClubHandle::getInstance()->GetClubManagerCount(wx_id, club_id);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::deleteClub(const string &club_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current)
{
    affectRows = ClubHandle::getInstance()->DeleteClub(club_id);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::deleteClubManager(const string &wx_id, const string &club_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current)
{
    affectRows = ClubHandle::getInstance()->DeleteClubManager(wx_id, club_id);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::createApply(const string &wx_id, const string &club_id, tars::TarsCurrentPtr current)
{
    int ret = ClubHandle::getInstance()->InsertApplyData(wx_id, club_id);
    if (ret != 0) return -1;
    return 0;
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

int DataServiceImp::setApplyStatus(const string &wx_id, const string &club_id, tars::Int32 apply_status, tars::Int32 &affectRows, tars::TarsCurrentPtr current)
{
    affectRows = ClubHandle::getInstance()->SetApplyStatus(wx_id, club_id, apply_status);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::getApplyCount(const string &wx_id, const string &club_id, tars::Int32 apply_status, tars::Int32 &count, tars::TarsCurrentPtr current)
{
    count = ClubHandle::getInstance()->GetApplyCount(wx_id, club_id, apply_status);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::deleteApply(const string &wx_id, const string &club_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current)
{
    affectRows = ClubHandle::getInstance()->DeleteApply(wx_id, club_id);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::createActivity(const LifeService::ActivityInfo &activityInfo, tars::TarsCurrentPtr current)
{
    int ret = ActivityHandle::getInstance()->InsertActivityData(activityInfo);
    return ret;
}
//////////////////////////////////////////////////////

int DataServiceImp::getActivityList(tars::Int32 index, tars::Int32 batch, const string &wx_id, const string &club_id, tars::Int32 &nextIndex, vector<map<string, string>> &activityList, tars::TarsCurrentPtr current)
{
    int ret = ActivityHandle::getInstance()->GetActivityList(index, batch, wx_id, club_id, nextIndex, activityList);
    return ret;
}
//////////////////////////////////////////////////////

int DataServiceImp::updateActivity(const LifeService::ActivityInfo &activityInfo, tars::Int32 &affectRows, tars::TarsCurrentPtr current)
{
    affectRows = ActivityHandle::getInstance()->UpdateActivity(activityInfo);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::deleteActivity(const std::string &activity_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current)
{
    affectRows = ActivityHandle::getInstance()->DeleteActivity(activity_id);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::createActivityRecord(const string &wx_id, const string &activity_id, tars::TarsCurrentPtr current)
{
    int ret = ActivityHandle::getInstance()->InsertActivityRecord(wx_id, activity_id);
    if (ret != 0) return 300;
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::getActivityRecords(tars::Int32 index, tars::Int32 batch, const string &activity_id, tars::Int32 &nextIndex, vector<LifeService::ActivityRecord> &recordList, tars::TarsCurrentPtr current)
{
    int ret = ActivityHandle::getInstance()->GetActivityRecords(index, batch, activity_id, nextIndex, recordList);
    return ret;
}
//////////////////////////////////////////////////////

int DataServiceImp::getRecordCount(const string &wx_id, const string &activity_id, tars::Int32 &count, tars::TarsCurrentPtr current)
{
    count = ActivityHandle::getInstance()->GetRecordCount(wx_id, activity_id);
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::deleteActivityRecord(const string &activity_id, const string &wx_id, tars::Int32 &affectRows, tars::TarsCurrentPtr current)
{
    try
    {
        affectRows = (int)MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("activity_records", "where `user_id`='" + wx_id + "' and `activity_id`=" + activity_id);
    }
    catch(exception &e)
    {
        LOG->error() << "DataServiceImp::deleteActivityRecord error: " << e.what() << endl;
        affectRows = -1;
    }
    return 0;
}
//////////////////////////////////////////////////////

int DataServiceImp::getActivityInfo(const string &activity_id, LifeService::ActivityInfo &activityInfo, tars::TarsCurrentPtr current)
{
    int ret = ActivityHandle::getInstance()->GetActivityInfo(activity_id, activityInfo);
    
    if (ret != 0) return 300;
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

// int DataServiceImp::insertData(const string &sTableName, const vector<LifeService::Column> &vColumns, tars::TarsCurrentPtr current)
// {
//     MDbQueryRecord::getInstance()->InsertData(sTableName, vColumns);
//     LOG->debug() << "DataServiceImp::insertData Execute Table: " << sTableName << endl;
//     return 0;
// }
//////////////////////////////////////////////////////

// int DataServiceImp::queryData(const string &sTableName, const vector<string> &vColumns, const string &sCondition, vector<map<string, string>> &vmpResults, tars::TarsCurrentPtr current)
// {
//     string sql = buildSelectSQL(sTableName, vColumns, sCondition);
    
//     TC_Mysql::MysqlData mysql_data;

//     try
//     {
//         mysql_data = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sql);
//     }
//     catch (exception &e)
//     {
//         LOG->error() << "DataServiceImp::queryData: " << e.what() << endl;
//         return -1;
//     }
//     LOG->debug() << "DataServiceImp::queryData: Query Table: " << sTableName << endl;
//     vmpResults = mysql_data.data();
//     return 0;
// }
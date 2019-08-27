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
int DataServiceImp::hasUser(const string &wx_id, bool &sRsp, tars::TarsCurrentPtr current)
{
    sRsp = UserHandle::getInstance()->hasUser(wx_id);
    if (sRsp)
    {
        LOG->debug() << "hasUser: User exist" << endl;
    }
    else
    {
        LOG->debug() << "hasUser: User not exist" << endl;
    }
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
    LOG->debug() << "Create Club Successfully" << endl;
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getClubList(vector<LifeService::ClubInfo> &clubInfoList, tars::TarsCurrentPtr current)
{
    clubInfoList = ClubHandle::getInstance()->vClubInfo;
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::insertData(const string &sTableName, const vector<LifeService::Column> &sColumns, tars::TarsCurrentPtr current)
{
    MDbQueryRecord::getInstance()->InsertData(sTableName, sColumns);
    LOG->debug() << "Insert Data Successfully" << endl;
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::queryData(const string &sTableName, const vector<string> &sColumns, const string &sCondition, vector<map<string, string>> &sRsp, tars::TarsCurrentPtr current)
{
    string sql = buildSelectSQL(sTableName, sColumns, sCondition);
    
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
    sRsp = mysql_data.data();
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
    return 0;
}
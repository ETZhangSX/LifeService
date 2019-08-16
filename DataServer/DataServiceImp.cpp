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
    if (UserHandle::getInstance()->mUserInfo.count(wx_id) == 0)
    {
        sRsp = false;
    }
    else
    {
        sRsp = true;
    }
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getUserInfo(const string &wx_id, LifeService::UserInfo &sRsp, tars::TarsCurrentPtr current)
{
    if (UserHandle::getInstance()->mUserInfo.count(wx_id) != 0)
    {
        sRsp = UserHandle::getInstance()->mUserInfo[wx_id];
        return 0;
    }
    return -1;
}

//////////////////////////////////////////////////////
int DataServiceImp::getGroupInfo(map<tars::Int32, string> &groupInfo, tars::TarsCurrentPtr current)
{
    groupInfo = UserHandle::getInstance()->mGroupInfo;
    return 0;
}

//////////////////////////////////////////////////////
int DataServiceImp::getGroupByUserId(const string &wx_id, string &group, tars::TarsCurrentPtr current)
{
    if (UserHandle::getInstance()->mUserInfo.count(wx_id) != 0)
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
int DataServiceImp::insertData(const string &sTableName, const vector<LifeService::Column> &sColumns, tars::TarsCurrentPtr current)
{
    MDbQueryRecord::getInstance()->InsertData(sTableName, sColumns);
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
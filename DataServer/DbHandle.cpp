#include "DbHandle.h"
#include "Config.h"
#include "servant/TarsLogger.h"
#include "util.h"
#include "MysqlHandler.h"

using namespace std;
using namespace tars;

int UserHandle::LoadDataFromDb()
{
    TC_Mysql mysql(SConfig::getInstance()->strDbHost, \
                   SConfig::getInstance()->strUserName,\
                   SConfig::getInstance()->strPassWord, \
                   SConfig::getInstance()->strDbName, \
                   "utf8", \
                   SConfig::getInstance()->usPort);
    
    {
        TC_Mysql::MysqlData oResults;
        vector<string> vColumns = {
            "wx_id", "name", "phone", "gender", "avatar_url", "registration_time", "group_id"
        };
        string sql = buildSelectSQL("users", vColumns, "");
        try
        {
            oResults = mysql.queryRecord(sql);
        }
        catch (exception &e)
        {
            LOG->error() << "User Info error query: " << e.what() << endl;
            return -1;
        }
        size_t oResultsCount = oResults.size();

        for (size_t i = 0; i < oResultsCount; i++)
        {
            LifeService::UserInfo userInfo;
            userInfo.name               = oResults[i][vColumns[1]];
            userInfo.phone              = oResults[i][vColumns[2]];
            userInfo.gender             = oResults[i][vColumns[3]];
            userInfo.avatar_url         = oResults[i][vColumns[4]];
            userInfo.registration_time  = oResults[i][vColumns[5]];
            userInfo.group              = TC_Common::strto<tars::Int32>(oResults[i][vColumns[6]]);

            mUserInfo.insert(make_pair(oResults[i][vColumns[0]], userInfo));
            LOG->debug() << "UserHandle::LoadDataFromDb : "
                         << oResults[i]["wx_id"] << "\t" 
                         << oResults[i]["name"] << "\t"
                         << oResults[i]["group_id"] << endl;
        }
    }
    {
        TC_Mysql::MysqlData oResults;
        vector<string> vColumns = {"group_id", "user_type"};
        string sql = buildSelectSQL("user_group", vColumns, "");
        try
        {
            oResults = mysql.queryRecord(sql);
        }
        catch (exception &e)
        {
            LOG->error() << "Group Info error query: " << e.what() << endl;
            return -1;
        }
        size_t oResultsCount = oResults.size();

        for (size_t i = 0; i < oResultsCount; i++)
        {
            mGroupInfo.insert(make_pair(TC_Common::strto<tars::Int32>(oResults[i]["group_id"]), oResults[i]["user_type"]));
        }
    }
    return 0;
}

int UserHandle::InsertUserData(const string &wx_id, const LifeService::UserInfo &userInfo)
{
    {
        TC_ThreadLock::Lock lock(_pLocker);
        mUserInfo.insert(make_pair(wx_id, userInfo));
    }

    map<string, pair<TC_Mysql::FT, string>> vColumns;
    vColumns.insert(make_pair(            "wx_id", make_pair(TC_Mysql::DB_STR, wx_id)));
    vColumns.insert(make_pair(             "name", make_pair(TC_Mysql::DB_STR, userInfo.name)));
    vColumns.insert(make_pair(            "phone", make_pair(TC_Mysql::DB_STR, userInfo.phone)));
    vColumns.insert(make_pair(           "gender", make_pair(TC_Mysql::DB_STR, userInfo.gender)));
    vColumns.insert(make_pair(         "group_id", make_pair(TC_Mysql::DB_INT, TC_Common::tostr<tars::Int32>(userInfo.group))));
    vColumns.insert(make_pair(       "avatar_url", make_pair(TC_Mysql::DB_STR, userInfo.avatar_url)));
    vColumns.insert(make_pair("registration_time", make_pair(TC_Mysql::DB_STR, userInfo.registration_time)));

    MDbQueryRecord::getInstance()->InsertData("users", vColumns);

    LOG->debug() << "UserHandle::UpdateUserData : " 
                 << wx_id << "\t"
                 << userInfo.name << "\t"
                 << userInfo.group << "\t";
    
    return 0;
}

bool UserHandle::hasUser(const string &wx_id)
{
    if (mUserInfo.count(wx_id) == 0)
        return false;
    
    return true;
}


int ClubHandle::LoadDataFromDb()
{
    TC_Mysql mysql(SConfig::getInstance()->strDbHost, \
                   SConfig::getInstance()->strUserName,\
                   SConfig::getInstance()->strPassWord, \
                   SConfig::getInstance()->strDbName, \
                   "utf8", \
                   SConfig::getInstance()->usPort);
    
    {
        TC_Mysql::MysqlData oResults;
        vector<string> vColumns = {
            "club_id", "name", "create_time", "chairman", "introduction"
        };
        string sql = buildSelectSQL("clubs", vColumns, "");
        try
        {
            oResults = mysql.queryRecord(sql);
        }
        catch (exception &e)
        {
            LOG->error() << "Club Info error query: " << e.what() << endl;
            return -1;
        }
        size_t oResultsCount = oResults.size();

        for (size_t i = 0; i < oResultsCount; i++) 
        {
            LifeService::ClubInfo clubInfo;
            clubInfo.club_id        = oResults[i][vColumns[0]];
            clubInfo.name           = oResults[i][vColumns[1]];
            clubInfo.create_time    = oResults[i][vColumns[2]];
            clubInfo.chairman       = oResults[i][vColumns[3]];
            clubInfo.introduction   = oResults[i][vColumns[4]];

            vClubInfo.push_back(clubInfo);
        }
    }
    return 0;
}

int ClubHandle::InsertClubData(const LifeService::ClubInfo &clubInfo)
{
    {
        TC_ThreadLock::Lock lock(_pLocker);
        vClubInfo.push_back(clubInfo);
    }

    map<string, pair<TC_Mysql::FT, string>> vColumns;

    vColumns.insert(make_pair(     "club_id", make_pair(TC_Mysql::DB_INT, clubInfo.club_id)));
    vColumns.insert(make_pair(        "name", make_pair(TC_Mysql::DB_STR, clubInfo.name)));
    vColumns.insert(make_pair( "create_time", make_pair(TC_Mysql::DB_STR, clubInfo.create_time)));
    vColumns.insert(make_pair(    "chairman", make_pair(TC_Mysql::DB_STR, clubInfo.chairman)));
    vColumns.insert(make_pair("introduction", make_pair(TC_Mysql::DB_STR, clubInfo.introduction)));

    MDbQueryRecord::getInstance()->InsertData("clubs", vColumns);

    LOG->debug() << "Insert Club Data: " << clubInfo.name << endl;

    return 0;
}
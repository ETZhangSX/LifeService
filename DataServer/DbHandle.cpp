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
        vector<string> columns = {"wx_id", "name", "phone", "gender", "avatar_url", "registration_time", "group_id"};
        string sql = buildSelectSQL("users", columns, "");
        try
        {
            /*
            * TODO: 选取字段: 
            *       users:       wx_id, name, phone, gender, registration_time, group_id
            *       
            */
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
            userInfo.name               = oResults[i]["name"];
            userInfo.phone              = oResults[i]["phone"];
            userInfo.gender             = oResults[i]["gender"];
            userInfo.avatar_url         = oResults[i]["avatar_url"];
            userInfo.registration_time  = oResults[i]["registration_time"];
            userInfo.group              = TC_Common::strto<tars::Int32>(oResults[i]["group_id"]);

            mUserInfo.insert(make_pair(oResults[i]["wx_id"], userInfo));
            LOG->debug() << "UserHandle::LoadDataFromDb : "
                         << oResults[i]["wx_id"] << "\t" 
                         << oResults[i]["name"] << "\t"
                         << oResults[i]["group_id"] << endl;
        }
    }
    {
        TC_Mysql::MysqlData oResults;
        vector<string> columns = {"group_id", "user_type"};
        string sql = buildSelectSQL("user_group", columns, "");
        try
        {
            /*
            * TODO: 选取字段: 
            *       user_groups:       group_id, user_type
            *       
            */
            oResults = mysql.queryRecord("");
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

    map<string, pair<TC_Mysql::FT, string>> columns;
    columns.insert(make_pair(            "wx_id", make_pair(TC_Mysql::DB_STR, wx_id)));
    columns.insert(make_pair(             "name", make_pair(TC_Mysql::DB_STR, userInfo.name)));
    columns.insert(make_pair(            "phone", make_pair(TC_Mysql::DB_STR, userInfo.phone)));
    columns.insert(make_pair(           "gender", make_pair(TC_Mysql::DB_INT, userInfo.gender)));
    columns.insert(make_pair(       "avatar_url", make_pair(TC_Mysql::DB_STR, userInfo.avatar_url)));
    columns.insert(make_pair("registration_time", make_pair(TC_Mysql::DB_STR, userInfo.registration_time)));

    MDbQueryRecord::getInstance()->InsertData("users", columns);

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
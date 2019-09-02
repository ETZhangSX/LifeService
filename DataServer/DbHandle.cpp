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

//////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////
int ActivityHandle::GetActivityList(const int &index, const int &batch, int &nextIndex, vector<map<string, string>> &activityList)
{
    string sTableName = "activities";
    vector<string> vColumns = {"activity_id", "name", "sponsor", "club_id", "target_id", "create_time", "start_time", "stop_time", "registry_start_time", "registry_stop_time", "content"};
    string sCondition = "`" + vColumns[0] + "`";
    // 0代表第一次请求
    if (index == 0)
    {
        sCondition += ">=0";
    }
    else 
    {
        sCondition += "<" + TC_Common::tostr<int>(index);
    }

    // 根据创建时间排序, 从最新的留言开始查询
    string sql = buildSelectSQL(sTableName, vColumns, sCondition, vColumns[4], DESC, batch);
    {
        TC_Mysql::MysqlData oResults;
        try
        {
            oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sql);
        }
        catch (exception &e)
        {
            LOG->error() << "GetActivityList query error: " << e.what() << endl;
            return -1;
        }
        size_t oResultsCount = oResults.size();

        // 若查询的数据小于batch, 说明以及没有更早的数据, 返回-1
        if (oResultsCount < batch)
            nextIndex = -1;
        else
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1][vColumns[0]]);

        for (size_t i = 0; i < oResultsCount; i++)
        {
            map<string, string> item;
            
            item.insert(make_pair(vColumns[0], oResults[i][vColumns[0]]));
            item.insert(make_pair(vColumns[1], oResults[i][vColumns[1]]));
            item.insert(make_pair(vColumns[2], oResults[i][vColumns[2]]));
            item.insert(make_pair(vColumns[3], oResults[i][vColumns[3]]));
            item.insert(make_pair(vColumns[4], oResults[i][vColumns[4]]));
            item.insert(make_pair(vColumns[5], oResults[i][vColumns[5]]));
            item.insert(make_pair(vColumns[6], oResults[i][vColumns[6]]));
            item.insert(make_pair(vColumns[7], oResults[i][vColumns[7]]));
            item.insert(make_pair(vColumns[8], oResults[i][vColumns[8]]));
            item.insert(make_pair(vColumns[9], oResults[i][vColumns[9]]));
            item.insert(make_pair(vColumns[10], oResults[i][vColumns[10]]));

            activityList.push_back(item);
        }
    }
    return 0;
}

//////////////////////////////////////////////////////
int MsgWallHandle::InsertMessage(const LifeService::Message &msg)
{
    map<string, pair<TC_Mysql::FT, string>> mColumns;

    mColumns.insert(make_pair(  "user_id", make_pair(TC_Mysql::DB_STR, msg.user_id)));
    mColumns.insert(make_pair(  "content", make_pair(TC_Mysql::DB_STR, msg.content)));
    mColumns.insert(make_pair("anonymous", make_pair(TC_Mysql::DB_INT, TC_Common::tostr<bool>(msg.anonymous))));

    MDbQueryRecord::getInstance()->InsertData("message_wall", mColumns);

    LOG->debug() << "Insert Message Wall Data" << msg.user_id << endl;

    return 0;
}

int MsgWallHandle::GetMsgList(const int &index, const int &batch, const string &date, const string wx_id, int &nextIndex, vector<LifeService::Message> &msgList)
{
    string sTableName = "message_wall";
    vector<string> vColumns = {"message_id", "user_id", "content", "anonymous", "message_time", "like_count"};
    string sCondition = "`" + vColumns[0] + "`";

    // 0代表第一次请求
    if (index == 0)
    {
        sCondition += ">=0";
    }
    else 
    {
        sCondition += "<" + TC_Common::tostr<int>(index);
    }

    if (wx_id != "")
    {
        sCondition += " and `user_id`='" + wx_id + "'";
    }

    if (date != "") 
    {
        sCondition += " and to_days(`" + vColumns[5] + "`)=to_days('" + date + "')";
    }

    // 根据创建时间排序, 从最新的留言开始查询
    string sql = buildSelectSQL(sTableName, vColumns, sCondition, vColumns[4], DESC, batch);
    {
        TC_Mysql::MysqlData oResults;
        try
        {
            oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sql);
        }
        catch (exception &e)
        {
            LOG->error() << "GetMsgList error query: " << e.what() << endl;
            return -1;
        }

        size_t oResultsCount = oResults.size();

        // 若查询的数据小于batch, 说明以及没有更早的数据, 返回-1
        if (oResultsCount < batch)
            nextIndex = -1;
        else
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1][vColumns[0]]);

        for (size_t i = 0; i < oResultsCount; i++)
        {
            LifeService::Message msg;
            msg.message_id   = oResults[i][vColumns[0]];
            msg.user_id      = oResults[i][vColumns[1]];
            msg.content      = oResults[i][vColumns[2]];
            msg.anonymous    = TC_Common::strto<bool>(oResults[i][vColumns[3]]);
            msg.message_time = oResults[i][vColumns[4]];
            msg.like_count   = TC_Common::strto<int>(oResults[i][vColumns[5]]);

            msgList.push_back(msg);
        }
    }
    return 0;
}

int MsgWallHandle::AddLike(const string &message_id)
{
    string sSql = "update message_wall set `like_count`=(`like_count`+1) where `message_id`=" + message_id;
    MDbExecuteRecord::getInstance()->AddExecuteSql(sSql);
    return 0;
}

int MsgWallHandle::GetLike(const string &message_id, int &like_count)
{
    string sSql = buildSelectSQL("message_wall", "like_count", "`message_id`=" + message_id);
    {
        TC_Mysql::MysqlData oResult;
        try
        {
            oResult = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sSql);
        }
        catch (exception &e)
        {
            LOG->error() << "GetLike error query: " << e.what() << endl;
            return -1;
        }

        if (oResult.size() < 1)
            return -1;

        like_count = TC_Common::strto<int>(oResult[0]["like_count"]);
    }
    return 0;
}
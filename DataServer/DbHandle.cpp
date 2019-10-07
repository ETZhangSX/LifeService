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
            mPhoneToWxId.insert(make_pair(userInfo.phone, oResults[i][vColumns[0]]));
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
//////////////////////////////////////////////////////

int UserHandle::InsertUserData(const string &wx_id, const LifeService::UserInfo &userInfo)
{
    map<string, pair<TC_Mysql::FT, string>> vColumns;
    vColumns.insert(make_pair("wx_id"            , make_pair(TC_Mysql::DB_STR, wx_id)));
    vColumns.insert(make_pair("name"             , make_pair(TC_Mysql::DB_STR, userInfo.name)));
    vColumns.insert(make_pair("phone"            , make_pair(TC_Mysql::DB_STR, userInfo.phone)));
    vColumns.insert(make_pair("gender"           , make_pair(TC_Mysql::DB_STR, userInfo.gender)));
    vColumns.insert(make_pair("group_id"         , make_pair(TC_Mysql::DB_INT, TC_Common::tostr<tars::Int32>(userInfo.group))));
    vColumns.insert(make_pair("avatar_url"       , make_pair(TC_Mysql::DB_STR, userInfo.avatar_url)));
    vColumns.insert(make_pair("registration_time", make_pair(TC_Mysql::DB_STR, userInfo.registration_time)));
    
    try 
    {
        MDbQueryRecord::getInstance()->GetMysqlObject()->insertRecord("users", vColumns);
    }
    catch(exception &e)
    {
        LOG->error() << "UserHandle::InsertUserData error: " << e.what() << endl;
        return -1;
    }
    
    {
        TC_ThreadWLock wlock(_pRWLocker);
        mUserInfo.insert(make_pair(wx_id, userInfo));
        mPhoneToWxId.insert(make_pair(userInfo.phone, wx_id));
    }

    LOG->debug() << "UserHandle::InsertUserData : " 
                 << wx_id << "\t"
                 << userInfo.name << "\t"
                 << userInfo.group << "\t";
    
    return 0;
}
//////////////////////////////////////////////////////

bool UserHandle::hasUser(const string &wx_id)
{
    TC_ThreadRLock rlock(_pRWLocker);
    if (mUserInfo.count(wx_id) == 0)
        return false;
    return true;
}
//////////////////////////////////////////////////////

bool UserHandle::hasPhone(const string &phone)
{
    TC_ThreadRLock rlock(_pRWLocker);
    if (mPhoneToWxId.count(phone) == 0)
        return false;
    return true;
}
//////////////////////////////////////////////////////

string UserHandle::getUserNameById(const string &wx_id)
{
    TC_ThreadRLock rlock(_pRWLocker);
    return mUserInfo[wx_id].name;
}
//////////////////////////////////////////////////////

LifeService::UserInfo UserHandle::getUserInfoById(const string &wx_id)
{
    TC_ThreadRLock rlock(_pRWLocker);
    return mUserInfo[wx_id];
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
            mClub.insert(make_pair(clubInfo.club_id, (int)vClubInfo.size() - 1));

            LOG->debug() << "club id: " << clubInfo.club_id
                         << "\tclub name: " << clubInfo.name << endl;
        }
        LOG->debug() << "vector size: " << vClubInfo.size() << endl;
    }
    return 0;
}
//////////////////////////////////////////////////////

int ClubHandle::InsertClubManager(const string &wx_id, const string &club_id)
{
    TC_Mysql::RECORD_DATA mColumns;

    mColumns.insert(make_pair("wx_id", make_pair(TC_Mysql::DB_STR, wx_id)));
    mColumns.insert(make_pair("club_id", make_pair(TC_Mysql::DB_INT, club_id)));

    try
    {
        MDbQueryRecord::getInstance()->GetMysqlObject()->insertRecord("club_managers", mColumns);
    }
    catch (exception &e)
    {
        LOG->error() << "ClubHandle::InsertClubManager error: " << e.what() << endl;
        return -1;
    }

    LOG->debug() << "ClubHandle::InsertClubManager user: " << wx_id << " club_id: " << club_id << endl;
    return 0;
}
//////////////////////////////////////////////////////

int ClubHandle::InsertClubData(LifeService::ClubInfo clubInfo, string &club_id)
{
    map<string, pair<TC_Mysql::FT, string>> mColumns;

    mColumns.insert(make_pair("name"        , make_pair(TC_Mysql::DB_STR, clubInfo.name)));
    mColumns.insert(make_pair("create_time" , make_pair(TC_Mysql::DB_STR, clubInfo.create_time)));
    mColumns.insert(make_pair("chairman"    , make_pair(TC_Mysql::DB_STR, clubInfo.chairman)));
    mColumns.insert(make_pair("introduction", make_pair(TC_Mysql::DB_STR, clubInfo.introduction)));
    {
        long last_insert_id;
        try
        {
            // 插入数据库
            MDbQueryRecord::getInstance()->GetMysqlObject()->insertRecord("clubs", mColumns);
            // 获取自增id
            last_insert_id = MDbQueryRecord::getInstance()->GetMysqlObject()->lastInsertID();
        }
        catch (exception &e)
        {
            LOG->error() << "ClubHandle::InsertClubData error: " << e.what() << endl;
            return -1;
        }
        // 新增数据到数组和map中
        clubInfo.club_id = TC_Common::tostr<long>(last_insert_id);
        {
            TC_ThreadWLock wlock(_pRWLocker);
            vClubInfo.push_back(clubInfo);
            mClub.insert(make_pair(clubInfo.club_id, (int)vClubInfo.size() - 1));
        }
        club_id = clubInfo.club_id;
    }
    

    LOG->debug() << "Insert Club Data: " << clubInfo.name << endl;

    return 0;
}
//////////////////////////////////////////////////////

int ClubHandle::GetClubList(int index, int batch, const string &wx_id, int &nextIndex, vector<LifeService::ClubInfo> &clubInfoList)
{
    nextIndex = -1;
    // 不需要筛选用户, 从vClubInfo中获取
    if(wx_id == "") 
    {
        int lenofclub;  // 数组长度
        int endp;       // 结束位置
        
        {// 读锁
            TC_ThreadRLock rlock(_pRWLocker);
            lenofclub = (int)vClubInfo.size();
            if (index >= lenofclub) return 0;
            // 若请求的位置超过数组长度则返回数组末端
            endp = ((index + batch > lenofclub)? (lenofclub - 1):(index + batch - 1));
            // 复制数组
            clubInfoList.assign(vClubInfo.begin() + index, vClubInfo.begin() + endp + 1);
        }

        // 是否还有数据
        nextIndex = ((endp + 1 == lenofclub)? -1 : (endp + 1));

        LOG->debug() << "ClubHandle::GetClubList List size: " << clubInfoList.size() 
                     << " index: " << index
                     << " endp: " << endp << endl;
        return 0;
    }

    string sTableLeft  = "apply_for_club";
    string sTableRight = "clubs";
    // 两张表有相同字段club_id
    vector<string> vColumns = {"apply_for_club.club_id", "create_time", "name", "chairman", "introduction"};
    string sOnFilter = sTableLeft + ".club_id=" + sTableRight + ".club_id where user_id='" + wx_id + "' and `apply_status`=1 and apply_for_club.club_id>" + TC_Common::tostr<int>(index);
    // 构建join语句
    string sSql = buildJoinSQL(sTableLeft, sTableRight, LEFTJOIN, vColumns, sOnFilter, "club_id", DEFAULT, batch);
    
    {
        TC_Mysql::MysqlData oResults;
        try 
        {
            oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sSql);
        }
        catch (exception &e)
        {
            LOG->error() << "GetClubList query error: " << e.what() << endl;
            return -1;
        }
        size_t oResultsCount = oResults.size();

        if (oResultsCount >= (size_t)batch)
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1]["club_id"]);
        
        for (size_t i = 0; i < oResultsCount; i++)
        {
            LifeService::ClubInfo clubInfo;
            clubInfo.club_id      = oResults[i]["club_id"];
            clubInfo.create_time  = oResults[i][vColumns[1]];
            clubInfo.name         = oResults[i][vColumns[2]];
            clubInfo.chairman     = oResults[i][vColumns[3]];
            clubInfo.introduction = oResults[i][vColumns[4]];

            clubInfoList.push_back(clubInfo);
        }
    }

    LOG->debug() << "ClubHandle::GetClubList Execute SQL: " << sSql << endl;
    return 0;
}
//////////////////////////////////////////////////////

int ClubHandle::GetManagerClubList(int index, int batch, const string &wx_id, int &nextIndex, vector<LifeService::ClubInfo> &clubInfoList)
{
    nextIndex = -1;

    string sTableLeft = "club_managers";
    string sTableRight = "clubs";
    vector<string> vColumns = {"clubs.club_id", "create_time", "name", "chairman", "introduction"};
    string sOnFilter = "clubs.club_id=club_managers.club_id";
    string sCondition = " where `wx_id`='" + wx_id + "'";
    // 构建join语句
    string sSql = buildJoinSQL(sTableLeft, sTableRight, LEFTJOIN, vColumns, sOnFilter + sCondition, vColumns[1], DESC, batch);
    
    {
        TC_Mysql::MysqlData oResults;
        try 
        {
            oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sSql);
        }
        catch (exception &e)
        {
            LOG->error() << "GetClubList query error: " << e.what() << endl;
            return -1;
        }

        size_t oResultsCount = oResults.size();

        if (oResultsCount >= (size_t)batch)
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1]["club_id"]);
        
        for (size_t i = 0; i < oResultsCount; i++)
        {
            LifeService::ClubInfo clubInfo;
            clubInfo.club_id      = oResults[i]["club_id"];
            clubInfo.create_time  = oResults[i][vColumns[1]];
            clubInfo.name         = oResults[i][vColumns[2]];
            clubInfo.chairman     = oResults[i][vColumns[3]];
            clubInfo.introduction = oResults[i][vColumns[4]];

            clubInfoList.push_back(clubInfo);
        }
    }

    LOG->debug() << "ClubHandle::GetManagerClubList Execute SQL: " << sSql << endl;
    return 0;
}
//////////////////////////////////////////////////////

int ClubHandle::GetClubManagerCount(const string &wx_id, const string &club_id)
{
    string sTableName = "club_managers";
    string sCondition = "where `wx_id`='" + wx_id + (club_id==""? "'" : ("' and `club_id`=" + club_id));
    int count = 0;
    try
    {
        count = MDbQueryRecord::getInstance()->GetMysqlObject()->getRecordCount(sTableName, sCondition);
    }
    catch (exception &e)
    {
        LOG->error() << "ClubHandle::GetClubManagerCount error: " << e.what() << endl;
        return -1;
    }
    LOG->debug() << "ClubHandle::GetClubManagerCount Table: " << sTableName << " Condition: " << sCondition << endl;
    return count;
}
//////////////////////////////////////////////////////

int ClubHandle::DeleteClub(const string &club_id)
{
    int affectRows = 0;
    try
    {
        MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("apply_for_club", "where `club_id`=" + club_id);
        MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("activities"    , "where `club_id`=" + club_id);
        affectRows = MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("clubs"         , "where `club_id`=" + club_id);
    }
    catch(exception &e)
    {
        LOG->error() << "ClubHandle::DeleteClub Delete Error: " << e.what() << endl;
        return -1;
    }
    {
        TC_ThreadWLock wlock(_pRWLocker);
        vClubInfo.erase(vClubInfo.begin() + mClub[club_id]);
        for (int i = mClub[club_id]; i < vClubInfo.size(); ++i)
        {
            mClub[vClubInfo[i].club_id] = i;
        }
    }
    LOG->debug() << "ClubHandle::DeleteClub Delete Club: " << vClubInfo[mClub[club_id]].name << endl;
    return affectRows;
}
//////////////////////////////////////////////////////

int ClubHandle::DeleteClubManager(const string &wx_id, const string &club_id)
{
    int affectRows = 0;
    try
    {
        affectRows = MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("club_managers", "where `wx_id`='" + wx_id + "' and `club_id`=" + club_id);
    }
    catch (exception &e)
    {
        LOG->error() << "ClubHandle::DeleteClubManager Error: " << e.what() << endl;
        return -1;
    }
    LOG->debug() << "ClubHandle::DeleteClubManager wx_id:" << wx_id << " club_id:" << club_id << endl;
    return affectRows;
}
//////////////////////////////////////////////////////

int ClubHandle::InsertApplyData(const string &wx_id, const string &club_id)
{
    string sTableName = "apply_for_club";
    TC_Mysql::RECORD_DATA mpColumns;
    mpColumns.insert(make_pair("apply_status", make_pair(TC_Mysql::DB_INT, "0")));
    mpColumns.insert(make_pair("user_id"     , make_pair(TC_Mysql::DB_STR, wx_id)));
    mpColumns.insert(make_pair("club_id"     , make_pair(TC_Mysql::DB_INT, club_id)));

    try
    {
        MDbQueryRecord::getInstance()->GetMysqlObject()->insertRecord(sTableName, mpColumns);
    }
    catch (exception &e)
    {
        LOG->error() << "ClubHandle::InsertApplyData Insert Error: " << e.what() << endl;
        return -1;
    }
    LOG->debug() << "ClubHandle::InsertApplyData wx_id: " << wx_id << " club_id: " << club_id << endl;
    return 0;
}
//////////////////////////////////////////////////////

int ClubHandle::GetApplyListByClubId(const string &club_id, int index, int batch, int apply_status, int &nextIndex, vector<LifeService::ApplyInfo> &applyList)
{
    nextIndex = -1;

    string sTableLeft = "apply_for_club";
    string sTableRight = "users";
    vector<string> vColumns = {"apply_id", "apply_time", "user_id", "club_id", "name", "avatar_url"};
    string sOnFilter = vColumns[2] + "=wx_id";
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
    // 筛选社团和状态
    sCondition += " and `club_id`=" + club_id + " and `apply_status`=" + TC_Common::tostr<int>(apply_status);
    string sSql;
    // 构建join语句
    sSql = buildJoinSQL(sTableLeft, sTableRight, LEFTJOIN, vColumns, sOnFilter + " where " + sCondition, vColumns[1], DESC, batch);

    {
        TC_Mysql::MysqlData oResults;
        try
        {
            oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sSql);
        }
        catch (exception &e)
        {
            LOG->error() << "GetApplyListByClubId query error: " << e.what() << endl;
            return -1;
        }
        size_t oResultsCount = oResults.size();

        // 若查询的数据小于batch, 说明以及没有更早的数据, 返回-1
        if (oResultsCount >= (size_t)batch)
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1][vColumns[0]]);

        for (size_t i = 0; i < oResultsCount; i++)
        {
            LifeService::ApplyInfo applyInfo;

            applyInfo.apply_id   = oResults[i][vColumns[0]];
            applyInfo.apply_time = oResults[i][vColumns[1]];
            applyInfo.wx_id      = oResults[i][vColumns[2]];
            applyInfo.club_id    = oResults[i][vColumns[3]];
            applyInfo.user_name  = oResults[i][vColumns[4]];
            applyInfo.avatar_url = oResults[i][vColumns[5]];

            applyList.push_back(applyInfo);
        }
    }
    LOG->debug() << "ClubHandle::GetApplyListByClubId Execute SQL: " << sSql << endl;
    return 0;
}
//////////////////////////////////////////////////////

int ClubHandle::GetApplyListByUserId(const string &wx_id, int index, int batch, int apply_status, int &nextIndex, vector<LifeService::ApplyInfo> &applyList)
{
    nextIndex = -1;

    string sTableLeft = "apply_for_club";
    string sTableRight = "clubs";
    vector<string> vColumns = {"apply_id", "apply_time", "user_id", "club_id", "name"};
    string sOnFilter = sTableLeft + "." + vColumns[3] + "=clubs.club_id";
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
    // 筛选用户和状态
    sCondition += " and `user_id`=" + wx_id + " and `apply_status`=" + TC_Common::tostr<int>(apply_status);
    // 构建join语句
    string sSql = buildJoinSQL(sTableLeft, sTableRight, LEFTJOIN, vColumns, sOnFilter + " where " + sCondition, vColumns[1], DESC, batch);
    
    {
        TC_Mysql::MysqlData oResults;
        try
        {
            oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sSql);
        }
        catch (exception &e)
        {
            LOG->error() << "GetApplyListByUserId query error: " << e.what() << endl;
            return -1;
        }
        size_t oResultsCount = oResults.size();

        // 若查询的数据小于batch, 说明以及没有更早的数据, 返回-1
        if (oResultsCount >= (size_t)batch)
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1][vColumns[0]]);

        for (size_t i = 0; i < oResultsCount; i++)
        {
            LifeService::ApplyInfo applyInfo;

            applyInfo.apply_id   = oResults[i][vColumns[0]];
            applyInfo.apply_time = oResults[i][vColumns[1]];
            applyInfo.wx_id      = oResults[i][vColumns[2]];
            applyInfo.club_id    = oResults[i][vColumns[3]];
            applyInfo.club_name  = oResults[i][vColumns[4]];

            applyList.push_back(applyInfo);
        }
    }

    LOG->debug() << "ClubHandle::GetApplyListByUserId Execute SQL: " << sSql << endl;
    return 0;
}
//////////////////////////////////////////////////////

string ClubHandle::getClubNameById(const string &club_id)
{
    TC_ThreadRLock rlock(_pRWLocker);
    return vClubInfo[mClub[club_id]].name;
}
//////////////////////////////////////////////////////

int ClubHandle::SetApplyStatus(const string &wx_id, const string &club_id, int apply_status)
{
    TC_Mysql::RECORD_DATA mpColumn;
    mpColumn.insert(make_pair("apply_status", make_pair(TC_Mysql::DB_INT, TC_Common::tostr<int>(apply_status))));
    string sCondition =  "where `user_id`='" + wx_id + "' and `club_id`=" + club_id;
    
    int affectRows = 0;
    try 
    {
        affectRows = (int)MDbQueryRecord::getInstance()->GetMysqlObject()->updateRecord("apply_for_club", mpColumn, sCondition);
    }
    catch(exception &e)
    {
        LOG->error() << "ClubHandle::SetApplyStatus Execute update error:" << e.what() << endl;
        return -1;
    }
    
    // MDbExecuteRecord::getInstance()->AddExecuteSql(sSql);
    LOG->debug() << "ClubHandle::SetApplyStatus Execute update apply_status: " << apply_status << endl;
    return affectRows;
}
//////////////////////////////////////////////////////

int ClubHandle::GetApplyCount(const string &wx_id, const string &club_id, int apply_status)
{
    string sTableName = "apply_for_club";
    string sCondition = "where `user_id`='" + wx_id + "' and `club_id`=" + club_id + " and `apply_status`";
    int count = 0;
    if (apply_status >= 0)
        sCondition += "=" + TC_Common::tostr<tars::Int32>(apply_status);
    else
        sCondition += "!=" + TC_Common::tostr<tars::Int32>(-apply_status);
    
    try
    {
        count = MDbQueryRecord::getInstance()->GetMysqlObject()->getRecordCount(sTableName, sCondition);
    }
    catch (exception &e)
    {
        LOG->error() << "ClubHandle::GetApplyCount error: " << e.what() << endl;
        return -1;
    }
    LOG->debug() << "ClubHandle::GetApplyCount Table: " << sTableName << " Condition: " << sCondition << endl;
    return count;
}
//////////////////////////////////////////////////////

int ClubHandle::DeleteApply(const string &wx_id, const string &club_id)
{
    string sCondition = "where `user_id`='" + wx_id + "' and `club_id`=" + club_id;
    int affectRows = 0;
    
    try 
    {
        affectRows = (int)MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("apply_for_club",sCondition);
    }
    catch(exception &e)
    {
        LOG->error() << "ClubHandle::DeleteApply Execute delete error:" << e.what() << endl;
        return -1;
    }
    // 将sql语句添加到MDbExecuteRecord类的执行队列中
    // MDbExecuteRecord::getInstance()->AddExecuteSql(sSql);
    LOG->debug() << "ClubHandle::DeleteApply delete record :" << sCondition << endl;
    return affectRows;
}
//////////////////////////////////////////////////////

int ActivityHandle::InsertActivityData(const LifeService::ActivityInfo activityInfo)
{
    string sTableName = "activities";
    TC_Mysql::RECORD_DATA mpColumns;
    mpColumns.insert(make_pair("name"               , make_pair(TC_Mysql::DB_STR, activityInfo.name)));
    mpColumns.insert(make_pair("sponsor"            , make_pair(TC_Mysql::DB_STR, activityInfo.sponsor)));
    mpColumns.insert(make_pair("club_id"            , make_pair(TC_Mysql::DB_STR, activityInfo.club_id)));
    mpColumns.insert(make_pair("target_id"          , make_pair(TC_Mysql::DB_STR, activityInfo.target_id)));
    mpColumns.insert(make_pair("start_time"         , make_pair(TC_Mysql::DB_STR, activityInfo.start_time)));
    mpColumns.insert(make_pair("stop_time"          , make_pair(TC_Mysql::DB_STR, activityInfo.stop_time)));
    mpColumns.insert(make_pair("registry_start_time", make_pair(TC_Mysql::DB_STR, activityInfo.registry_start_time)));
    mpColumns.insert(make_pair("registry_stop_time" , make_pair(TC_Mysql::DB_STR, activityInfo.registry_stop_time)));
    mpColumns.insert(make_pair("content"            , make_pair(TC_Mysql::DB_STR, activityInfo.content)));

    try
    {
        MDbQueryRecord::getInstance()->GetMysqlObject()->insertRecord(sTableName, mpColumns);
    }
    catch (exception &e)
    {
        LOG->error() << "ActivityHandle::InsertActivityData Insert Error: " << e.what() << endl;
        return -1;
    }
    LOG->debug() << "ActivityHandle::InsertActivityData Name: " << activityInfo.name << endl;
    return 0;
}
//////////////////////////////////////////////////////

int ActivityHandle::GetActivityList(int index, int batch, const string &wx_id, const string &club_id, int &nextIndex, vector<map<string, string>> &activityList)
{
    nextIndex = -1;

    string sTableName = "activities";
    string ambiguousColumn = "activity_id";
    vector<string> vColumns = {
        "activities.activity_id", "name", "sponsor", "club_id", "target_id", "create_time", "start_time", "stop_time", "registry_start_time", "registry_stop_time", "content"
    };
    string sCondition = vColumns[0];

    // 0代表第一次请求
    if (index == 0)
        sCondition += ">=0";
    else 
        sCondition += "<" + TC_Common::tostr<int>(index);
    
    // 筛选特定社团
    if (club_id != "")
    {
        sCondition += " and `club_id`=" + club_id;
    }

    string sSql;
    // 筛选特定用户参加的活动, 需要联表查询
    if (wx_id != "")
    {
        string sTableLeft = "activity_records";
        string sOnFilter = sTableLeft + ".activity_id=" + sTableName + ".activity_id where " + sCondition + " and `user_id`='" + wx_id + "'";
        sSql = buildJoinSQL(sTableLeft, sTableName, LEFTJOIN, vColumns, sOnFilter, vColumns[5], DESC, batch);
    }
    else
    {
        sSql = buildSelectSQL(sTableName, vColumns, sCondition, vColumns[5], DESC, batch);
    }

    // 根据创建时间排序
    {
        TC_Mysql::MysqlData oResults;
        try
        {
            oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sSql);
        }
        catch (exception &e)
        {
            LOG->error() << "GetActivityList query error: " << e.what() << endl;
            return -1;
        }
        size_t oResultsCount = oResults.size();

        // 若查询的数据小于batch, 说明以及没有更早的数据, 返回-1
        if (oResultsCount >= (size_t)batch)
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1][ambiguousColumn]);

        for (size_t i = 0; i < oResultsCount; i++)
        {
            map<string, string> item;
            
            item.insert(make_pair(ambiguousColumn , oResults[i][ambiguousColumn]));
            item.insert(make_pair(vColumns[1] , oResults[i][vColumns[1]]));
            item.insert(make_pair(vColumns[2] , oResults[i][vColumns[2]]));
            item.insert(make_pair(vColumns[3] , oResults[i][vColumns[3]]));
            item.insert(make_pair(vColumns[4] , oResults[i][vColumns[4]]));
            item.insert(make_pair(vColumns[5] , oResults[i][vColumns[5]]));
            item.insert(make_pair(vColumns[6] , oResults[i][vColumns[6]]));
            item.insert(make_pair(vColumns[7] , oResults[i][vColumns[7]]));
            item.insert(make_pair(vColumns[8] , oResults[i][vColumns[8]]));
            item.insert(make_pair(vColumns[9] , oResults[i][vColumns[9]]));
            item.insert(make_pair(vColumns[10], oResults[i][vColumns[10]]));

            // 获取社团名
            string club_name = ClubHandle::getInstance()->getClubNameById(item["club_id"]);
            
            item.insert(make_pair("club_name", club_name));
            activityList.push_back(item);
        }
    }
    LOG->debug() << "ActivityHandle::GetActivityList AddExecuteSql: " << sSql << endl;

    return 0;
}
//////////////////////////////////////////////////////

int ActivityHandle::UpdateActivity(const LifeService::ActivityInfo &activityInfo)
{
    TC_Mysql::RECORD_DATA updateItem;
    updateItem.insert(make_pair("name"               , make_pair(TC_Mysql::DB_STR, activityInfo.name)));
    updateItem.insert(make_pair("start_time"         , make_pair(TC_Mysql::DB_STR, activityInfo.start_time)));
    updateItem.insert(make_pair("stop_time"          , make_pair(TC_Mysql::DB_STR, activityInfo.stop_time)));
    updateItem.insert(make_pair("registry_start_time", make_pair(TC_Mysql::DB_STR, activityInfo.registry_start_time)));
    updateItem.insert(make_pair("registry_stop_time" , make_pair(TC_Mysql::DB_STR, activityInfo.registry_stop_time)));
    updateItem.insert(make_pair("content"            , make_pair(TC_Mysql::DB_STR, activityInfo.content)));
    int affectRows = 0;
    try
    {
        affectRows = (int)MDbQueryRecord::getInstance()->GetMysqlObject()->updateRecord("activities", updateItem, "where `activity_id`=" + activityInfo.activity_id);
    }
    catch(exception &e)
    {
        LOG->error() << "ActivityHandle::UpdateActivity error: " << e.what() << endl;
        return -1;
    }
    return affectRows;
}
//////////////////////////////////////////////////////

int ActivityHandle::DeleteActivity(const string &activity_id)
{
    string sql_delete_records = "where `activity_id`=" + activity_id;
    string sql_delete_activity = "where `activity_id`=" + activity_id;

    int affectRows = 0;
    try
    {
        MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("activity_records", sql_delete_records);
        affectRows = (int)MDbQueryRecord::getInstance()->GetMysqlObject()->deleteRecord("activities", sql_delete_activity);
    }
    catch(exception &e)
    {
        LOG->error() << "ActivityHandle::DeleteActivity error: " << e.what() << endl;
        return -1;
    }

    LOG->debug() << "ActivityHandle::DeleteActivity AddExecuteSql: " << sql_delete_records << ", " << sql_delete_activity << endl;
    return affectRows;
}
//////////////////////////////////////////////////////

int ActivityHandle::GetActivityInfo(const string &activity_id, LifeService::ActivityInfo &activityInfo)
{
    string sTableName = "activities";
    vector<string> vColumns = {"name", "sponsor", "club_id", "target_id", "create_time", "start_time", "stop_time", "registry_start_time", "registry_stop_time", "content"};
    string sCondition = "`activity_id`=" + activity_id;

    string sSql = buildSelectSQL(sTableName, vColumns, sCondition);
    
    {
        TC_Mysql::MysqlData oResults;
        try
        {
            oResults = MDbQueryRecord::getInstance()->GetMysqlObject()->queryRecord(sSql);
        }
        catch (exception &e)
        {
            LOG->error() << "ActivityHandle::GetActivityInfo Execute SQL ERROR: " << sSql << endl;
            return -1;
        }

        size_t oResultsCount = oResults.size();

        if (oResultsCount < 1)
        {
            LOG->error() << "ActivityHandle::GetActivityInfo No Query Result For SQL: " << sSql << endl;
            return -1;
        }

        activityInfo.activity_id         = activity_id;
        activityInfo.name                = oResults[0][vColumns[0]];
        activityInfo.sponsor             = oResults[0][vColumns[1]];
        activityInfo.club_id             = oResults[0][vColumns[2]];
        activityInfo.target_id           = oResults[0][vColumns[3]];
        activityInfo.create_time         = oResults[0][vColumns[4]];
        activityInfo.start_time          = oResults[0][vColumns[5]];
        activityInfo.stop_time           = oResults[0][vColumns[6]];
        activityInfo.registry_start_time = oResults[0][vColumns[7]];
        activityInfo.registry_stop_time  = oResults[0][vColumns[8]];
        activityInfo.content             = oResults[0][vColumns[9]];
    }
    return 0;
}
//////////////////////////////////////////////////////

int ActivityHandle::InsertActivityRecord(const string &wx_id, const string &activity_id)
{
    string sTableName = "activity_records";
    
    TC_Mysql::RECORD_DATA mpColumns;
    mpColumns.insert(make_pair("user_id"    , make_pair(TC_Mysql::DB_STR, wx_id)));
    mpColumns.insert(make_pair("activity_id", make_pair(TC_Mysql::DB_INT, activity_id)));

    try
    {
        MDbQueryRecord::getInstance()->GetMysqlObject()->insertRecord(sTableName, mpColumns);
    }
    catch (exception &e)
    {
        LOG->error() << "ActivityHandle::InsertActivityRecord Error: " << e.what() << endl;
        return -1;
    }
    LOG->debug() << "ActivityHandle::InsertActivityRecord Inser Record: user_id " << wx_id << " activity_id " << activity_id << endl;
    return 0;
}
//////////////////////////////////////////////////////

int ActivityHandle::GetActivityRecords(int index, int batch, const string &activity_id, int &nextIndex, vector<LifeService::ActivityRecord> &recordList)
{
    nextIndex = -1;
    
    string sCondition = "`activity_id`=" + activity_id + " and `record_id`";
    // 0代表第一次请求
    if (index == 0)
        sCondition += ">=0";
    else 
        sCondition += "<" + TC_Common::tostr<int>(index);
    
    string sSql = buildSelectSQL("activity_records", vector<string>{"user_id", "record_time"}, sCondition, "record_time", DESC, batch);
    {
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
        size_t oResultsCount = oResults.size();

        // 若查询的数据小于batch, 说明以及没有更早的数据, 返回-1
        if (oResultsCount >= (size_t)batch)
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1]["record_id"]);

        for (size_t i = 0; i < oResultsCount; i++)
        {
            LifeService::ActivityRecord record;
            record.wx_id = oResults[i]["user_id"];
            record.record_time = oResults[i]["record_time"];
            record.user_name = UserHandle::getInstance()->getUserNameById(record.wx_id);

            recordList.push_back(record);
        }
    }
    
    LOG->debug() << "DataServiceImp::getActivityRecords Execute SQL: " << sSql << endl;
    return 0;
}
//////////////////////////////////////////////////////

int ActivityHandle::GetRecordCount(const string &wx_id, const string &activity_id)
{
    string sTableName = "club_managers";
    string sCondition = "where `wx_id`='" + wx_id + "' and `club_id`=" + activity_id;
    int count = 0;
    try
    {
        count = MDbQueryRecord::getInstance()->GetMysqlObject()->getRecordCount(sTableName, sCondition);
    }
    catch (exception &e)
    {
        LOG->error() << "ActivityHandle::GetRecordCount: " << e.what() << endl;
        count = -1;
        return 0;
    }
    LOG->debug() << "ActivityHandle::GetRecordCount Table: " << sTableName << " Condition: " << sCondition << endl;
    return count;
}
//////////////////////////////////////////////////////

int MsgWallHandle::InsertMessage(const LifeService::Message &msg)
{
    map<string, pair<TC_Mysql::FT, string>> mColumns;

    mColumns.insert(make_pair("user_id"  , make_pair(TC_Mysql::DB_STR, msg.user_id)));
    mColumns.insert(make_pair("receiver" , make_pair(TC_Mysql::DB_STR, msg.receiver)));
    mColumns.insert(make_pair("content"  , make_pair(TC_Mysql::DB_STR, msg.content)));
    mColumns.insert(make_pair("anonymous", make_pair(TC_Mysql::DB_INT, TC_Common::tostr<bool>(msg.anonymous))));

    string sSql = MDbQueryRecord::getInstance()->GetMysqlObject()->buildInsertSQL("message_wall", mColumns);
    // 将sql语句添加到MDbExecuteRecord类的执行队列中
    MDbExecuteRecord::getInstance()->AddExecuteSql(sSql);

    LOG->debug() << "Insert Message Wall Data " << msg.user_id << endl;

    return 0;
}
//////////////////////////////////////////////////////

int MsgWallHandle::GetMsgList(int index, int batch, const string &date, const string wx_id, int &nextIndex, vector<LifeService::Message> &msgList)
{
    nextIndex = -1;

    string sTableName = "message_wall";
    vector<string> vColumns = {"message_id", "user_id", "receiver", "content", "anonymous", "message_time", "like_count"};
    string sCondition = "`" + vColumns[0] + "`";

    // 0代表第一次请求
    if (index == 0)
        sCondition += ">=0";
    else 
        sCondition += "<" + TC_Common::tostr<int>(index);
    
    // 是否需要筛选用户
    if (wx_id != "")
        sCondition += " and `user_id`='" + wx_id + "'";

    //是否需要筛选日期信息
    if (date != "") 
        sCondition += " and to_days(`" + vColumns[5] + "`)=to_days('" + date + "')";

    // 根据创建时间排序, 从最新的留言开始查询
    string sql = buildSelectSQL(sTableName, vColumns, sCondition, vColumns[5], DESC, batch);
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
        if (oResultsCount >= (size_t)batch)
            nextIndex = TC_Common::strto<int>(oResults[oResultsCount - 1][vColumns[0]]);

        for (size_t i = 0; i < oResultsCount; i++)
        {
            LifeService::Message msg;
            msg.message_id   = oResults[i][vColumns[0]];
            msg.user_id      = oResults[i][vColumns[1]];
            msg.receiver     = oResults[i][vColumns[2]];
            msg.content      = oResults[i][vColumns[3]];
            msg.anonymous    = TC_Common::strto<bool>(oResults[i][vColumns[4]]);
            msg.message_time = oResults[i][vColumns[5]];
            msg.like_count   = TC_Common::strto<int>(oResults[i][vColumns[6]]);
            // 判断是否匿名
            if (!msg.anonymous)
                msg.user_name = UserHandle::getInstance()->getUserNameById(msg.user_id);
            
            msgList.push_back(msg);
        }
    }
    LOG->debug() << "MsgWallHandle::GetMsgList Execute SQL: " << sql << endl;    
    return 0;
}
//////////////////////////////////////////////////////

int MsgWallHandle::AddLike(const string &message_id)
{
    string sSql = "update message_wall set `like_count`=(`like_count`+1) where `message_id`=" + message_id;

    // 将sql语句添加到MDbExecuteRecord类的执行队列中
    MDbExecuteRecord::getInstance()->AddExecuteSql(sSql);
    LOG->debug() << "MsgWallHandle::AddLike AddExecuteSql: " << sSql << endl;    
    return 0;
}
//////////////////////////////////////////////////////

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
    LOG->debug() << "MsgWallHandle::GetLike AddExecuteSql: " << sSql << endl;    
    return 0;
}
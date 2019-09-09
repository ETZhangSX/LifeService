#include <sstream>
#include "util.h"

using namespace std;


string buildSelectSQL(const string &sTableName,const vector<string> &sColumns, const string &sWhereFilter)
{
    return buildSelectSQL(sTableName, sColumns, sWhereFilter, "", DEFAULT, 0);
}

string buildSelectSQL(const string &sTableName,const vector<string> &sColumns, const string &sWhereFilter, const string &orderBy, const MYSQL_Order &mysqlOrder, const int &limitNum)
{
    ostringstream sColumnNameSet;

    vector<string>::const_iterator itEnd = sColumns.end();

    for(vector<string>::const_iterator it = sColumns.begin(); it != itEnd; ++it)
    {
        if (it == sColumns.begin())
        {
            sColumnNameSet << *it;
        }
        else
        {
            sColumnNameSet << ", " << *it;
        }
    }

    ostringstream os;
    os << "select " << sColumnNameSet.str()
       << " from " << sTableName;
    if (sWhereFilter != "")
       os << " where " << sWhereFilter;

    if (orderBy != "")
    {
        os << " order by `" << orderBy << "`";
        if (mysqlOrder == ASC)
            os << " ASC";
        else if (mysqlOrder == DESC)
            os << " DESC";
    }

    if (limitNum != 0)
    {
        os << " limit " << tars::TC_Common::tostr<int>(limitNum);
    }

    return os.str();
}

string buildSelectSQL(const string &sTableName, const string &sColumn, const string &sWhereFilter)
{
    return buildSelectSQL(sTableName, sColumn, sWhereFilter, "", DEFAULT, 0);
}

string buildSelectSQL(const string &sTableName,const string &sColumn, const string &sWhereFilter, const string &orderBy, const MYSQL_Order &mysqlOrder, const int &limitNum)
{
    ostringstream os;
    
    os << "select " << sColumn
       << " from " << sTableName;
    
    if (sWhereFilter != "")
       os << " where " << sWhereFilter;
    
    if (orderBy != "")
    {
        os << " order by `" << orderBy << "`";
        if (mysqlOrder == ASC)
            os << " ASC";
        else if (mysqlOrder == DESC)
            os << " DESC";
    }

    if (limitNum != 0)
    {
        os << " limit " << tars::TC_Common::tostr<int>(limitNum);
    }
    return os.str();
}

string buildJoinSQL(const string &sTableLeft, const string &sTableRight, const MYSQL_JoinType &joinType, const vector<string> &sColumns, const string sOnFilter, const string &orderBy, const MYSQL_Order &mysqlOrder, const int &limitNum)
{
    ostringstream sColumnNameSet;

    vector<string>::const_iterator itEnd = sColumns.end();

    for(vector<string>::const_iterator it = sColumns.begin(); it != itEnd; ++it)
    {
        if (it == sColumns.begin())
        {
            sColumnNameSet << *it;
        }
        else
        {
            sColumnNameSet << ", " << *it;
        }
    }

    ostringstream os;
    os << "select " << sColumnNameSet.str()
       << " from " << sTableLeft;
    
    if (joinType == INNERJOIN)
        os << " inner join ";
    else if (joinType == LEFTJOIN)
        os << " left join ";
    else if (joinType == RIGHTJOIN)
        os << " right join ";

    os << sTableRight;
    
    if (sOnFilter != "")
       os << " on " << sOnFilter;

    if (orderBy != "")
    {
        os << " order by `" << orderBy << "`";
        if (mysqlOrder == ASC)
            os << " ASC";
        else if (mysqlOrder == DESC)
            os << " DESC";
    }

    if (limitNum != 0)
    {
        os << " limit " << tars::TC_Common::tostr<int>(limitNum);
    }

    return os.str();
}
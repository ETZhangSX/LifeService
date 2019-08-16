#include <sstream>
#include "util.h"

using namespace std;

string buildSelectSQL(const string &sTableName,const vector<string> &sColumns, const string &sWhereFilter)
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

    return os.str();
}

string buildSelectSQL(const string &sTableName,const string &sColumn, const string &sWhereFilter)
{
    ostringstream os;
    os << "select " << sColumn
       << " from " << sTableName;
    if (sWhereFilter != "")
       os << " where " << sWhereFilter;

    return os.str();
}
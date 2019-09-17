/**
 * 测试util工具
 */
#include "../util.h"
#include <vector>
#include <string>

using namespace std;

// 测试用例结构体
struct BuildSQLTest;
// 生成测试用例
vector<vector<BuildSQLTest>> SQLTestCases();
// 测试函数
void test_buildSelectSQL_simple(vector<BuildSQLTest> vTestCases);
void test_buildSelectSQL_simple_multi_columns(vector<BuildSQLTest> vTestCases);
void test_buildSelectSQL(vector<BuildSQLTest> vTestCases);
void test_buildSelectSQL_multi_columns(vector<BuildSQLTest> vTestCases);
void test_buildJoinSQL(vector<BuildSQLTest> vTestCases);

int main()
{
    vector<vector<BuildSQLTest>> vvTestCases = SQLTestCases();
    
    test_buildSelectSQL_simple(vvTestCases[0]);
    test_buildSelectSQL_simple_multi_columns(vvTestCases[1]);
    test_buildSelectSQL(vvTestCases[2]);
    test_buildSelectSQL_multi_columns(vvTestCases[3]);
    test_buildJoinSQL(vvTestCases[4]);

    return 0;
}

struct BuildSQLTest
{
    string          tableName;
    string          column;
    vector<string>  columns;
    string          whereFilter;
    string          orderBy;
    MYSQL_Order     mysqlOrder;
    int             limitNum;
    string          tableRight;
    MYSQL_JoinType  joinType;

    BuildSQLTest(string in_tableName = "",
                       string in_column = "",
                       vector<string> in_columns = {},
                       string in_whereFilter = "",
                       string in_orderBy = "",
                       MYSQL_Order in_mysqlOrder = DEFAULT,
                       int in_limitNum = 0,
                       string in_tableRight = "",
                       MYSQL_JoinType in_joinType = LEFTJOIN)
        : tableName(in_tableName),
          column(in_column),
          columns(in_columns),
          whereFilter(in_whereFilter),
          orderBy(in_orderBy),
          mysqlOrder(in_mysqlOrder),
          limitNum(in_limitNum),
          tableRight(in_tableRight),
          joinType(in_joinType)
    {
    }
};

/////////////////////////////////////////////
vector<vector<BuildSQLTest>> SQLTestCases()
{
    vector<vector<BuildSQLTest>> testCases;

    vector<BuildSQLTest> testcases_buildSelectSQL_simple;
    testcases_buildSelectSQL_simple.emplace_back("users", "wx_id", vector<string>(), "wx_id = 0", "wx_id", DEFAULT, 0);
    testCases.push_back(testcases_buildSelectSQL_simple);

    vector<BuildSQLTest> testcases_buildSelectSQL_simple_multicolumns;
    testcases_buildSelectSQL_simple_multicolumns.emplace_back("users", "", vector<string>({"wx_id", "name"}), "wx_id = 0", "wx_id", DEFAULT, 0);
    testCases.push_back(testcases_buildSelectSQL_simple_multicolumns);

    vector<BuildSQLTest> testcases_buildSelectSQL;
    testcases_buildSelectSQL.emplace_back("users", "wx_id", vector<string>(), "wx_id = 0", "wx_id", DESC, 100);
    testCases.push_back(testcases_buildSelectSQL);

    vector<BuildSQLTest> testcases_buildSelectSQL_multicolumns;
    testcases_buildSelectSQL_multicolumns.emplace_back("users", "", vector<string>({"wx_id", "name"}), "wx_id = 0", "wx_id", DESC, 100);
    testCases.push_back(testcases_buildSelectSQL_multicolumns);

    vector<BuildSQLTest> testcases_buildJoinSQL;
    testcases_buildJoinSQL.emplace_back("apply_for_club", "", vector<string>({"apply_id", "apply_time", "user_id", "club_id", "name", "avatar_url"}), "user_id=wx_id where `apply_id`>=0 and `club_id`=1 and `apply_status`=0", "apply_time", DESC, 1, "users", LEFTJOIN);
    testCases.push_back(testcases_buildJoinSQL);
    
    return testCases;
}

/////////////////////////////////////////////
void test_buildSelectSQL_simple(vector<BuildSQLTest> vTestCases)
{
    for (auto item : vTestCases)
        cout << buildSelectSQL(item.tableName, item.column, item.whereFilter) << endl;
}

/////////////////////////////////////////////
void test_buildSelectSQL_simple_multi_columns(vector<BuildSQLTest> vTestCases)
{
    for (auto item : vTestCases)
        cout << buildSelectSQL(item.tableName, item.columns, item.whereFilter) << endl;
}

/////////////////////////////////////////////
void test_buildSelectSQL(vector<BuildSQLTest> vTestCases)
{
    for (auto item : vTestCases)
        cout << buildSelectSQL(item.tableName, item.column, item.whereFilter, item.orderBy, item.mysqlOrder, item.limitNum) << endl;
}

/////////////////////////////////////////////
void test_buildSelectSQL_multi_columns(vector<BuildSQLTest> vTestCases)
{
    for (auto item : vTestCases)
        cout << buildSelectSQL(item.tableName, item.columns, item.whereFilter, item.orderBy, item.mysqlOrder, item.limitNum) << endl;
}

/////////////////////////////////////////////
void test_buildJoinSQL(vector<BuildSQLTest> vTestCases)
{
    for (auto item: vTestCases)
        cout << buildJoinSQL(item.tableName, item.tableRight, item.joinType, item.columns, item.whereFilter, item.orderBy, item.mysqlOrder, item.limitNum) << endl;
}
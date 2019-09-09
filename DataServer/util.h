#include <iostream>
#include <vector>
#include "util/tc_common.h"


enum MYSQL_Order
{
    DEFAULT,
    ASC,
    DESC
};

enum MYSQL_JoinType
{
    INNERJOIN,
    LEFTJOIN,
    RIGHTJOIN
};
/**
 * @brief 构建查询语句
 * 
 * @param sTableName    表名
 * @param sColumns      列名(多个)
 * @param sWhereFilter  where范围过滤
 * 
 * @return string   SQL语句
 */
std::string buildSelectSQL(const std::string &sTableName, const std::vector<std::string> &sColumns, const std::string &sWhereFilter);

/**
 * @brief 构建查询语句
 * 
 * @param sTableName    表名
 * @param sColumns      列名(多个)
 * @param sWhereFilter  where范围过滤
 * @param orderBy       排序字段
 * @param mysqlOrder    排序方式 ASC, DESC
 * @param limitNum      限制查询条数
 * 
 * @return string   SQL语句
 */
std::string buildSelectSQL(const std::string &sTableName, const std::vector<std::string> &sColumns, const std::string &sWhereFilter, const std::string &orderBy, const MYSQL_Order &mysqlOrder, const int &limitNum);

/**
 * @brief 构建查询语句
 * 
 * @param sTableName    表名
 * @param sColumn       列名(单个)
 * @param sWhereFilter  where范围过滤
 * 
 * @return string   SQL语句
 */
std::string buildSelectSQL(const std::string &sTableName, const std::string &sColumn, const std::string &sWhereFilter);

/**
 * @brief 构建查询语句
 * 
 * @param sTableName    表名
 * @param sColumn       列名(单个)
 * @param sWhereFilter  where范围过滤
 * @param orderBy       排序字段
 * @param mysqlOrder    排序方式 ASC, DESC
 * @param limitNum      限制查询条数
 * 
 * @return string   SQL语句
 */
std::string buildSelectSQL(const std::string &sTableName, const std::string &sColumn, const std::string &sWhereFilter, const std::string &orderBy, const MYSQL_Order &mysqlOrder, const int &limitNum);

/**
 * @brief 构建Join查询语句
 * 
 * @param sTableLeft    左表名
 * @param sTableRight   右表名
 * @param joinType      join类型
 * @param sColumn       列名(单个)
 * @param sOnFilter     on范围过滤
 * @param orderBy       排序字段
 * @param mysqlOrder    排序方式 ASC, DESC
 * @param limitNum      限制查询条数
 * 
 * @return string   SQL语句
 */
std::string buildJoinSQL(const std::string &sTableLeft, const std::string &sTableRight, const MYSQL_JoinType &joinType, const vector<std::string> &sColumns, const std::string sOnFilter, const std::string &orderBy, const MYSQL_Order &mysqlOrder, const int &limitNum);
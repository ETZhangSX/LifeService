#include <iostream>
#include <vector>

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
 * @param sColumn       列名(单个)
 * @param sWhereFilter  where范围过滤
 * 
 * @return string   SQL语句
 */
std::string buildSelectSQL(const std::string &sTableName, const std::string &sColumn, const std::string &sWhereFilter);
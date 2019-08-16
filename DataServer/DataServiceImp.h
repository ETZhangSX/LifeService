#ifndef _DataServiceImp_H_
#define _DataServiceImp_H_

#include "servant/Application.h"
#include "DataService.h"
#include <map>

/**
 *
 *
 */
class DataServiceImp : public LifeService::DataService
{
public:
    /**
     *
     */
    virtual ~DataServiceImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     * @brief 判断用户是否存在
     */
    virtual int hasUser(const std::string &wx_id, bool &sRsp, tars::TarsCurrentPtr current);

    /**
     * @brief 获取用户信息
     */
    virtual int getUserInfo(const std::string &wx_id, LifeService::UserInfo &sRsp, tars::TarsCurrentPtr current);

    /**
     * @brief 获取分组信息
     */
    virtual int getGroupInfo(map<tars::Int32, std::string> &groupInfo, tars::TarsCurrentPtr current);

    /**
     * @brief 通过用户id查询用户分组权限
     */
    virtual int getGroupByUserId(const std::string &wx_id, std::string &group, tars::TarsCurrentPtr current);

    /**
     * @brief 通过分组id查询分组
     */
    virtual int getGroupByGroupId(tars::Int32 groupId, std::string &group, tars::TarsCurrentPtr current);
    
    /**
     * @brief 向数据库插入数据
     */
    virtual int insertData(const std::string &sTableName, const vector<LifeService::Column> &sColumns, tars::TarsCurrentPtr current);
    
    /**
     * @brief 查询数据
     */
    virtual int queryData(const std::string &sTableName, const vector<std::string> &sColumns, const std::string &sCondition, vector<map<std::string, std::string>> &sRsp, tars::TarsCurrentPtr current);
};
/////////////////////////////////////////////////////
#endif

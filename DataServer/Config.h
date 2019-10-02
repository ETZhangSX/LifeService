#ifndef _LIFESERVICE_CONFIG_
#define _LIFESERVICE_CONFIG_

#include "util/tc_singleton.h"
#include "util/tc_config.h"
#include <string>

/**
 * @brief 数据库配置类
 */
class SConfig: public tars::TC_Singleton<SConfig>
{
public:
    int     usPort;
    string  strUserName;
    string  strDbHost;
    string  strPassWord;
    string  strDbName;
    string  strMsgWallDbName;
    int     maxMatch;

public:
    /**
     * @brief 加载配置文件
     * @param strConfFileName 要解析的配置文件名
     */
    void LoadConfig(const std::string &strConfFileName)
    {
        tars::TC_Config tcConfig;
        // 解析配置文件
        tcConfig.parseFile(strConfFileName);
        // 配置节点位置
        string s1 = "/LifeService/";
        // 获取配置属性
        usPort      = atoi(tcConfig.get(s1 + "<usPortConfig>", "3306").c_str());
        strDbHost   = tcConfig.get(s1 + "<strDbHostConfig>", "49.234.63.57").c_str();
        strUserName = tcConfig.get(s1 + "<strUserNameConfig>", "lifeservice").c_str();
        strPassWord = tcConfig.get(s1 + "<strPassWordConfig>", "tars@lifeservice").c_str();
        strDbName   = tcConfig.get(s1 + "<strDbNameConfig>", "db_life_service").c_str();
        maxMatch    = atoi(tcConfig.get(s1 + "<maxMatch>", "1000").c_str());
    }
};

#endif

#ifndef _LIFESERVICE_CONFIG_
#define _LIFESERVICE_CONFIG_

#include "util/tc_singleton.h"
#include "util/tc_config.h"
#include <string>

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
    void LoadConfig(const std::string &strCongFileName)
    {
        tars::TC_Config tcConfig;
        tcConfig.parseFile(strCongFileName);
        string s1 = "/LifeService/";

        usPort      = atoi(tcConfig.get(s1 + "<usPortConfig>", "3306").c_str());
        strDbHost        = tcConfig.get(s1 + "<strDbHostConfig>", "49.234.63.57").c_str();
        strUserName      = tcConfig.get(s1 + "<strUserNameConfig>", "lifeservice").c_str();
        strPassWord      = tcConfig.get(s1 + "<strPassWordConfig>", "tars@lifeservice").c_str();
        strDbName        = tcConfig.get(s1 + "<strDbNameConfig>", "db_life_service").c_str();
        // strMsgWallDbName = tcConfig.get(s1 + "<strMsgWallDbNameConfig>", "db_life_service_message_wall").c_str();
        maxMatch    = atoi(tcConfig.get(s1 + "<maxMatch>", "1000").c_str());
    }
};

#endif

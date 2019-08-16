#ifndef _DataServer_H_
#define _DataServer_H_

#include <iostream>
#include "servant/Application.h"

using namespace tars;

/**
 *
 **/
class DataServer : public Application
{
public:
    /**
     *
     **/
    virtual ~DataServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();
};

extern DataServer g_app;

////////////////////////////////////////////
#endif

#ifndef SIMPLEPLATFORM_H
#define SIMPLEPLATFORM_H

#include "platform.h"

class SimplePlatform:public Platform
{
public:
    SimplePlatform();
    virtual ~SimplePlatform();
    void setPlatform();
};

#endif // SIMPLEPLATFORM_H

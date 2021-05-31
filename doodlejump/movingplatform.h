#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include "platform.h"

class MovingPlatform: public Platform
{
public:
    MovingPlatform();
    virtual ~MovingPlatform();
    void setPlatform();
};
#endif // MOVINGPLATFORM_H

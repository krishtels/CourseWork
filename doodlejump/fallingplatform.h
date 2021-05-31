#ifndef FALLINGPLATFORM_H
#define FALLINGPLATFORM_H

#include "threat.h"

class FallingPlatform: public QObject, public Threat
{
    Q_OBJECT
public:
    FallingPlatform();
    virtual ~FallingPlatform();
    void setThreat();
};


#endif // FALLINGPLATFORM_H

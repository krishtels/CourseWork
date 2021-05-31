#ifndef MULTIPLIER_H
#define MULTIPLIER_H


#include "definition.h"
#include "gamehelper.h"

class Multiplier: public GameHelper
{
public:
    Multiplier();
    virtual ~Multiplier();
    void incrementCount();
    int count=0;
private:
    void setMultiplier();
    void changePix();
};

#endif // MULTIPLIER_H

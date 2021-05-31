#ifndef DRIVEHORIZONTALPLATFORM_H
#define DRIVEHORIZONTALPLATFORM_H

#include "platform.h"

class DriveHorizontalPlatform: public Platform
{
    Q_OBJECT
public:
    DriveHorizontalPlatform();
    virtual ~DriveHorizontalPlatform();
    void setPlatform();
    void setDirection(horizontalDirection direction);
    horizontalDirection currentDirection;
    qreal minX, maxX, current;
    int speed;
signals:
    void leftSign();
    void rightSign();
public slots:
    void movingLeft();
    void movingRight();
};
#endif // DRIVEHORIZONTALPLATFORM_H

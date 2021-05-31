#ifndef GHOST_H
#define GHOST_H

#include "threat.h"

class Ghost: public QObject, public Threat
{
    Q_OBJECT
public:
    Ghost();
    virtual ~Ghost();
    void setThreat();
    void setDirection(horizontalDirection direction);
    horizontalDirection currentDirection;
    qreal minX, maxX, current;
    int speed;
signals:
    void leftSignal();
    void rightSignal();
public slots:
    void moveLeft();
    void moveRight();
};

#endif // GHOST_H

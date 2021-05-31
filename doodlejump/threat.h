#ifndef THREAT_H
#define THREAT_H

#include <QGraphicsPixmapItem>

#include "definition.h"

class Threat: public QGraphicsPixmapItem
{
public:
    Threat();
    virtual ~Threat();
    void setCoordinate(qreal x, qreal y=-DISPLACEMENT);
protected:
    qreal xCoord, yCoord;
};

#endif // THREAT_H

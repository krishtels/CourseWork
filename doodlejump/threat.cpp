#include "threat.h"

Threat::Threat()
{
    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    setData(TYPE, THREAT);
    setZValue(1.8);
}

Threat::~Threat()
{
}

void Threat::setCoordinate(qreal x, qreal y)
{
    xCoord=x;
    yCoord=y;
}

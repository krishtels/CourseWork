#include "platform.h"

Platform::Platform()
{
    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    setData(TYPE, PLATFORM);
}

void Platform::setCoordinates(qreal x, qreal y){
    xCoord = x;
    yCoord = y;
}

qreal Platform::X() const{
    return xCoord;
}

qreal Platform::Y() const{
    return yCoord;
}

int Platform::getHeight() const{
    return platformHeight;
}

Platform::~Platform()
{
}

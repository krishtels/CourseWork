#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>

#include "definition.h"

class Platform: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Platform();
    virtual ~Platform();
    void setCoordinates(qreal x, qreal y);
    qreal X() const;
    qreal Y() const;
    int getHeight() const;
protected:
    qreal xCoord, yCoord;
    int platformHeight;
};

#endif // PLATFORM_H

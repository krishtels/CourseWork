#ifndef GAMEHELPER_H
#define GAMEHELPER_H

#include <QGraphicsPixmapItem>

#include "definition.h"

class GameHelper: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameHelper();
    virtual ~GameHelper();
};

#endif // GAMEHELPER_H

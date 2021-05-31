#ifndef ATTACK_H
#define ATTACK_H


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "ghost.h"

class Attack: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Attack();
public slots:
    void move();
};

#endif // ATTACK_H

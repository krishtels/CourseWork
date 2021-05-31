#include "attack.h"

Attack::Attack()
{
    setShapeMode(HeuristicMaskShape);
    setPixmap(QPixmap(ATTACK_PATH));
    QTimer *timer = new QTimer();
    timer->start(16);
    setData(TYPE, ATTACK);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
}

void Attack::move()
{
    QList<QGraphicsItem*> collisions=this->collidingItems();
    if(!scene()->collidingItems(this).isEmpty()){
        foreach(QGraphicsItem *collidingItem, collisions){
            if(collidingItem->data(TYPE)==THREAT){
                scene()->removeItem(collidingItem);
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
    }
    setPos(x(), y()-10);
    if(y()<=0-pixmap().height()){
        scene()->removeItem(this);
        delete this;

    }
}

#include "playdoodle.h"
#include "gamecontrol.h"

PlayDoodle::PlayDoodle(GameControl &control):
    controller(control),
    currentDirection(DOWN),
    movingDirection(STOP),
    initialSpeed(20),
    gravity(0.65)
{
    connect(this, SIGNAL(upSignal()), this, SLOT(moveUp()));
    connect(this, SIGNAL(downSignal()), this, SLOT(moveDown()));
    connect(this, SIGNAL(leftSignal()), this, SLOT(moveLeft()));
    connect(this, SIGNAL(rightSignal()), this, SLOT(moveRight()));
    setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    setZValue(2);
    deltaY=initialSpeed;
    QPixmap pixmap;
    bool success = pixmap.load(PLAYER_RIGHT_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLAYER_WIDTH));
    playerHeight=pixmap.scaledToWidth(PLAYER_WIDTH).height();
}

void PlayDoodle::moveDirection(horizontalDirection direction)
{
    movingDirection=direction;
}

bool PlayDoodle::checkMovingDirection(horizontalDirection direction)
{
    return direction==movingDirection;
}

bool PlayDoodle::meetPlatform()
{
    QList<QGraphicsItem *> collisions=this->collidingItems();
    if(scene()->collidingItems(this).isEmpty()){
        return false;
    }
    else{
        foreach(QGraphicsItem *collidingItem, collisions){
            if(collidingItem->data(TYPE)==PLATFORM && collidingItem->y() - playerHeight + DISPLACEMENT>=y()){
                    distanceToGround=VIEW_HEIGHT-collidingItem->y();
                    previousY=static_cast<Platform *>(collidingItem)->Y();
                    if(collidingItem->data(PLATFORM_TYPE)==STOPING)
                        boostFactor=0;
                    else if(collidingItem->data(PLATFORM_TYPE)==MOVING)
                        boostFactor=2;
                    else if(collidingItem->data(PLATFORM_TYPE)==DRIVE)
                        boostFactor=1;
                    else
                        boostFactor=1;
                return true;
            }
        }
        return false;
    }
}

bool PlayDoodle::meetThreats()
{
    QList<QGraphicsItem *> collisions=this->collidingItems();
    if(scene()->collidingItems(this).isEmpty()){
        return false;
    }
    else{
        foreach(QGraphicsItem *collidingItem, collisions){
            if(collidingItem->data(TYPE)==THREAT){
                if(currentDirection==DOWN){
                    jump();
                    if(collidingItem->data(THREAT_TYPE)==GHOST){
                        scene()->removeItem(collidingItem);
                        Ghost *ghost=static_cast<Ghost *>(collidingItem);
                        ghost->minX=-1*rand()%MOVE_RANGE;
                        ghost->maxX=-1*ghost->minX;
                        ghost->speed=rand()%3+1;
                        ghost->setY(-1*((rand()%(VIEW_HEIGHT*GHOST_RARITY)-DISPLACEMENT)));
                        ghost->setPos(rand()%(VIEW_WIDTH/2-GHOST_WIDTH/2)+(VIEW_WIDTH/4-GHOST_WIDTH/2), -1*rand()%(VIEW_HEIGHT*GHOST_RARITY)-VIEW_HEIGHT);
                        scene()->addItem(collidingItem);
                    }
                    else if(collidingItem->data(THREAT_TYPE)==FALLING_PLATFORM){
                        scene()->removeItem(collidingItem);
                        collidingItem->setPos(rand()%(VIEW_WIDTH-PLATFORM_WIDTH)+PLATFORM_WIDTH, -1*rand()%(VIEW_HEIGHT*FALLING_PLATFORM_RARITY));
                        scene()->addItem(collidingItem);
                    }
                    return false;
                }
                return true;
             }
        }
        return false;
    }
}

double PlayDoodle::getDeltaY() const
{
    return deltaY;
}

void PlayDoodle::jump()
{
    setMoveVertDirection(UP);
    deltaY=initialSpeed*boostFactor*springBootsFactor;
}

void PlayDoodle::setMoveVertDirection(verticalDirection direction)
{
    currentDirection=direction;
}

qreal PlayDoodle::getDistanceToGround() const
{
    return distanceToGround;
}

verticalDirection PlayDoodle::getCurrentDirection() const
{
    return currentDirection;
}

qreal PlayDoodle::getPlayerHeight() const
{
    return playerHeight;
}

double PlayDoodle::getGravity() const
{
    return gravity;
}

void PlayDoodle::setDeltaY(double value)
{
    deltaY = value;
}

void PlayDoodle::moveUp()
{
    deltaY-=gravity;
    setPos(x(), y()-deltaY);
    if(deltaY<=0){
        setMoveVertDirection(DOWN);
        deltaY=0;
    }
}

void PlayDoodle::moveDown()
{
    deltaY+=gravity;
    setPos(x(), y()+deltaY);
    if((y()+playerHeight)>VIEW_HEIGHT){
        emit controller.gameOver();
    }
    boostFactor=1;
}

void PlayDoodle::moveLeft()
{
    QPixmap pixmap;
    bool success = pixmap.load(PLAYER_LEFT_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLAYER_WIDTH));
    setPos(x()-8,y());
    if(x()+PLAYER_WIDTH/2<=0){
        setPos(VIEW_WIDTH-PLAYER_WIDTH/2,y());
    }
}

void PlayDoodle::moveRight()
{
    QPixmap pixmap;
    bool success = pixmap.load(PLAYER_RIGHT_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(PLAYER_WIDTH));
    setPos(x()+8,y());
    if(x()>=VIEW_WIDTH-PLAYER_WIDTH/2){
        setPos(-1*PLAYER_WIDTH/2,y());
    }
}

void PlayDoodle::advance(int phase)
{
    if(!phase){
        return;
    }
    switch(currentDirection){
        case UP:
            emit upSignal();
            break;
        case DOWN:
            emit downSignal();
            if(meetPlatform()){
                jump();
            }
            break;
    }
    switch(movingDirection){
        case LEFT:
            emit leftSignal();
            break;
        case RIGHT:
            emit rightSignal();
            break;
        case STOP:
            break;
    }
    if(meetThreats()){
        emit controller.gameOver();
    }
    meetMultiplier();
}

void PlayDoodle::meetMultiplier()
{
    QList<QGraphicsItem *> collisions=this->collidingItems();
    if(scene()->collidingItems(this).isEmpty()){
        return;
    }
    else{
        foreach(QGraphicsItem *collidingItem, collisions){
            if(collidingItem->data(TYPE)==GAMEHELPER){
                if(collidingItem->data(GAMEHELPER_TYPE)==MULTIPLIER){
                    controller.multiplier->incrementCount();
                    if(controller.multiplier->count>=5){
                        scene()->removeItem(controller.multiplier);
                    }
                    else{
                        collidingItem->setPos(rand()%(VIEW_WIDTH-GHOST_WIDTH)+GHOST_WIDTH,
                                               -1*rand()%(VIEW_HEIGHT*MULTIPLIER_RARITY));
                    }
                }
                else if(collidingItem->data(GAMEHELPER_TYPE)==SPRING_BOOTS){
                    springBootsFactor==2?springBootsFactor=1:springBootsFactor=2;
                    scene()->removeItem(collidingItem);
                    controller.bootsNotInScene=true;
                }
            }
        }
    }
}

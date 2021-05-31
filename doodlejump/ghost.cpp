#include "ghost.h"

Ghost::Ghost():Threat(),
    currentDirection(RIGHT),
    current(0),
    speed(1)
{
    srand(time(NULL));
    minX=-1*rand()%MOVE_RANGE;
    maxX=-1*minX;
    connect(this, SIGNAL(leftSignal()), this, SLOT(moveLeft()));
    connect(this, SIGNAL(rightSignal()), this, SLOT(moveRight()));
    setThreat();
}

Ghost::~Ghost()
{
}

void Ghost::setThreat()
{
    QPixmap pixmap;
    bool success = pixmap.load(GHOST_PATH);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(GHOST_WIDTH));
    setData(THREAT_TYPE, GHOST);
}

void Ghost::setDirection(horizontalDirection direction)
{
    currentDirection=direction;
}

void Ghost::moveLeft()
{
    current-=1;
}

void Ghost::moveRight()
{
    current+=1;
}

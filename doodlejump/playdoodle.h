#ifndef PLAYDOODLE_H
#define PLAYDOODLE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <vector>

#include "definition.h"

class GameControl;

class PlayDoodle: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PlayDoodle(GameControl &control);
    void moveDirection(horizontalDirection direction);
    bool checkMovingDirection(horizontalDirection direction);
    bool meetPlatform();
    bool meetThreats();
    void meetMultiplier();
    double getDeltaY() const;
    void jump();
    void setDeltaY(double value);
    void setMoveVertDirection(verticalDirection direction);
    qreal getDistanceToGround() const;
    verticalDirection getCurrentDirection() const;
    qreal getPlayerHeight() const;
    double getGravity() const;
    double previousY;
private:
    GameControl &controller;
    qreal playerHeight, distanceToGround;
    verticalDirection currentDirection;
    horizontalDirection movingDirection;
    const double initialSpeed, gravity;
    double deltaY=25;
    int boostFactor=1;
    int springBootsFactor=1;
signals:
    void upSignal();
    void downSignal();
    void leftSignal();
    void rightSignal();
public slots:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
protected:
    void advance(int phase);
};


#endif // PLAYDOODLE_H

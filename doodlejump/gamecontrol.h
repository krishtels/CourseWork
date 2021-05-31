#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QApplication>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include <QFont>
#include <vector>

#include "playdoodle.h"
#include "button.h"
#include "mainwindow.h"
#include "ghost.h"
#include "fallingplatform.h"
#include "attack.h"
#include "multiplier.h"
#include "springboots.h"
#include "platform.h"
#include "simpleplatform.h"
#include "stopplatform.h"
#include "movingplatform.h"
#include "mainwindow.h"
#include "drivehorizontalplatform.h"

class GameControl: public QObject
{
    Q_OBJECT
public:
    GameControl();
    GameControl(QGraphicsScene &scene, QGraphicsView &view, MainWindow *window,  QObject *parent=nullptr);
    QGraphicsItemGroup *platformGroup;
    Multiplier *multiplier;
    bool bootsNotInScene=true;
    virtual ~GameControl();
    MainWindow* currentWindow = nullptr;
private:
    std::vector<Platform *> platforms;
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);
    Platform *randomPlatform();
    void initialize();
    void initPlayer();
    void initPlatform();
    void initGhost();
    void initFallingPlatform();
    void initMultiplier();
    void initGameOverScene();
    void initDrivePlatform();
    void showScore();
    void setMultiplier();
    QGraphicsScene *tempScene, &scene, *pauseScene, *gameOverScene;
    QGraphicsView *tempView, &view;
    QList<QGraphicsItem *> platformList;
    QTimer *timer;
    QGraphicsTextItem *label;
    PlayDoodle *playDoodle;
    Attack *attack;
    Ghost *ghost;
    FallingPlatform *fallingPlatform;
    DriveHorizontalPlatform *drivePlatform;
    SpringBoots *springBoots;
    bool paused=false;
    double fallingPlatformSpeed;
    int score;
    int multipliers[5];
    bool trackerFall;
signals:
    void gameOver();
    void scoreUpdated();
public slots:
    void moveCamera();
    void objectMovementGeneration();
    void generatePlatform();
    void moveGhost();
    void generateDrivePlatform();
    void movePlatform();
    void generateGhost();
    void moveFallingPlatform();
    void generateFallingPlatform();
    void generateMultiplier();
    void removeSpringBoots();
    void addScore();
    void setScore();
    void gameOverSlot();
protected:
    bool eventFilter(QObject *object, QEvent *event);
    void advance(int phase);
};
#endif // GAMECONTROL_H

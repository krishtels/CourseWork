#include "gamecontrol.h"
#include <windows.h>

Platform* GameControl::randomPlatform()
{
    int index=rand()%50;
    if(trackerFall==false){
        index<2?index=STOPING:(index<10?index=MOVING:index=SIMPLE);
    }
    else{
        index<4?index=MOVING:index=SIMPLE;
    }
    Platform *platform;

    switch(index){
        case MOVING:
            platform = new MovingPlatform;
            trackerFall=false;
            break;
        case STOPING:
            platform = new StopPlatform;
            trackerFall=true;
            break;
        default:
            platform = new SimplePlatform;
            trackerFall=false;
            break;
    }
    return platform;
}

GameControl::GameControl():
    tempScene(new QGraphicsScene(this)),
    scene(*tempScene),
    tempView(new QGraphicsView()),
    view(*tempView)
{

}

GameControl::GameControl(QGraphicsScene &scene, QGraphicsView &view, QObject *parent, MainWindow *window):
    QObject(parent),
    multiplier(new Multiplier()),
    scene(scene),
    pauseScene(new QGraphicsScene(this)),
    gameOverScene(new QGraphicsScene(this)),
    view(view),
    timer(new QTimer(this)),
    label(new QGraphicsTextItem),
    playDoodle(new PlayDoodle(*this)),
    ghost(new Ghost()),
    fallingPlatform(new FallingPlatform()),
    drivePlatform(new DriveHorizontalPlatform()),
    springBoots(new SpringBoots()),
    score(0)
{
    trackerFall=false;
    setMultiplier();
    srand(time(NULL));
    scene.installEventFilter(this);
    currentWindow = window;
    label->setPlainText(QString::number(score));
    timer->start(16);
    connect(timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    connect(timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
    connect(timer, SIGNAL(timeout()), this, SLOT(objectMovementGeneration()));
    connect(timer, SIGNAL(timeout()), ghost, SLOT(moveLeft()));
    connect(timer, SIGNAL(timeout()), ghost, SLOT(moveRight()));
    connect(timer, SIGNAL(timeout()), drivePlatform, SLOT(movingLeft()));
    connect(timer, SIGNAL(timeout()), drivePlatform, SLOT(movingRight()));
    connect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));
    connect(this, SIGNAL(scoreUpdated()), this, SLOT(setScore()));
    initialize();
    showScore();
}

GameControl::~GameControl()
{
}


void GameControl::handleKeyPressed(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Left:
            playDoodle->moveDirection(LEFT);
            break;
        case Qt::Key_Right:
            playDoodle->moveDirection(RIGHT);
            break;
        case Qt::Key_Escape:
            if(paused==false){
                disconnect(timer, SIGNAL(timeout()), &scene, SLOT(advance()));
                disconnect(timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
                disconnect(timer, SIGNAL(timeout()), this, SLOT(objectMovementGeneration()));
                disconnect(timer, SIGNAL(timeout()), ghost, SLOT(moveLeft()));
                disconnect(timer, SIGNAL(timeout()), ghost, SLOT(moveRight()));
                disconnect(timer, SIGNAL(timeout()), drivePlatform, SLOT(movingLeft()));
                disconnect(timer, SIGNAL(timeout()), drivePlatform, SLOT(movingRight()));
                disconnect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));
                paused=true;
            }
            else{
                connect(timer, SIGNAL(timeout()), &scene, SLOT(advance()));
                connect(timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
                connect(timer, SIGNAL(timeout()), this, SLOT(objectMovementGeneration()));
                connect(timer, SIGNAL(timeout()), ghost, SLOT(moveLeft()));
                connect(timer, SIGNAL(timeout()), ghost, SLOT(moveRight()));
                connect(timer, SIGNAL(timeout()), drivePlatform, SLOT(movingLeft()));
                connect(timer, SIGNAL(timeout()), drivePlatform, SLOT(movingRight()));
                connect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));
                paused=false;
            }
            break;
        case Qt::Key_Space:
            if(paused==false){
                QPixmap pixmap;
                bool success = pixmap.load(PLAYER_SHOOT_PATH);
                if (!success){
                    exit(-1);
                }
                playDoodle->setPixmap(pixmap.scaledToWidth(PLAYER_WIDTH));
                attack=new Attack();
                attack->setPos(playDoodle->x()-5, playDoodle->y()-playDoodle->getPlayerHeight()/2);
                scene.addItem(attack);

            }
            break;
    }
}

void GameControl::handleKeyRelease(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Left:
            if(playDoodle->checkMovingDirection(LEFT))
                playDoodle->moveDirection(STOP);
            break;
        case Qt::Key_Right:
            if(playDoodle->checkMovingDirection(RIGHT))
                playDoodle->moveDirection(STOP);
            break;
    }
}

void GameControl::initialize()
{
    initPlayer();
    initPlatform();
    initGhost();
    initDrivePlatform();
    initFallingPlatform();
    initMultiplier();
    initGameOverScene();
}

void GameControl::initPlayer()
{
    playDoodle->setPos(VIEW_WIDTH/2-PLAYER_WIDTH/2,VIEW_HEIGHT/2);
    scene.addItem(playDoodle);
}

void GameControl::initPlatform()
{
    Platform *platform;
    for(int i=0; i<PLATFORM_ONSCREEN; i++){
        if (i==0){
            platform=new SimplePlatform;
        } else {
            platform = randomPlatform();
        }
        platforms.push_back(platform);
        if (i==0){
            platforms[i]->setCoordinates(VIEW_WIDTH/2-PLATFORM_WIDTH/2,VIEW_HEIGHT-platforms[i]->getHeight());
        } else {
            platforms[i]->setCoordinates(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),(VIEW_HEIGHT-platforms[i]->getHeight())-i*((VIEW_HEIGHT-platforms[i]->getHeight())/PLATFORM_ONSCREEN));
        }
        platforms[i]->setPos(platforms[i]->X(),platforms[i]->Y());
        platformList.append(platforms[i]);
    }
    platformGroup=scene.createItemGroup(platformList);
}

void GameControl::initDrivePlatform()
{
    scene.addItem(drivePlatform);
    drivePlatform->setCoordinates(VIEW_WIDTH/2-PLATFORM_WIDTH/2,-1*rand()%(VIEW_HEIGHT*DRIVE_PLATFORM_RARITY));
     drivePlatform->setPos(drivePlatform->X(),drivePlatform->Y());
}

void GameControl::initGhost(){
    scene.addItem(ghost);
    ghost->setPos(rand()%(VIEW_WIDTH/2-GHOST_WIDTH/2)+(VIEW_WIDTH/4-GHOST_WIDTH/2), -1*rand()%(VIEW_HEIGHT*GHOST_RARITY)-VIEW_HEIGHT);
}
void GameControl::initFallingPlatform()
{
    scene.addItem(fallingPlatform);
    fallingPlatform->setPos(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),-1*rand()%(VIEW_HEIGHT*FALLING_PLATFORM_RARITY));
}

void GameControl::initMultiplier()
{
    scene.addItem(multiplier);
    multiplier->setPos(rand()%(VIEW_WIDTH-GHOST_WIDTH),-1*rand()%(VIEW_HEIGHT*MULTIPLIER_RARITY));
}

void GameControl::initGameOverScene()
{
    gameOverScene->setBackgroundBrush(QBrush(QImage(BACKGROUND_LOSE_PATH)));
}

void GameControl::showScore()
{
    label->setFont(QFont("courier", 35));
    label->setDefaultTextColor(Qt::black);
    label->setPos(DISPLACEMENT,DISPLACEMENT);
    label->setZValue(2);
    scene.addItem(label);
}

void GameControl::setMultiplier()
{
    multipliers[0]=1;
    multipliers[1]=3;
    multipliers[2]=5;
    multipliers[3]=10;
    multipliers[4]=20;
}

void GameControl::setScore()
{
    label->setPlainText(QString::number(score));
}

void GameControl::moveCamera()
{
    if(playDoodle->y()<VIEW_HEIGHT/2-playDoodle->getPlayerHeight()){
        playDoodle->setY(VIEW_HEIGHT/2-playDoodle->getPlayerHeight());
        std::vector<Platform*>::iterator it=platforms.begin();
        for(int i=0;it!=platforms.end();it++, i++){
            if(playDoodle->getCurrentDirection()==UP){
                platforms[i]->setY(platforms[i]->y()+playDoodle->getDeltaY());
            }
        }
        ghost->setY(ghost->y()+playDoodle->getDeltaY());
        drivePlatform->setY(drivePlatform->y()+playDoodle->getDeltaY());
        fallingPlatform->setY(fallingPlatform->y()+playDoodle->getDeltaY());
        multiplier->setY(multiplier->y()+playDoodle->getDeltaY());
        springBoots->setY(springBoots->y()+playDoodle->getDeltaY());
        addScore();
    }
}

void GameControl::objectMovementGeneration()
{
    generatePlatform();
    moveGhost();
    generateGhost();
    movePlatform();
    generateDrivePlatform();
    moveFallingPlatform();
    generateFallingPlatform();
    generateMultiplier();
    removeSpringBoots();
}

void GameControl::generatePlatform()
{
    bool withBoots;
    withBoots=(rand()%SPRING_BOOTS_RARITY==0);
    if(platforms[0]->y()>=VIEW_HEIGHT){
        double temp= VIEW_HEIGHT-platforms[0]->y();
        platformList.removeAt(0);
        platforms.erase(platforms.begin());
        platforms.push_back(randomPlatform());
        platforms.back()->setCoordinates(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),-1*temp);
        platforms.back()->setPos(platforms.back()->X(),platforms.back()->Y());
        if(withBoots && bootsNotInScene ){
            springBoots->setPos(platforms.back()->x()+PLATFORM_WIDTH/2-SPRING_BOOTS_WIDTH/2,platforms.back()->y()-DISPLACEMENT*2);
            scene.addItem(springBoots);
            bootsNotInScene=false;
        }
        platformList.append(platforms.back());
    }
    scene.destroyItemGroup(platformGroup);
    platformGroup=scene.createItemGroup(platformList);
}

void GameControl::moveGhost()
{
    switch(ghost->currentDirection){
        case LEFT:
            emit ghost->leftSignal();
            break;
        case RIGHT:
            emit ghost->rightSignal();
            break;
        default:
            break;
    }
    if(ghost->current<ghost->minX){
        ghost->currentDirection=RIGHT;
    }
    else if(ghost->current>ghost->maxX){
        ghost->currentDirection=LEFT;
    }
    if(ghost->current>0){
        ghost->setX(ghost->x()-ghost->speed);
    }
    else {
        ghost->setX(ghost->x()+ghost->speed);
    }
    if(ghost->x()>=VIEW_WIDTH-GHOST_WIDTH/2){
        ghost->setX(-1*GHOST_WIDTH/2);
    }
    else if(ghost->x()+GHOST_WIDTH/2<=0){
        ghost->setX(VIEW_WIDTH-GHOST_WIDTH/2);
    }

}

void GameControl::generateGhost()
{
    if(ghost->y()>=VIEW_HEIGHT+DISPLACEMENT){
        ghost->minX=-1*rand()%MOVE_RANGE;
        ghost->maxX=-1*ghost->minX;
        ghost->speed=rand()%3+1;
        ghost->setY(-1*((rand()%(VIEW_HEIGHT*GHOST_RARITY)-DISPLACEMENT)));
        ghost->setPos(rand()%(VIEW_WIDTH/2-GHOST_WIDTH/2)+(VIEW_WIDTH/4-GHOST_WIDTH/2),-1*rand()%(VIEW_HEIGHT*GHOST_RARITY)-VIEW_HEIGHT);
    }
}

void GameControl::movePlatform()
{
    switch(drivePlatform->currentDirection){
        case LEFT:
            emit drivePlatform->leftSign();
            break;
        case RIGHT:
            emit drivePlatform->rightSign();
            break;
        default:
            break;
    }
    if(drivePlatform->current<drivePlatform->minX){
        drivePlatform->currentDirection=RIGHT;
    }
    else if(drivePlatform->current>drivePlatform->maxX){
        drivePlatform->currentDirection=LEFT;
    }
    if(drivePlatform->current>0){
        drivePlatform->setX(drivePlatform->x()-drivePlatform->speed);
    }
    else {
        drivePlatform->setX(drivePlatform->x()+drivePlatform->speed);
    }
    if(drivePlatform->x()>=VIEW_WIDTH-PLATFORM_WIDTH/2){
        drivePlatform->setX(-1*PLATFORM_WIDTH/2);
    }
    else if(drivePlatform->x()+PLATFORM_WIDTH/2<=0){
        drivePlatform->setX(VIEW_WIDTH-PLATFORM_WIDTH/2);
    }

}

void GameControl::generateDrivePlatform()
{
    if(drivePlatform->y()>=VIEW_HEIGHT+DISPLACEMENT){
        drivePlatform->minX=-1*rand()%PLATFORM_RANGE;
        drivePlatform->maxX=-1*drivePlatform->minX;
        drivePlatform->speed=rand()%2 + 1 +rand()%5;
        drivePlatform->setY(-1*((rand()%(VIEW_HEIGHT*DRIVE_PLATFORM_RARITY)-DISPLACEMENT)));
        drivePlatform->setCoordinates(VIEW_WIDTH/2-PLATFORM_WIDTH/2,-1*rand()%(VIEW_HEIGHT*DRIVE_PLATFORM_RARITY));
        drivePlatform->setPos(drivePlatform->X(),drivePlatform->Y());
    }
}

void GameControl::moveFallingPlatform()
{
    fallingPlatform->setY(fallingPlatform->y()+10);
}

void GameControl::generateFallingPlatform()
{
    if(fallingPlatform->y()>=VIEW_HEIGHT+DISPLACEMENT){
        fallingPlatform->setPos(rand()%(VIEW_WIDTH-PLATFORM_WIDTH),-1*rand()%(VIEW_HEIGHT*FALLING_PLATFORM_RARITY));
    }
}

void GameControl::generateMultiplier()
{
    if(multiplier->y()>=VIEW_HEIGHT+DISPLACEMENT){
        multiplier->setPos(rand()%(VIEW_WIDTH-GHOST_WIDTH), -1*rand()%(VIEW_HEIGHT*MULTIPLIER_RARITY));
    }
}

void GameControl::removeSpringBoots()
{
    if(springBoots->y()>=VIEW_HEIGHT+DISPLACEMENT && bootsNotInScene==false){
        scene.removeItem(springBoots);
        bootsNotInScene=true;
    }
}

void GameControl::addScore()
{
    if (multiplier->count<5){
        score+=playDoodle->getDeltaY()*multipliers[multiplier->count];
    } else {
        score+=playDoodle->getDeltaY()*multipliers[4];
    }
    emit scoreUpdated();
}

void GameControl::gameOverSlot()
{
    Sleep(500);
    QMediaPlayer * player = new QMediaPlayer(this);
    QMediaPlaylist * playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    playlist->addMedia(QUrl("qrc:/resource/lose.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    player->play();
    disconnect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(generatePlatform()));
    if (currentWindow!=nullptr){
        if (currentWindow->getBestScore()<score){
            currentWindow->setBestScore(score);
        }
    }
    label->setFont(QFont("Times", 20, QFont::Bold));
    label->setDefaultTextColor(Qt::red);
    label->setPos(400 ,DISPLACEMENT+30);
    label->setZValue(2);
    label->setTextWidth(VIEW_WIDTH-DISPLACEMENT/2);
    gameOverScene->addItem(label);
    QGraphicsTextItem *label2 = new QGraphicsTextItem;
    if (currentWindow!=nullptr){
        label2->setPlainText(QString::number(currentWindow->getBestScore()));
    } else {
        label2->setPlainText(QString::number(0));
    }
    label2->setFont(QFont("Times", 20, QFont::Bold));
    label2->setDefaultTextColor(Qt::red);
    label2->setPos(400 ,DISPLACEMENT+165);
    label2->setZValue(2);
    label2->setTextWidth(VIEW_WIDTH-DISPLACEMENT/2);
    gameOverScene->addItem(label2);
    Button *menuButton = new Button(MENU_PATH, MENU_COVER_PATH);
    menuButton->setZValue(4);
    gameOverScene->addItem(menuButton);
    menuButton->setPos(3*VIEW_WIDTH/4-BUTTON_WIDTH/2, 575);
    connect(menuButton, SIGNAL(clicked()), QApplication::activeWindow(), SLOT(showMainMenu()));
    Button *playButton = new Button(PLAY_PATH, PLAY_COVER_PATH);
    playButton->setZValue(4);
    gameOverScene->addItem(playButton);
    playButton->setPos(VIEW_WIDTH/4-BUTTON_WIDTH/2, 575);
    connect(playButton, SIGNAL(clicked()), QApplication::activeWindow(), SLOT(newGame()));
    view.setScene(gameOverScene);
}

bool GameControl::eventFilter(QObject *object, QEvent *event)
{
    if(event->type()==QEvent::KeyPress){
        handleKeyPressed(static_cast<QKeyEvent *>(event));
        return true;
    }
    else if(event->type()==QEvent::KeyRelease){
        handleKeyRelease(static_cast<QKeyEvent *>(event));
        return true;
    }
    else{
        return QObject::eventFilter(object, event);
    }
}

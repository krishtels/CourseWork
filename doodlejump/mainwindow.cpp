#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontrol.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      scene(new QGraphicsScene(this)),
      mainScene(new QGraphicsScene(this)),
      view(new QGraphicsView(this)),
      control(new GameControl())
{
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    startingScene();
    showMainMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getBestScore(){
    return bestScore;
}

MainWindow* MainWindow::getWindow(){
    return this;
}

void MainWindow::setBestScore(int score){
    bestScore = score;
}
void MainWindow::changeScene(QGraphicsScene *scene)
{
    view->setScene(scene);
}

void MainWindow::showMainMenu()
{
    mainScene->setBackgroundBrush(QBrush(QImage(MAIN_MENU_PATH)));
    Button *playButton = new Button(PLAY_PATH, PLAY_COVER_PATH);
    mainScene->addItem(playButton);
    playButton->setPos(3*VIEW_WIDTH/4-BUTTON_WIDTH/2, 575);
    connect(playButton, SIGNAL(clicked()), this, SLOT(newGame()));
    changeScene(mainScene);
    playlist->addMedia(QUrl("qrc:/resource/start.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->play();
}

void MainWindow::newGame()
{
    player->stop();
    scene->clear();
    delete control;
    control=new GameControl(*scene, *view, this, this);
    startGame();
}

void MainWindow::startingScene()
{
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(VIEW_WIDTH,VIEW_HEIGHT);
    view->setSceneRect(0,0,VIEW_WIDTH,VIEW_HEIGHT);
    view->fitInView(0,0,VIEW_WIDTH,VIEW_HEIGHT,Qt::KeepAspectRatio);
    ui->setupUi(this);
    setCentralWidget(view);
}

void MainWindow::startGame()
{
    scene->setBackgroundBrush(QBrush(QImage(BACKGROUND_PATH)));
    changeScene(scene);
}

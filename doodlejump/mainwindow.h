#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "definition.h"

class GameControl;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeScene(QGraphicsScene *scene);
    int getBestScore();
    void setBestScore(int score);
    MainWindow* getWindow();
public slots:
    void showMainMenu();
    void newGame();
private:
    Ui::MainWindow *ui;
    void startingScene();
    void startGame();
    int bestScore = 0;
    QGraphicsScene *scene, *mainScene;
    QGraphicsView *view;
    GameControl *control;
    QMediaPlayer * player;
    QMediaPlaylist * playlist;
};
#endif // MAINWINDOW_H

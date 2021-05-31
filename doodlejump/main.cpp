#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(VIEW_WIDTH, VIEW_HEIGHT);
    w.show();
    return a.exec();
}

#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "definition.h"

class Button: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Button(QString firstPath, QString coverPath, QGraphicsItem *parent=nullptr);
signals:
    void clicked();
private:
    QString firstPath, coverPath;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
};
#endif // BUTTON_H

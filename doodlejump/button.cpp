#include "button.h"

Button::Button(QString firstPath, QString coverPath, QGraphicsItem *parent):
    QGraphicsPixmapItem (parent),
    firstPath(firstPath),
    coverPath(coverPath)
{
    setAcceptHoverEvents(true);
    QPixmap pixmap;
    bool success = pixmap.load(firstPath);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(BUTTON_WIDTH));
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    QPixmap pixmap;
    bool success = pixmap.load(coverPath);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(BUTTON_WIDTH));
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    QPixmap pixmap;
    bool success = pixmap.load(firstPath);
    if (!success){
        exit(-1);
    }
    setPixmap(pixmap.scaledToWidth(BUTTON_WIDTH));
}

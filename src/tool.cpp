#include "tool.h"

Tool::Tool(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
}

void Tool::setScene(QGraphicsSceneCustom *sceneCm)
{
    this->sceneCm = sceneCm;
}

QGraphicsSceneCustom* Tool::getSceneCm()
{
    return this->sceneCm;
}

QRectF Tool::boundingRect() const
{
    return this->pixmap().rect();
}

void Tool::advance(int)
{
    if(this->scene()->collidingItems(this).empty()) {
        return;
    }

    foreach (QGraphicsItem *t, this->scene()->collidingItems(this)) {
        emit collidingItem(t);
    }
}

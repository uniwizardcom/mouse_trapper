#include "traphole.h"
#include "mouse.h"

TrapHole::TrapHole(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    this->setPixmap(QPixmap(":/images/trap_hole.png").scaledToHeight(100));
}

QRectF TrapHole::boundingRect() const
{
    return this->pixmap().rect();
}

void TrapHole::advance(int step)
{
    if(this->scene()->collidingItems(this).empty()) {
        return;
    }

    foreach (QGraphicsItem *t, this->scene()->collidingItems(this)) {
        if(t && Mouse::isQGraphicsItem(t)) {
            this->scene()->removeItem(t);
            emit miceInHole();
        }
    }
}

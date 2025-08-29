#include "traphole.h"
#include "../sprites/mouse.h"

Tools::TrapHole::TrapHole(QObject *parent) : Tool(parent)
{
    this->setPixmap(QPixmap(":/images/dziura_2.png").scaledToHeight(100));
    QObject::connect(this, &Tool::collidingItem, this, &Tools::TrapHole::collition);
}

void Tools::TrapHole::collition(QGraphicsItem *t)
{
    if(Sprites::Mouse::isQGraphicsItem(t)) {
        ((Sprites::Mouse*)t)->goAway();
    }
}

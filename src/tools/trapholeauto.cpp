#include "trapholeauto.h"
#include "../sprites/mouse.h"

Tools::TrapHoleAuto::TrapHoleAuto(QObject *parent) : Tool(parent)
{
    this->setPixmap(QPixmap(":/images/trap_hole.png").scaledToHeight(100));
    this->setToolTip("AutoDziura na myszy");
    QObject::connect(this, &Tool::collidingItem, this, &Tools::TrapHoleAuto::collition);
}

void Tools::TrapHoleAuto::collition(QGraphicsItem *t)
{
    if(Sprites::Mouse::isQGraphicsItem(t)) {
        Sprites::Mouse *mouse = (Sprites::Mouse *)t;
        mouse->trapped();
        mouse->deadBodyVisible(false);
        mouse->kill();
    }
}

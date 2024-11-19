/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#include "qgraphicsscenecustom.h"
#include "mouse.h"
#include "qforeach.h"
#include "qgraphicsitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <flybullet.h>

QGraphicsSceneCustom::QGraphicsSceneCustom(QObject *parent)
    : QGraphicsScene{parent}
{
}

void QGraphicsSceneCustom::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF qpf = event->scenePos();

    Mouse *it = (Mouse*)this->itemAt(qpf, QTransform());
    if(it && !it->isTrapped) {
        it->trapped();
        qDebug() << "Mouse released! " << it->pos().x() << "x" << it->pos().y();

        QPixmap p = QPixmap(":/images/bullet.png").scaledToHeight(100);

        FlyBullet *fb = new FlyBullet(this);
        fb->bulletDestX = qpf.x();
        fb->bulletDestY = qpf.y();
        fb->bulletItem = new QGraphicsPixmapItem(p);
        fb->bulletItem->setPos(600, 600);
        fb->mouse = it;
        this->addItem(fb->bulletItem);

        connect(fb, &FlyBullet::destBullet, this, &QGraphicsSceneCustom::flyBulletFinished);
        fb->start();
    }
}

void QGraphicsSceneCustom::flyBulletFinished(FlyBullet *fb)
{
    QPixmap p = QPixmap(":/images/dziura.png").scaledToHeight(100);

    QGraphicsPixmapItem *dz = new QGraphicsPixmapItem(p);
    dz->setPos(fb->bulletDestX, fb->bulletDestY);
    this->addItem(dz);

    this->removeItem(fb->bulletItem);
    this->removeItem(fb->mouse);
}



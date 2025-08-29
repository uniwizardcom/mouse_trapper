/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */
#ifndef SPRITES_FLYBULLET_H
#define SPRITES_FLYBULLET_H

#include "mouse.h"
#include <QThread>
#include <QGraphicsPixmapItem>
#include <QTime>

namespace Sprites {
class FlyBullet : public QThread
{
    Q_OBJECT

public:
    explicit FlyBullet(QObject *parent = nullptr);
    ~FlyBullet();

    Mouse *mouse;
    QGraphicsPixmapItem *bulletItem;
    int bulletDestX;
    int bulletDestY;

    void run();

private:
    QTimer *bulletTimer;
    int bulletX;
    int bulletY;

public:
    Q_SIGNAL void destBullet(FlyBullet*);

public slots:
    void flyBullet();

};
}

#endif // SPRITES_FLYBULLET_H

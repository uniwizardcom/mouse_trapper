/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#include "flybullet.h"
#include <QTimer>
#include <QDebug>

FlyBullet::FlyBullet(QObject *parent) : QThread{parent}
{
}

FlyBullet::~FlyBullet()
{
}

void FlyBullet::run()
{
    this->bulletTimer = new QTimer();
    connect(this->bulletTimer, &QTimer::timeout, this, QOverload<>::of(&FlyBullet::flyBullet));
    this->bulletTimer->start(30);

    exec();
}

void FlyBullet::flyBullet()
{
    int x = this->bulletItem->pos().x() - 10;
    int y  = this->bulletItem->pos().y() - 10;

    if(x < this->bulletDestX) x = this->bulletDestX;
    if(y < this->bulletDestY) y = this->bulletDestY;
    this->bulletItem->setPos(x, y);


    if(x == this->bulletDestX && y == this->bulletDestY) {
        emit destBullet(this);
        this->quit();
    }
}

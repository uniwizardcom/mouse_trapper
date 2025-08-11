/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#include "qgraphicsscenecustom.h"
#include "sprites/mouse.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "sprites/flybullet.h"
#include <QString>
#include "sprites/traphole.h"

QGraphicsSceneCustom::QGraphicsSceneCustom(QObject *parent)
    : QGraphicsScene{parent}
{
    this->nextLevel = 0;
    this->withWorkingButtons = false;
    QObject::connect(this, &QGraphicsSceneCustom::noMiceOnScene, this, &QGraphicsSceneCustom::choiceLevel);
}

void QGraphicsSceneCustom::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF qpf = event->scenePos();
    Mouse *mit = (Mouse*)this->itemAt(qpf, QTransform());

    if(!Mouse::isQGraphicsItem(mit)) {
        qDebug() << "It's not a Mouse!";
        return;
    }

    if(mit && !mit->isTrapped) {
        mit->trapped();

        QPixmap p = QPixmap(":/images/bullet.png").scaledToHeight(100);

        FlyBullet *fb = new FlyBullet(this);
        fb->bulletDestX = qpf.x();
        fb->bulletDestY = qpf.y();
        fb->bulletItem = new QGraphicsPixmapItem(p);
        fb->bulletItem->setPos(600, 600);
        fb->mouse = mit;
        this->addItem(fb->bulletItem);

        connect(fb, &FlyBullet::destBullet, this, &QGraphicsSceneCustom::flyBulletFinished);
        fb->start();
    }
    else if(!this->items().count()) {
        this->setNewLevel(1);
    }

    // this->showTrapHole(qpf.x(), qpf.y());
}

void QGraphicsSceneCustom::flyBulletFinished(FlyBullet *fb)
{
    QPixmap p = QPixmap(":/images/dziura_2.png").scaledToHeight(100);

    QGraphicsPixmapItem *dz = new QGraphicsPixmapItem(p);
    dz->setPos(
        fb->bulletDestX - (p.width() / 2),
        fb->bulletDestY - (p.height() / 2)
        );
    this->addItem(dz);

    this->removeItem(fb->bulletItem);
    if(fb->mouse) {
        this->removeItem(fb->mouse);
        if(!this->countOfMice()) {
            this->nextLevel = this->miceCount +1;
            emit noMiceOnScene();
        }
    }
}

int QGraphicsSceneCustom::countOfMice()
{
    int m = 0;
    foreach (QGraphicsItem *t, this->items()) {
        if(Mouse::isQGraphicsItem(t)) {
            m++;
        }
    }

    return m;
}

void QGraphicsSceneCustom::choiceLevel()
{
    if(!this->choiceLevelDialog) {
        this->choiceLevelDialog = new ChoiceLevel();
        if(!this->withWorkingButtons) {
            this->choiceLevelDialog->hideNextButton();
            this->withWorkingButtons = true;
        }
        this->choiceLevelDialog->setNextLevel(this->nextLevel);

        QObject::connect(this->choiceLevelDialog, &ChoiceLevel::levelRestart, this, &QGraphicsSceneCustom::gotoLevelRestart);
        QObject::connect(this->choiceLevelDialog, &ChoiceLevel::levelUp, this, &QGraphicsSceneCustom::gotoLevelUp);
        QObject::connect(this->choiceLevelDialog, &ChoiceLevel::choiceLevelRejected, this, &QGraphicsSceneCustom::choiceLevelRejected);

        this->choiceLevelDialog->setModal(true);
        this->choiceLevelDialog->show();
    }
}

void QGraphicsSceneCustom::clearScene()
{
    // this->clear();
    foreach (QGraphicsItem *t, this->items()) {
        if(t->isWidget()) {
            continue;
        }
        // qDebug() << "Removed item: " << t->isWidget();

        this->removeItem(t);
    }

    this->refreshControls();
}

void QGraphicsSceneCustom::setNewLevel(int miceCount)
{
    this->miceCount = miceCount;
    if(this->nextLevel == 0) {
        this->nextLevel = miceCount;
    }

    this->clearScene();

    for (int i = 0; i < miceCount; ++i) {
        Mouse *mouse = new Mouse;
        mouse->setPos(
            ::sin((i * 6.28) / miceCount) * 200,
            ::cos((i * 6.28) / miceCount) * 200
            );

        mouse->setCursor(this->miceCursor);

        this->addItem(mouse);
    }

    if(miceCount) {
        this->choiceLevel();
    }
}

void QGraphicsSceneCustom::gotoLevelRestart()
{
    this->setNewLevel(this->miceCount);
    this->choiceLevelRejected();
}

void QGraphicsSceneCustom::gotoLevelUp()
{
    this->setNewLevel(this->miceCount +1);
    this->choiceLevelRejected();
}

void QGraphicsSceneCustom::choiceLevelRejected()
{
    if(this->choiceLevelDialog) {
        this->choiceLevelDialog->close();
    }
    this->choiceLevelDialog = nullptr;
}

void QGraphicsSceneCustom::showTrapHole(qreal x, qreal y)
{
    TrapHole *trapHole = new TrapHole(this);

    QObject::connect(trapHole, &TrapHole::miceInHole, this, &QGraphicsSceneCustom::miceInHole);

    trapHole->setPos(
        x - (trapHole->pixmap().width() / 2),
        y - (trapHole->pixmap().height() / 2)
    );

    this->addItem(trapHole);
}

void QGraphicsSceneCustom::miceInHole()
{
    if(!this->countOfMice()) {
        this->nextLevel = this->miceCount +1;
        emit noMiceOnScene();
    }
}

void QGraphicsSceneCustom::setMenu(Menu *menu)
{
    this->menu = menu;
    qDebug() << "Menu set";
}

void QGraphicsSceneCustom::setMiceCursor(const QCursor &miceCursor)
{
    this->miceCursor = (QCursor)miceCursor;
}

void QGraphicsSceneCustom::refreshControls()
{
    /*
    if(!this->menu) {
        qDebug() << "Menu null";
    }
    else if(this->menu->parentScene() == nullptr) {
        qDebug() << "Menu parent: nullptr";
        this->menu->setParentScene(this);
        this->addWidget(this->menu);
    }
    else {
        qDebug() << "Menu parent: " << this->menu->parentScene();
    } */

    // this->menu->setBaseSize(100, 200);
}


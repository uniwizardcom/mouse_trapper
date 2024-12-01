/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#include "qgraphicsscenecustom.h"
#include "mouse.h"
#include "qgraphicsitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <flybullet.h>
#include <QString>

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

    Mouse *it = (Mouse*)this->itemAt(qpf, QTransform());
    if(it && !it->isTrapped) {
        it->trapped();

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

    if(!this->countOfMice()) {
        this->nextLevel = this->miceCount +1;
        emit noMiceOnScene();
    }
}

int QGraphicsSceneCustom::countOfMice()
{
    int m = 0;

    qDebug() << "Items: " << this->items().size();
    foreach (QGraphicsItem *t, this->items()) {
        QString toc = QString(typeid(*t).name());
        if(toc.right(5) == "Mouse") {
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
        qDebug() << "this->nextLevel QGraphicsSceneCustom::choiceLevel: " << this->nextLevel;
        this->choiceLevelDialog->setNextLevel(this->nextLevel);

        QObject::connect(this->choiceLevelDialog, &ChoiceLevel::levelRestart, this, &QGraphicsSceneCustom::gotoLevelRestart);
        QObject::connect(this->choiceLevelDialog, &ChoiceLevel::levelUp, this, &QGraphicsSceneCustom::gotoLevelUp);
        QObject::connect(this->choiceLevelDialog, &ChoiceLevel::choiceLevelRejected, this, &QGraphicsSceneCustom::choiceLevelRejected);

        this->choiceLevelDialog->setModal(true);
        this->choiceLevelDialog->show();
    }
}

void QGraphicsSceneCustom::setNewLevel(int miceCount)
{
    this->miceCount = miceCount;
    if(this->nextLevel == 0) {
        this->nextLevel = miceCount;
    }

    this->clear();

    QPixmap pr = QPixmap(":/images/crosshair-symmetry-sniper_red.png").scaledToWidth(100);
    QCursor cr = QCursor(pr, pr.width() / 2, pr.height() / 2);

    for (int i = 0; i < miceCount; ++i) {
        Mouse *mouse = new Mouse;
        mouse->setPos(::sin((i * 6.28) / miceCount) * 200,
                      ::cos((i * 6.28) / miceCount) * 200);

        mouse->setCursor(cr);

        this->addItem(mouse);
    }

    qDebug() << "this->miceCount QGraphicsSceneCustom::setNewLevel: " << this->miceCount;
    this->choiceLevel();
}

void QGraphicsSceneCustom::gotoLevelRestart()
{
    qDebug() << "this->miceCount QGraphicsSceneCustom::gotoLevelRestart: " << this->miceCount ;

    this->setNewLevel(this->miceCount);
    this->choiceLevelRejected();
}

void QGraphicsSceneCustom::gotoLevelUp()
{
    qDebug() << "this->miceCount QGraphicsSceneCustom::gotoLevelUp: " << this->miceCount +1 ;

    this->setNewLevel(this->miceCount +1);
    this->choiceLevelRejected();
}

void QGraphicsSceneCustom::choiceLevelRejected()
{
    if(this->choiceLevelDialog) {
        this->choiceLevelDialog->close();
        // delete this->choiceLevelDialog;
    }
    this->choiceLevelDialog = nullptr;
}


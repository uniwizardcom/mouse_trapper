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
#include <QResizeEvent>
#include "tools/traphole.h"

QGraphicsSceneCustom::QGraphicsSceneCustom(QObject *parent)
    : QGraphicsScene{parent}
{
    this->nextLevel = 0;
    this->withWorkingButtons = false;
    QObject::connect(this, &QGraphicsSceneCustom::noMiceOnScene, this, &QGraphicsSceneCustom::choiceLevel);
}

void QGraphicsSceneCustom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit this->mousePressEventCustom(event);
}

void QGraphicsSceneCustom::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF qpf = event->scenePos();
    Sprites::Mouse *mit = (Sprites::Mouse*)this->itemAt(qpf, QTransform());

    emit this->mouseReleaseEventCustom(event);

    if(!Sprites::Mouse::isQGraphicsItem(mit)) {
        return;
    }

    if(mit && !mit->isTrapped) {
        mit->trapped();

        QPixmap p = QPixmap(":/images/bullet.png").scaledToHeight(100);

        Sprites::FlyBullet *fb = new Sprites::FlyBullet(this);
        fb->bulletDestX = qpf.x();
        fb->bulletDestY = qpf.y();
        fb->bulletItem = new QGraphicsPixmapItem(p);
        fb->bulletItem->setPos(600, 600);
        fb->mouse = mit;
        fb->mouse->lastX = fb->bulletDestX;
        fb->mouse->lastY = fb->bulletDestY;
        this->addItem(fb->bulletItem);

        connect(fb, &Sprites::FlyBullet::destBullet, this, &QGraphicsSceneCustom::flyBulletFinished);
        fb->start();
    }
    else if(!this->items().count()) {
        this->setNewLevel(1);
    }
}

void QGraphicsSceneCustom::viewResizeEvent(QResizeEvent *event)
{
    this->viewSize = event->size();
}

QSize QGraphicsSceneCustom::getViewSize()
{
    return this->viewSize;
}

void QGraphicsSceneCustom::flyBulletFinished(Sprites::FlyBullet *fb)
{
    this->removeItem(fb->bulletItem);
    if(fb->mouse) {
        fb->mouse->kill();
    }
}

int QGraphicsSceneCustom::countOfMice()
{
    int m = 0;
    foreach (QGraphicsItem *t, this->items()) {
        if(Sprites::Mouse::isQGraphicsItem(t) && !((Sprites::Mouse*)t)->isTrapped) {
            m++;
        }
    }

    return m;
}

int QGraphicsSceneCustom::getLevel()
{
    return this->miceCount;
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
    foreach (QGraphicsItem *t, this->items()) {
        if(t->isWidget()) {
            continue;
        }

        this->removeItem(t);
    }
}

void QGraphicsSceneCustom::setNewLevel(int miceCount)
{
    emit levelChange(this->nextLevel, miceCount);

    this->miceCount = miceCount;
    if(this->nextLevel == 0) {
        this->nextLevel = miceCount;
    }

    this->clearScene();

    for (int i = 0; i < miceCount; ++i) {
        Sprites::Mouse *mouse = new Sprites::Mouse;
        mouse->setPos(
            ::sin((i * 6.28) / miceCount) * 200,
            ::cos((i * 6.28) / miceCount) * 200
            );

        mouse->setCursor(this->miceCursor);
        QObject::connect(mouse, &Sprites::Mouse::spriteIsKilled, this, &QGraphicsSceneCustom::spriteIsKilled);

        this->addItem(mouse);
    }

    if(miceCount) {
        this->choiceLevel();
    }
}

void QGraphicsSceneCustom::spriteIsKilled(QGraphicsItem *t)
{
    if(Sprites::Mouse::isQGraphicsItem(t) && ((Sprites::Mouse*)t)->isDeadBodyVisible()) {
        Tools::TrapHole *th = new Tools::TrapHole();
        th->setPos(
            t->pos().x() - (th->pixmap().size().width() / 2),
            t->pos().y() - (th->pixmap().size().height() / 2)
        );
        this->addItem(th);
    }

    if(!this->countOfMice()) {
        this->nextLevel = this->miceCount +1;
        emit noMiceOnScene();
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
    emit this->levelUp();
}

void QGraphicsSceneCustom::choiceLevelRejected()
{
    if(this->choiceLevelDialog) {
        this->choiceLevelDialog->close();
    }
    this->choiceLevelDialog = nullptr;
}

void QGraphicsSceneCustom::setMenu(MenuWg *menu)
{
    this->menu = menu;
}

void QGraphicsSceneCustom::setMiceCursor(const QCursor &miceCursor)
{
    this->miceCursor = (QCursor)miceCursor;
}

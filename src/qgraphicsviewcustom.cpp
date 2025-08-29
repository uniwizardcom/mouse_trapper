#include "qgraphicsviewcustom.h"
#include "qgraphicsscenecustom.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QResizeEvent>

QGraphicsViewCustom::QGraphicsViewCustom()
{
    this->setRenderHint(QPainter::Antialiasing);
    this->setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setDragMode(QGraphicsView::NoDrag);
}

void QGraphicsViewCustom::setCursorDefault(const QCursor &cursor)
{
    this->viewport()->setCursor(cursor);
    this->setCursor(cursor);
}

void QGraphicsViewCustom::setCursorOnTarget(const QCursor &cursor)
{
    this->cursorOnTarget = cursor;
}

void QGraphicsViewCustom::setMenu(MenuWg *menu)
{
    this->menu = menu;

    this->menu->setCursor(this->cursor());

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(this->menu);
    layout->setAlignment(this->menu, Qt::AlignRight | Qt::AlignTop);
}

void QGraphicsViewCustom::setCustomScene(QGraphicsSceneCustom *scene)
{
    scene->setMiceCursor(this->cursorOnTarget);
    QObject::connect(scene, &QGraphicsSceneCustom::levelUp, this, &QGraphicsViewCustom::levelChange);
    QObject::connect(scene, &QGraphicsSceneCustom::mouseReleaseEventCustom, this, &QGraphicsViewCustom::mouseReleaseEventScene);
    this->setScene((QGraphicsScene*) scene);
    this->menu->setParentScene(scene);
}

void QGraphicsViewCustom::mouseReleaseEventScene(QGraphicsSceneMouseEvent *)
{
    this->viewport()->setCursor(this->cursor());
}

void QGraphicsViewCustom::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    this->menu->parentScene()->viewResizeEvent(event);
}

void QGraphicsViewCustom::levelChange()
{
    if(this->windowTitleOrg.isEmpty()) {
        this->windowTitleOrg = this->windowTitle();
    }

    this->setWindowTitle(
        QString("%1 - level %2")
            .arg(this->windowTitleOrg)
            .arg(((QGraphicsSceneCustom*)this->scene())->getLevel())
        );
}

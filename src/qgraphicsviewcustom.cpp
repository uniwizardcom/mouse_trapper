#include "qgraphicsviewcustom.h"
#include "qgraphicsscenecustom.h"
#include <QApplication>

QGraphicsViewCustom::QGraphicsViewCustom()
{
    this->setRenderHint(QPainter::Antialiasing);
    this->setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
}

void QGraphicsViewCustom::setCursorDefault(const QCursor &cursor)
{
    // this->setCursor(cursor);
    this->viewport()->setCursor(cursor);
}

void QGraphicsViewCustom::setCursorOnTarget(const QCursor &cursor)
{
    this->cursorOnTarget = cursor;
}

void QGraphicsViewCustom::setMenu(Menu *menu)
{
    this->menu = menu;
    qDebug() << "Menu set";

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(this->menu);
    layout->setAlignment(this->menu, Qt::AlignRight | Qt::AlignTop);
}

void QGraphicsViewCustom::setCustomScene(QGraphicsSceneCustom *scene)
{
    //scene->miceCursor = ;
    scene->setMiceCursor(this->cursorOnTarget);
    // scene->views()->s
    this->setScene((QGraphicsScene*) scene);
}

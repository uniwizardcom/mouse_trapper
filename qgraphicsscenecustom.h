/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */
#ifndef QGRAPHICSSCENECUSTOM_H
#define QGRAPHICSSCENECUSTOM_H

#include "flybullet.h"
#include <QGraphicsScene>
#include <QTimer>

class QGraphicsSceneCustom : public QGraphicsScene
{
public:
    explicit QGraphicsSceneCustom(QObject *parent = nullptr);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsPixmapItem *bulletItem;

 public slots:
    void flyBulletFinished(FlyBullet*);
};

#endif // QGRAPHICSSCENECUSTOM_H

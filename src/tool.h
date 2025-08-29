#ifndef TOOL_H
#define TOOL_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "qgraphicsscenecustom.h"

class Tool : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Tool(QObject *parent = nullptr);

    QRectF boundingRect() const override;
    void setScene(QGraphicsSceneCustom *sceneCm);
    QGraphicsSceneCustom* getSceneCm();

signals:
    void collidingItem(QGraphicsItem*);

protected:
    void advance(int) override;

private:
    QGraphicsSceneCustom *sceneCm = nullptr;
};

#endif // TOOL_H

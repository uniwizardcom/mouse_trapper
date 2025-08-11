#ifndef TRAPHOLE_H
#define TRAPHOLE_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class TrapHole : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit TrapHole(QObject *parent = nullptr);

    QRectF boundingRect() const override;

signals:
    void miceInHole();

protected:
    void advance(int step) override;
};

#endif // TRAPHOLE_H

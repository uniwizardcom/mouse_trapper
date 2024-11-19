/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsItem>

//! [0]
class Mouse : public QGraphicsItem
{
public:
    Mouse();

    bool isTrapped;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void trapped();

protected:
    void advance(int step) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;
};
//! [0]

#endif

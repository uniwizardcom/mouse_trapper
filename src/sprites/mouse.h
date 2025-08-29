/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#ifndef SPRITES_MOUSE_H
#define SPRITES_MOUSE_H

#include <QGraphicsItem>
#include <QObject>

namespace Sprites {
class Mouse : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit Mouse(QObject *parent = nullptr);

    bool isTrapped;
    int lastX;
    int lastY;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief trapped
     *
     * The mice is catch by some trap
     */
    void trapped();

    /**
     * @brief trapped
     *
     * The mice will be killed (removing from scene)
     */
    void kill();

    /**
     * @brief goAway
     *
     * GoAway ... from some tool on sceen
     */
    void goAway();

    void deadBodyVisible(bool );
    bool isDeadBodyVisible();

// Static tools
    static bool isQGraphicsItem(QGraphicsItem *i);

    Q_SIGNAL void spriteIsKilled(QGraphicsItem *);

protected:
    void advance(int step) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;
    bool deadBody = true;
};
}

#endif // SPRITES_MOUSE_H

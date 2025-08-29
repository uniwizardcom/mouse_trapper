/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#include "mouse.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0) angle += TwoPi;
    while (angle > TwoPi) angle -= TwoPi;

    return angle;
}

Sprites::Mouse::Mouse(QObject *parent) :
    QObject(parent), QGraphicsItem(),
    color(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256))
{
    this->isTrapped = false;
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
}

QRectF Sprites::Mouse::boundingRect() const
{
    qreal adjust = 0.5;

    return QRectF(
        -18 - adjust,
        -22 - adjust,
        36 + adjust,
        60 + adjust
        );
}

QPainterPath Sprites::Mouse::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Sprites::Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);

    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    // Nose
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // Pupils
    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

    // Ears
    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
    painter->drawEllipse(-17, -12, 16, 16);
    painter->drawEllipse(1, -12, 16, 16);

    // Tail
    QPainterPath path(QPointF(0, 20));
    path.cubicTo(-5, 22, -5, 22, 0, 25);
    path.cubicTo(5, 27, 5, 32, 0, 30);
    path.cubicTo(-5, 32, -5, 42, 0, 35);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);
}

void Sprites::Mouse::advance(int step)
{
    if (!step || this->isTrapped)
        return;

    // Don't move too far away
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            this->angle += (this->angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            this->angle += (this->angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(this->angle) < 0) {
        this->angle += 0.25;
    } else if (::sin(this->angle) > 0) {
        this->angle -= 0.25;
    }

    // Try not to crash with any other mice
    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                           << mapToScene(0, 0)
                           << mapToScene(-30, -50)
                           << mapToScene(30, -50));

    for (const QGraphicsItem *item : dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            this->angle += 0.5;
        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            this->angle -= 0.5;
        }
    }

    // Add some random movement
    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            this->angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            this->angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }

    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

    qreal dx = ::sin(this->angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
}

void Sprites::Mouse::trapped()
{
    this->isTrapped = true;
}

void Sprites::Mouse::kill()
{
    emit spriteIsKilled(this);
    this->scene()->removeItem(this);
}

void Sprites::Mouse::goAway()
{
    if (::sin(this->angle) < 0) {
        this->angle -= 0.3;
        this->speed -= (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;
    } else {
        this->angle += 0.3;
        this->speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;
    }

    setPos(mapToParent(0, -(3 + sin(this->speed) * 3)));

    qreal dx = ::sin(this->angle) * 10;
    setRotation(rotation() + dx);
}

void Sprites::Mouse::deadBodyVisible(bool deadBody)
{
    this->deadBody = deadBody;
}

bool Sprites::Mouse::isDeadBodyVisible()
{
    return this->deadBody;
}

// Static tools
bool Sprites::Mouse::isQGraphicsItem(QGraphicsItem *i)
{
    if(i == nullptr) {
        return false;
    }

    return dynamic_cast<Mouse*>(i) != nullptr;
}


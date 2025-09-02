#include "button.h"
#include "qapplication.h"
#include "../qgraphicsscenecustom.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

/**
 * @brief MenuButton::MenuButton
 *
 *
 *  explicit QPushButton(QWidget *parent = nullptr);
 *  explicit QPushButton(const QString &text, QWidget *parent = nullptr);
 *  QPushButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
 */
/*
Menu::MenuButton::MenuButton(QWidget *parent): QPushButton(parent)
{
    //
}

Menu::MenuButton::MenuButton(const QString &text, QWidget *parent): QPushButton(text, parent)
{
    //
}

Menu::MenuButton::MenuButton(const QIcon& icon, const QString &text, QWidget *parent): QPushButton(icon, text, parent)
{
    //
}*/

Menu::MenuButton::MenuButton(QWidget *parent) : QToolButton(parent)
{
    // this->setObjectName("pushButton1");
    this->scene = ((MenuWg*)this->parent())->parentScene();
}

void Menu::MenuButton::setIconFromQPixmap(QPixmap pixmap)
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    this->setPalette(palette);
    this->setStyleSheet("border: none; QToolButton { color: white;} QToolButton QWidget { color: black;}");

    this->setIcon(QIcon(pixmap));
    this->setIconSize(pixmap.scaledToWidth(100).size());
}

void Menu::MenuButton::setToolCreator(ToolCreator tp)
{
    this->toolCreator = tp;
    this->tool = this->toolCreator();

    this->setIconFromQPixmap(this->tool->pixmap());
    this->setToolTip(this->tool->toolTip());
}

void Menu::MenuButton::setDefaultCursor(const QCursor &cur)
{
    this->defaultCursor = cur;
}

void Menu::MenuButton::enterEvent(QEnterEvent *)
{
}

void Menu::MenuButton::leaveEvent(QEvent *)
{
}

void Menu::MenuButton::mousePressEvent(QMouseEvent *)
{
    if(this->tool == nullptr) {
        this->tool = this->toolCreator();
    }

    QPixmap scpd = QPixmap(this->tool->pixmap()).scaledToWidth(100);
    QCursor sniperCursorDefault = QCursor(scpd, scpd.width() / 2, scpd.height() / 2);

    this->setCursor(sniperCursorDefault);
}

void Menu::MenuButton::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(this->defaultCursor);
    if(this->tool != nullptr) {
        this->scene->addItem(this->tool);
        this->setToolPosition(event);
        this->tool = nullptr;
    }
}

void Menu::MenuButton::setToolPosition(QMouseEvent *event)
{
    this->tool->setPos(
        (event->scenePosition().x() - (this->tool->pixmap().size().width() / 2)) - (this->scene->getViewSize().width() / 2),
        (event->scenePosition().y() - (this->tool->pixmap().size().height() / 2)) - (this->scene->getViewSize().height() / 2)
    );
}

#include "menubutton.h"
#include <QPainter>

/**
 * @brief MenuButton::MenuButton
 *
 *
 *  explicit QPushButton(QWidget *parent = nullptr);
 *  explicit QPushButton(const QString &text, QWidget *parent = nullptr);
 *  QPushButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
 */
/*
MenuButton::MenuButton(QWidget *parent): QPushButton(parent)
{
    //
}

MenuButton::MenuButton(const QString &text, QWidget *parent): QPushButton(text, parent)
{
    //
}

MenuButton::MenuButton(const QIcon& icon, const QString &text, QWidget *parent): QPushButton(icon, text, parent)
{
    //
}*/

MenuButton::MenuButton(QWidget *parent)
{
    //
}

void MenuButton::setBackgroundImage(const QString &fileName)
{
    this->backgroundImage = fileName;
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    // palette.setColor(QPalette::Button, QColor(82,110,166));
    this->setPalette(palette);
    this->setIcon(QIcon(fileName));
    this->setIconSize(QSize(121, 100));

    this->setToolTip("Comment");
}

void MenuButton::enterEvent(QEnterEvent *) {
    qDebug() << "entering";
}

void MenuButton::leaveEvent(QEvent *) {
    qDebug() << "leaving";
}


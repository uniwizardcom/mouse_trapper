#ifndef MENU_MENUBUTTON_H
#define MENU_MENUBUTTON_H

#include <QObject>
#include <QToolButton>
#include <QPaintEvent>
#include <functional>

#include "../tool.h"

typedef Tool*(*ToolCreator)(void);

namespace Menu {
class MenuButton : public QToolButton
{
public:
 /*   explicit MenuButton(QWidget *parent = nullptr);
    explicit MenuButton(const QString &text, QWidget *parent = nullptr);
    MenuButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);*/

    explicit MenuButton(QWidget *parent = nullptr);

    void setIconFromQPixmap(QPixmap pixmap);
    void setToolCreator(ToolCreator tp);
    void setDefaultCursor(const QCursor&);

protected:
    void enterEvent(QEnterEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *me) override;

    void setToolPosition(QMouseEvent *event);

private:
    QGraphicsSceneCustom *scene = nullptr;
    QString backgroundImage;
    ToolCreator toolCreator;
    Tool *tool = nullptr;
    QCursor defaultCursor;

public:
    Q_SIGNAL void dragAndDrop();
};
}

#endif // MENU_MENUBUTTON_H

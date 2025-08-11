#ifndef MENU_H
#define MENU_H

#include "src/menu/menubutton.h"
#include <QWidget>

class QGraphicsSceneCustom;

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    void setTrapHolesStartLevel(int level);
    ~Menu();

    void setParentScene(QGraphicsSceneCustom *scene);
    QGraphicsSceneCustom* parentScene();

private:
    Ui::Menu *ui;

    int trapHolesStartLevel;
    QGraphicsSceneCustom *scene = nullptr;
};

#endif // MENU_H

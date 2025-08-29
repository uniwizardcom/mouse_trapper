#ifndef MENUWG_H
#define MENUWG_H

#include <QWidget>

class QGraphicsSceneCustom;

namespace Ui {
class MenuWg;
}

class MenuWg : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWg(QWidget *parent = nullptr);
    void setTrapHolesStartLevel(int level);
    ~MenuWg();

    void setParentScene(QGraphicsSceneCustom *scene);
    QGraphicsSceneCustom* parentScene();

    void addMenuButtons();

public slots:
    void levelChange(int prev, int curr);

private:
    Ui::MenuWg *ui;

    int trapHolesStartLevel;
    QGraphicsSceneCustom *sceneCm = nullptr;
};

#endif // MENUWG_H

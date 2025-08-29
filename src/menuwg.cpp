#include "menuwg.h"
#include "ui_menuwg.h"

#include "menu/button.h"
#include "tools/trapholeauto.h"

MenuWg::MenuWg(QWidget *parent): QWidget(parent), ui(new Ui::MenuWg)
{
    ui->setupUi(this);

    ui->label->setText("Twoje narzędzia");
    ui->label->setStyleSheet("background: #ffffff; border: none");
}

MenuWg::~MenuWg()
{
    delete ui;
}

void MenuWg::setParentScene(QGraphicsSceneCustom *scene)
{
    this->sceneCm = scene;

    QObject::connect(this->sceneCm, &QGraphicsSceneCustom::levelChange, this, &MenuWg::levelChange);
}

QGraphicsSceneCustom* MenuWg::parentScene()
{
    return this->sceneCm;
}

void MenuWg::levelChange(int prev, int curr)
{
    if(curr >= this->trapHolesStartLevel) {
        Menu::MenuButton *pushButton1 = new Menu::MenuButton(this);
        pushButton1->setDefaultCursor(this->cursor());
        pushButton1->setToolCreator([]() -> Tool* {
            return (Tool*)(new Tools::TrapHoleAuto());
        });

        ui->gridLayout_2->addWidget(pushButton1, 1, 0, 1, 1);
    }
}

void MenuWg::setTrapHolesStartLevel(int level)
{
    this->trapHolesStartLevel = level;
}

void MenuWg::addMenuButtons()
{

}

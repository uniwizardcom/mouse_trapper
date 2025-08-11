#include "menu.h"
#include "ui_menu.h"

#include "menu/menubutton.h"
#include "sprites/traphole.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);

    QCursor cc = QCursor(Qt::CrossCursor);

    MenuButton *pushButton1 = new MenuButton(this);
    pushButton1->setObjectName("pushButton1");
    pushButton1->setBackgroundImage(":images/trap_hole.png");
    pushButton1->cursor().swap(cc);
    pushButton1->setText("Button 1");
    ui->gridLayout->addWidget(pushButton1, 1, 0, 1, 1);

    MenuButton *pushButton2 = new MenuButton(this);
    pushButton2->setObjectName("pushButton2");
    pushButton2->setText("Button 2");
    ui->gridLayout->addWidget(pushButton2, 1, 1, 1, 1);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::setParentScene(QGraphicsSceneCustom *scene)
{
    this->scene = scene;
}

QGraphicsSceneCustom* Menu::parentScene()
{
    return this->scene;
}

void Menu::setTrapHolesStartLevel(int level)
{
    this->trapHolesStartLevel = level;
}


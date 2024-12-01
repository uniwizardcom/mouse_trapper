#include "choicelevel.h"
#include "ui_choicelevel.h"

ChoiceLevel::ChoiceLevel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChoiceLevel)
{
    ui->setupUi(this);
}

ChoiceLevel::~ChoiceLevel()
{
    delete ui;
}

void ChoiceLevel::setNextLevel(int nextLevel)
{
    this->nextLevel = nextLevel;

    ui->pushButton->setText( QString("Start level\n%1").arg(nextLevel) );

    qDebug() << "ui->pushButton_2->isHidden(): " << (ui->pushButton_2->isHidden() ? "tak" : "nie");
    if(!ui->pushButton_2->isHidden()) {
        ui->pushButton_2->setText( QString("Retart level: %1").arg(nextLevel - 1) );
    }
}

void ChoiceLevel::hideNextButton()
{
    ui->pushButton_2->setHidden(true);
}

void ChoiceLevel::on_ChoiceLevel_rejected()
{
    emit choiceLevelRejected();
}

/**
 * Restart current level
 *
 * @brief ChoiceLevel::on_pushButton_clicked
 */
void ChoiceLevel::on_pushButton_clicked()
{
    if(ui->pushButton_2->isHidden()) {
        emit levelRestart();
    } else {
        emit levelUp();
    }
}

/**
 * Go to next level
 *
 * @brief ChoiceLevel::on_pushButton_2_clicked
 */
void ChoiceLevel::on_pushButton_2_clicked()
{
    emit levelRestart();
}


#ifndef CHOICELEVEL_H
#define CHOICELEVEL_H

#include <QDialog>

namespace Ui {
class ChoiceLevel;
}

class ChoiceLevel : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiceLevel(QWidget *parent = nullptr);
    ~ChoiceLevel();

    void setNextLevel(int nextLevel = 0);
    void hideNextButton();

signals:
    void levelUp();
    void levelRestart();
    void choiceLevelRejected();

private slots:
    void on_ChoiceLevel_rejected();

    /**
     * Restart next level
     *
     * @brief ChoiceLevel::on_pushButton_clicked
     */
    void on_pushButton_clicked();

    /**
     * Go to current level
     *
     * @brief ChoiceLevel::on_pushButton_2_clicked
     */
    void on_pushButton_2_clicked();

private:
    Ui::ChoiceLevel *ui;
    int nextLevel = 0;
};

#endif // CHOICELEVEL_H

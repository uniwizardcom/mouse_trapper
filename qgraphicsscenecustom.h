/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */
#ifndef QGRAPHICSSCENECUSTOM_H
#define QGRAPHICSSCENECUSTOM_H

#include "flybullet.h"
#include "choicelevel.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>

class QGraphicsSceneCustom : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit QGraphicsSceneCustom(QObject *parent = nullptr);
    void setNewLevel(int miceCount);
    int countOfMice();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsPixmapItem *bulletItem;
    ChoiceLevel *choiceLevelDialog = nullptr;
    bool withWorkingButtons;
    int nextLevel;
    int miceCount;

public:
signals:
    void noMiceOnScene();
    void levelUp();
    void levelRestart();


public slots:
    void flyBulletFinished(FlyBullet*);
    void choiceLevel();
    void gotoLevelUp();
    void gotoLevelRestart();
    void choiceLevelRejected();

};

#endif // QGRAPHICSSCENECUSTOM_H

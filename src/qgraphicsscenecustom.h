/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */
#ifndef QGRAPHICSSCENECUSTOM_H
#define QGRAPHICSSCENECUSTOM_H

#include "sprites/flybullet.h"
#include "choicelevel.h"
#include "src/menu.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>

class QGraphicsSceneCustom : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit QGraphicsSceneCustom(QObject *parent = nullptr);
    void setNewLevel(int miceCount);
    void setMenu(Menu *menu);
    void setMiceCursor(const QCursor&);
    int countOfMice();
    void clearScene();
    void refreshControls();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsPixmapItem *bulletItem;
    ChoiceLevel *choiceLevelDialog = nullptr;
    Menu *menu = nullptr;
    QCursor miceCursor;
    bool withWorkingButtons;
    int nextLevel;
    int miceCount;

    void showTrapHole(qreal x, qreal y);

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
    void miceInHole();

};

#endif // QGRAPHICSSCENECUSTOM_H

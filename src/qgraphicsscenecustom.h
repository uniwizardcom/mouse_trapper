/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */
#ifndef QGRAPHICSSCENECUSTOM_H
#define QGRAPHICSSCENECUSTOM_H

#include "sprites/flybullet.h"
#include "choicelevel.h"
#include "src/menuwg.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>

class QGraphicsSceneCustom : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit QGraphicsSceneCustom(QObject *parent = nullptr);
    void setNewLevel(int miceCount);
    void setMenu(MenuWg *menu);
    void setMiceCursor(const QCursor&);
    int countOfMice(); // count of live mice
    int getLevel(); // the level of game - count of mice at the start of this level
    void clearScene();

    void viewResizeEvent(QResizeEvent *event);
    QSize getViewSize();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsPixmapItem *bulletItem;
    ChoiceLevel *choiceLevelDialog = nullptr;
    MenuWg *menu = nullptr;
    QCursor miceCursor;
    bool withWorkingButtons;
    int nextLevel;
    int miceCount;

    QSize viewSize;

public:
signals:
    void noMiceOnScene();
    void levelUp();
    void levelRestart();
    void levelChange(int prev, int curr);

    void mousePressEventCustom(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEventCustom(QGraphicsSceneMouseEvent *event);

public slots:
    void flyBulletFinished(Sprites::FlyBullet*);
    void choiceLevel();
    void gotoLevelUp();
    void gotoLevelRestart();
    void choiceLevelRejected();
    void spriteIsKilled(QGraphicsItem *);
};

#endif // QGRAPHICSSCENECUSTOM_H

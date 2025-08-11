#ifndef QGRAPHICSVIEWCUSTOM_H
#define QGRAPHICSVIEWCUSTOM_H

#include <QGraphicsView>
#include <QGridLayout>
#include "menu.h"

class QGraphicsViewCustom : public QGraphicsView
{
public:
    QGraphicsViewCustom();

    void setCursorDefault(const QCursor&);
    void setCursorOnTarget(const QCursor&);
    void setMenu(Menu *menu);
    void setCustomScene(QGraphicsSceneCustom *scene);

private:
    Menu *menu = nullptr;
    QCursor cursorOnTarget;
};

#endif // QGRAPHICSVIEWCUSTOM_H

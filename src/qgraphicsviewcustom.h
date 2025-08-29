#ifndef QGRAPHICSVIEWCUSTOM_H
#define QGRAPHICSVIEWCUSTOM_H

#include <QGraphicsView>
#include <QGridLayout>
#include "menuwg.h"

class QGraphicsViewCustom : public QGraphicsView
{
    Q_OBJECT

public:
    QGraphicsViewCustom();

    void setCursorDefault(const QCursor&);
    void setCursorOnTarget(const QCursor&);
    void setMenu(MenuWg *menu);
    void setCustomScene(QGraphicsSceneCustom *scene);

private:
    MenuWg *menu = nullptr;
    QCursor cursorOnTarget;
    QString windowTitleOrg = "";

public slots:
    void mouseReleaseEventScene(QGraphicsSceneMouseEvent *);
    void resizeEvent(QResizeEvent *event) override;
    void levelChange();
};

#endif // QGRAPHICSVIEWCUSTOM_H

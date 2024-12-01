/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#include <QApplication>
#include <QGraphicsView>
#include "qgraphicsscenecustom.h"

// static constexpr int MouseCount = 1;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QGraphicsSceneCustom scene;
    scene.setSceneRect(-300, -300, 600, 600);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    scene.setNewLevel(10);

    QPixmap ps = QPixmap(":/images/crosshair-symmetry-sniper.png").scaledToWidth(100);
    QCursor c = QCursor(ps, ps.width() / 2, ps.height() / 2);
    QGuiApplication::setOverrideCursor(c);


    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);


    QGraphicsView *view = new QGraphicsView();

    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Mice Trapping"));
    view->resize(800, 600);
    view->show();


    view->setScene(&scene);

    return app.exec();
}


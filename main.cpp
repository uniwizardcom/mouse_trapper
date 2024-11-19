/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#include <QtMath>
#include <QtWidgets>

#include "mouse.h"
#include "qgraphicsscenecustom.h"

static constexpr int MouseCount = 100;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QGraphicsSceneCustom scene;
    scene.setSceneRect(-300, -300, 600, 600);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    QPixmap pr = QPixmap(":/images/crosshair-symmetry-sniper_red.png").scaledToWidth(100);
    QCursor cr = QCursor(pr, pr.width() / 2, pr.height() / 2);
    QPixmap ps = QPixmap(":/images/crosshair-symmetry-sniper.png").scaledToWidth(100);
    QCursor c = QCursor(ps, ps.width() / 2, ps.height() / 2);
    QGuiApplication::setOverrideCursor(c);

    for (int i = 0; i < MouseCount; ++i) {
        Mouse *mouse = new Mouse;
        mouse->setPos(::sin((i * 6.28) / MouseCount) * 200,
                      ::cos((i * 6.28) / MouseCount) * 200);

        mouse->setCursor(cr);

        scene.addItem(mouse);
    }

    QGraphicsView view(&scene);

    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Mice Trapping"));
    view.resize(800, 600);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);

    return app.exec();
}


/**
 * Developer: Uniwizard Wojciech Niewiadomski
 * Main graphics designer: Julian Niewiadomski
 * */

#include <QApplication>
#include <QGraphicsView>
#include <QWebEngineSettings>
#include "src/qgraphicsscenecustom.h"
#include "src/qgraphicsviewcustom.h"
#include "src/menu.h"
// #include "src/qwebengineview.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QGraphicsSceneCustom scene;
    scene.setSceneRect(-300, -300, 600, 600);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.setNewLevel(1);

    QPixmap scpd = QPixmap(":/images/crosshair-sniper-default.png").scaledToWidth(100);
    QCursor sniperCursorDefault = QCursor(scpd, scpd.width() / 2, scpd.height() / 2);

    QPixmap scpr = QPixmap(":/images/crosshair-sniper-red.png").scaledToWidth(100);
    QCursor sniperCursorRed = QCursor(scpr, scpr.width() / 2, scpr.height() / 2);
    // QGuiApplication::setOverrideCursor(cursor);

    QIcon ic = QIcon(QPixmap(":/images/ikonka.png"));
    QGuiApplication::setWindowIcon(ic);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);

    QGraphicsViewCustom *view = new QGraphicsViewCustom();
    view->setCursorDefault(sniperCursorDefault);
    view->setCursorOnTarget(sniperCursorRed);

    Menu *menu = new Menu();
    menu->setCursor(QCursor(Qt::ArrowCursor));
    menu->setTrapHolesStartLevel(3);
    view->setMenu(menu);

    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Mice Trapping"));
    view->resize(800, 600);
    view->show();

    /*QWebEngineView *webview = new QWebEngineView;
    webview->setUrl(QUrl(QStringLiteral("https://onet.pl")));
    webview->setUrl(QUrl(QStringLiteral("file:///home/uniwizard/Wideo/reklama.mp4")));
    webview->setUrl(QUrl(QStringLiteral("https://v.wpimg.pl/XzRNQi5tdxszLCdaGg96DnB0cwpFHAcXMyMySxlWLVhobH5YAEZoTmdhYF4GRmBKZXlhWgZBb1VgfGVZajU0FjcpIwZqLDUbIREYBFQTPSUCAg5fBQcHPx8HAjZiJAdOHwx_BEVAegc")));
    webview->setUrl(QUrl(QStringLiteral("qrc:/html/reklama.html")));
    webview->resize(1024, 750);
    webview->show();*/

    view->setCustomScene(&scene);

    return app.exec();
}


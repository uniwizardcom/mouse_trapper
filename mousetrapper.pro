#
#
# Developer: Uniwizard Wojciech Niewiadomski
# Main graphics designer: Julian Niewiadomski
#
#

QT += widgets core webenginewidgets

HEADERS += \
    src/qgraphicsviewcustom.h \
    src/choicelevel.h \
    src/menu.h \
    src/menu/menubutton.h \
    src/qgraphicsscenecustom.h \
    src/sprites/flybullet.h \
    src/sprites/mouse.h \
    src/sprites/traphole.h \
    src/tools.h \
    src/webview.h
SOURCES += \
    main.cpp \
    src/qgraphicsviewcustom.cpp \
    src/choicelevel.cpp \
    src/menu.cpp \
    src/menu/menubutton.cpp \
    src/qgraphicsscenecustom.cpp \
    src/sprites/flybullet.cpp \
    src/sprites/mouse.cpp \
    src/sprites/traphole.cpp \
    src/tools.cpp \
    src/webview.cpp

RESOURCES += \
	mice.qrc

DISTFILES += \
    README.md

FORMS += \
    src/choicelevel.ui \
    src/menu.ui


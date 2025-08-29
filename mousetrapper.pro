#
#
# Developer: Uniwizard Wojciech Niewiadomski
# Main graphics designer: Julian Niewiadomski
#
#

QT += widgets core webenginewidgets

HEADERS += \
    src/menuwg.h \
    src/qgraphicsviewcustom.h \
    src/choicelevel.h \
    src/menu/button.h \
    src/qgraphicsscenecustom.h \
    src/sprites/flybullet.h \
    src/sprites/mouse.h \
    src/tool.h \
    src/tools/traphole.h \
    src/tools/trapholeauto.h \
    src/webview.h

SOURCES += \
    main.cpp \
    src/menuwg.cpp \
    src/qgraphicsviewcustom.cpp \
    src/choicelevel.cpp \
    src/menu/button.cpp \
    src/qgraphicsscenecustom.cpp \
    src/sprites/flybullet.cpp \
    src/sprites/mouse.cpp \
    src/tool.cpp \
    src/tools/traphole.cpp \
    src/tools/trapholeauto.cpp \
    src/webview.cpp

# CONFIG += object_parallel_to_source
# CONFIG += object_with_source

RESOURCES += \
	mice.qrc

DISTFILES += \
    README.md

FORMS += \
    src/choicelevel.ui \
    src/menuwg.ui


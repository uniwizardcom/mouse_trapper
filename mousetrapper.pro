#
#
# Developer: Uniwizard Wojciech Niewiadomski
# Main graphics designer: Julian Niewiadomski
#
#

QT += widgets core

HEADERS += \
	choicelevel.h \
	flybullet.h \
	mouse.h \
	qgraphicsscenecustom.h
SOURCES += \
    choicelevel.cpp \
    flybullet.cpp \
	main.cpp \
        mouse.cpp \
    qgraphicsscenecustom.cpp

RESOURCES += \
	mice.qrc

DISTFILES += \
    README.md

FORMS += \
    choicelevel.ui


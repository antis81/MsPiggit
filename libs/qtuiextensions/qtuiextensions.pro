#-------------------------------------------------
#
# Project created by QtCreator 2011-10-03T22:06:40
#
#-------------------------------------------------

include(../../app.pri)

TARGET = QtUiExtensions
DESTDIR = $$BIN_BASE
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += .
DEPENDPATH += .

SOURCES += \
    csplashscreen.cpp

HEADERS += \
    csplashscreen.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}







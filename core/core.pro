#-------------------------------------------------
#
# Project created by QtCreator 2011-10-03T14:25:19
#
#-------------------------------------------------

include(../app.pri)

QT       += core gui

TARGET = MsPiggit
TEMPLATE = app
DESTDIR = $$BIN_BASE

INCLUDEPATH += . ../libs ../libs/libqgit2 ../libs/libqgit2/libgit2 ../libs/libqgit2/libgit2/include
#DEPENDPATH += $$PWD/../libs/libqgit2

LIBS += -lz

unix:!symbian|win32: LIBS += \
    -L$$OUT_PWD/../libs/qtuiextensions -lQtUiExtensions \
    -L$$OUT_PWD/../libs/libqgit2 -lqgit2

win32: {
PRE_TARGETDEPS += \
    $$OUT_PWD/../libs/qtuiextensions/QtUiExtensions.lib \
    $$OUT_PWD/../libs/libqgit2/libqgit2.lib
}
else:unix:!symbian: {
PRE_TARGETDEPS += \
    $$OUT_PWD/../libs/qtuiextensions/libQtUiExtensions.a \
    $$OUT_PWD/../libs/libqgit2/libqgit2.a
}


SOURCES += \
    main.cpp \
    ui/repowindow.cpp \
    model/commitmodel.cpp

HEADERS  += \
    ui/repowindow.h \
    model/commitmodel.h

FORMS    += \
    ui/repowindow.ui

RESOURCES += \
    resources/MsPiggitResources.qrc


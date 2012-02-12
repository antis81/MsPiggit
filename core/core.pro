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

win32-msvc: LIBEXT=lib
else: LIBEXT=a

unix:!symbian|win32: LIBS += \
    -L$$OUT_PWD/../libs/qtuiextensions -lQtUiExtensions \
    -L$$OUT_PWD/../libs/libqgit2 -lqgit2 \
    -L/usr/lib -lz

!symbian: {
PRE_TARGETDEPS += \
    $$OUT_PWD/../libs/qtuiextensions/libQtUiExtensions.$${LIBEXT} \
    $$OUT_PWD/../libs/libqgit2/libqgit2.$${LIBEXT}
}

SOURCES += \
    main.cpp \
    ui/repowindow.cpp \
    model/commitmodel.cpp \
    model/referencemodel.cpp \
    model/submodulemodel.cpp

HEADERS  += \
    ui/repowindow.h \
    model/commitmodel.h \
    model/referencemodel.h \
    model/submodulemodel.h \
    model/headeritem.h \
    model/treeitem.h

FORMS    += \
    ui/repowindow.ui

RESOURCES += \
    resources/MsPiggitResources.qrc


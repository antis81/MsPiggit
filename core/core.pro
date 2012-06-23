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

INCLUDEPATH += . ../libs/libqgit2 ../libs/libqgit2/include \
            ../libs/libqgit2/libgit2 ../libs/libqgit2/libgit2/include

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
    model/msptypeinfo.cpp \
    model/treeitem.cpp \
    model/treebuilder.cpp \
    ui/refdelegate.cpp \
    model/repomodel.cpp \
    ui/repoview.cpp \
    ui/repodelegate.cpp \
    model/modelaccess.cpp

HEADERS  += \
    ui/repowindow.h \
    model/commitmodel.h \
    model/referencemodel.h \
    model/treeitem.h \
    model/msptypeinfo.h \
    model/treebuilder.h \
    ui/refdelegate.h \
    ui/submoduledelegate.h \
    model/repomodel.h \
    ui/repoview.h \
    ui/repodelegate.h \
    model/modelaccess.h \
    metatypes.h

FORMS    += \
    ui/repowindow.ui \
    ui/repoview.ui

RESOURCES += \
    resources/MsPiggitResources.qrc


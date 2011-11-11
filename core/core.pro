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

LIBS += -L$$BIN_BASE \
    -lQtUiExtensions

win32-msvc: LIBEXT=lib
else: LIBEXT=a

PRE_TARGETDEPS += \
    $$DESTDIR/libQtUiExtensions.$${LIBEXT}

SOURCES += \
        main.cpp \
        ui/repowindow.cpp

HEADERS  += \
    ui/repowindow.h

FORMS    += \
    ui/repowindow.ui

RESOURCES += \
    resources/MsPiggitResources.qrc


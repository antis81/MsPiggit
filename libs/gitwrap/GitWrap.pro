#-------------------------------------------------
#
# Project created by QtCreator 2011-10-04T20:12:41
#
#-------------------------------------------------

QT       -= gui

TARGET = GitWrap
TEMPLATE = lib

DEFINES += GITWRAP_LIBRARY

SOURCES += gitwrap.cpp \
    abstractrepo.cpp \
    repocommander.cpp

HEADERS += gitwrap.h\
        GitWrap_global.h \
    abstractrepo.h \
    repocommander.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEEF3F1EF
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = GitWrap.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}









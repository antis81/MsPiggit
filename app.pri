!isEmpty(APP_PRI_INCLUDED):error("ignored: app.pri already included")
APP_PRI_INCLUDED = 1

PROJECT_BASE = $$PWD

BIN_BASE = $$PWD/build
message("Binaries going to $$BIN_BASE")

message("Meta files going to $$PWD/GeneratedFiles")
MOC_DIR = $$PWD/GeneratedFiles/moc
UI_DIR  = $$PWD/GeneratedFiles/ui
RCC_DIR = $$PWD/GeneratedFiles/rcc
OBJECTS_DIR = $$PWD/GeneratedFiles/obj

INCLUDEPATH += $$PWD $$PWD/libs $$PWD/libs/3rdparty

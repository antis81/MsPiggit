contains(QT_VERSION, ^4\\.[0-6]\\..*) {
	message("Qt animation framework is disabled for compatibility with versions < 4.7 ")
        DEFINES += "QT_NO_ANIMATION"
#    message("Cannot build $$TARGET with Qt version $${QT_VERSION}.")
#    error("Use at least Qt 4.7.")
}

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    libs \
    core

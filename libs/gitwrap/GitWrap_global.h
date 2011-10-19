#ifndef GITWRAP_GLOBAL_H
#define GITWRAP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GITWRAP_LIBRARY)
#  define GITWRAPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GITWRAPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GITWRAP_GLOBAL_H

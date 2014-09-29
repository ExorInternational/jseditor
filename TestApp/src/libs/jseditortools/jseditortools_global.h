#ifndef JSEDITORTOOLS_GLOBAL_H
#define JSEDITORTOOLS_GLOBAL_H

#include <qglobal.h>

#if defined(JSEDITORTOOLS_LIBRARY)
#  define JSEDITORTOOLS_EXPORT Q_DECL_EXPORT
#else
#  define JSEDITORTOOLS_EXPORT Q_DECL_IMPORT
#endif

#include <app_version_new.h>

#endif // JSEDITORTOOLS_GLOBAL_H

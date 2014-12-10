#ifndef JSEDITORTOOLS_GLOBAL_H
#define JSEDITORTOOLS_GLOBAL_H

#include <qglobal.h>

#if defined(JSEDITORTOOLS_LIBRARY)
#  define JSEDITORTOOLS_EXPORT Q_DECL_EXPORT
#else
#  define JSEDITORTOOLS_EXPORT Q_DECL_IMPORT
#endif

namespace Core {
namespace Constants {
    const char * const IDE_VERSION_LONG      = "1.0.0";
    const char * const IDE_SETTINGSVARIANT_STR      = "JsEditorTools";
    const char * const IDE_APPNAME_STR      = "JsEditor";
    const char * const IDE_COPY_SETTINGS_FROM_VARIANT_STR = "Dummy";
}
}

#endif // JSEDITORTOOLS_GLOBAL_H

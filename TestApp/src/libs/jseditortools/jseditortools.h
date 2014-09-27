#ifndef JSEDITORTOOLS_H
#define JSEDITORTOOLS_H

#include "jseditortools_global.h"

class QMainWindow;

namespace Core {
namespace Internal {
class CorePlugin;
}
}

namespace JsEditorTools {

class JSEDITORTOOLS_EXPORT JsEditorToolsLib {
public:
    JsEditorToolsLib(QMainWindow *mainWindow);
    ~JsEditorToolsLib();
private:
    QMainWindow *m_MainWindow;
    Core::Internal::CorePlugin *m_pCorePlugin;
};

}// namespace JsEditorTools


#endif // JSEDITORTOOLS_H

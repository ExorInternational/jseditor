#ifndef JSEDITORTOOLS_H
#define JSEDITORTOOLS_H

#include "jseditortools_global.h"

class QMainWindow;

namespace Core {
namespace Internal {
class CorePlugin;
}
}

namespace TextEditor {
namespace Internal {
class TextEditorPlugin;
}
}

namespace QmlJSTools {
namespace Internal {
class QmlJSToolsPlugin;
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
    TextEditor::Internal::TextEditorPlugin *m_pTextEditorPlugin;
    QmlJSTools::Internal::QmlJSToolsPlugin *m_pQmlJSToolsPlugin;
};

}// namespace JsEditorTools


#endif // JSEDITORTOOLS_H

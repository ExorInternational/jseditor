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

namespace QmlJSEditor {
namespace Internal {
class QmlJSEditorPlugin;
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
    QmlJSEditor::Internal::QmlJSEditorPlugin *m_pQmlJSEditorPlugin;
};

}// namespace JsEditorTools


#endif // JSEDITORTOOLS_H

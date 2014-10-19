#ifndef JSEDITORTOOLS_H
#define JSEDITORTOOLS_H

#include "jseditortools_global.h"
#include <coreplugin/icore.h>

class QMainWindow;
class QStringList;

namespace ExtensionSystem {
class PluginManager;
}

namespace Core {
namespace Internal {
class CorePlugin;
}
class IDocument;
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

    void newFileInEditor();
    void openFileInEditor();
private:
    QMainWindow *m_MainWindow;

    ExtensionSystem::PluginManager *m_pPluginManager;
    Core::Internal::CorePlugin *m_pCorePlugin;
    TextEditor::Internal::TextEditorPlugin *m_pTextEditorPlugin;
    QmlJSTools::Internal::QmlJSToolsPlugin *m_pQmlJSToolsPlugin;
    QmlJSEditor::Internal::QmlJSEditorPlugin *m_pQmlJSEditorPlugin;

    Core::IDocument *openFiles(const QStringList &fileNames, Core::ICore::OpenFilesFlags flags);
};

}// namespace JsEditorTools


#endif // JSEDITORTOOLS_H

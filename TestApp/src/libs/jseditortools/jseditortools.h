#ifndef JSEDITORTOOLS_H
#define JSEDITORTOOLS_H

#include "jseditortools_global.h"

#include <QObject>

class QMainWindow;
class QStringList;

namespace ExtensionSystem {
class PluginManager;
}

namespace Core {
namespace Internal {
class CorePlugin;
}
//class IDocument;
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

class JSEditorMenuItems;

class JSEDITORTOOLS_EXPORT JsEditorToolsLib : public QObject {
    Q_OBJECT
public:
    JsEditorToolsLib(QWidget *mainWindow);
    ~JsEditorToolsLib();

    void setParentWidget(QWidget *mainWIndow);
    JSEditorMenuItems *getJSEditorMenuItems() { return m_pJSEditorMenuItems; }
private:
    QWidget *m_MainWindow;

    ExtensionSystem::PluginManager *m_pPluginManager;
    Core::Internal::CorePlugin *m_pCorePlugin;
    TextEditor::Internal::TextEditorPlugin *m_pTextEditorPlugin;
    QmlJSTools::Internal::QmlJSToolsPlugin *m_pQmlJSToolsPlugin;
    QmlJSEditor::Internal::QmlJSEditorPlugin *m_pQmlJSEditorPlugin;

    JSEditorMenuItems *m_pJSEditorMenuItems;
};

}// namespace JsEditorTools


#endif // JSEDITORTOOLS_H

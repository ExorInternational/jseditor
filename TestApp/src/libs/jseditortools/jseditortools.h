#ifndef JSEDITORTOOLS_H
#define JSEDITORTOOLS_H

#include "jseditortools_global.h"

#include <QObject>
#include <QHash>//#720 ROOPAK 

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

class JSEDITORTOOLS_EXPORT JSCustomBuiltinKey//#720 ROOPAK - START
{
public:
    JSCustomBuiltinKey() 
    {
        m_bDeclareGlobalObject = false;
    }
    JSCustomBuiltinKey(const JSCustomBuiltinKey &other)
    {
        this->m_strClassName = other.m_strClassName;
        this->m_bDeclareGlobalObject = other.m_bDeclareGlobalObject;
        this->m_strObjectName = other.m_strObjectName;
    }
    JSCustomBuiltinKey &operator=(const JSCustomBuiltinKey &other)
    {
        if (this != &other)
        {
            this->m_strClassName = other.m_strClassName;
            this->m_bDeclareGlobalObject = other.m_bDeclareGlobalObject;
            this->m_strObjectName = other.m_strObjectName;
        }
        return *this;
    }
    bool operator==(const JSCustomBuiltinKey &other) const 
    { 
        bool bRet = (this->m_strClassName == other.m_strClassName) &&
                    (this->m_bDeclareGlobalObject == other.m_bDeclareGlobalObject) &&
                    (this->m_strObjectName == other.m_strObjectName);
        return bRet; 
    }
    bool operator< (const JSCustomBuiltinKey &other) const 
    {
        return m_strClassName < other.m_strClassName;
    }
    QString m_strClassName;
    bool m_bDeclareGlobalObject;
    QString m_strObjectName;
    
};//#720 ROOPAK - END
class JSEditorMenuItems;

class JSEDITORTOOLS_EXPORT JsEditorToolsLib : public QObject {
    Q_OBJECT
public:
    JsEditorToolsLib(QWidget *mainWindow);
    ~JsEditorToolsLib();

    void setParentWidget(QWidget *mainWIndow);
    void setCustomBuiltinTypes(QMap<JsEditorTools::JSCustomBuiltinKey, QObject *> oCustomClassTypesList);//#720 ROOPAK 
    JSEditorMenuItems *getJSEditorMenuItems();

    bool openFile(QString strFilePath);
    QString getCurrentDocumentText();
    void undo();
    bool isUndoEnabled();
    void redo();
    bool isRedoEnabled();
    void doCopy();
    void doCut();
    bool isPasteEnabled();
    void doPaste();
    void doSelectAll();
signals:
    void currentDocumentChanged();
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

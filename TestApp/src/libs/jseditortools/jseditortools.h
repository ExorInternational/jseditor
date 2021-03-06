#ifndef JSEDITORTOOLS_H
#define JSEDITORTOOLS_H

#include "jseditortools_global.h"

#include <QObject>
#include <QHash>//#720 ROOPAK 
#include <QLayout>
#include <QPlainTextEdit>
#include <QTranslator>
#include <QDialog>

class QMainWindow;
class QStringList;
class QSettings;

namespace ExtensionSystem {
class PluginManager;
}

namespace Core {
namespace Internal {
class CorePlugin;
}
//class IDocument;
class IEditor;
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


class JSEDITORTOOLS_EXPORT FindDialog : public QDialog {
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = 0, Qt::WindowFlags f = 0): QDialog(parent, f){  }
signals:
    void isClosing();
protected:
    void closeEvent(QCloseEvent * e){ emit isClosing(); QDialog::closeEvent(e); }
};

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
    JsEditorToolsLib(QWidget *mainWindow, QString strLocale=QString());
    ~JsEditorToolsLib();

    void setParentWidget(QWidget *mainWIndow, QString strLocale);
    void setCustomBuiltinTypes(QMap<JsEditorTools::JSCustomBuiltinKey, QMetaObject> oCustomClassTypesList);//#720 ROOPAK
    JSEditorMenuItems *getJSEditorMenuItems();
    void setLayout(QLayout *pLayout);

    QPlainTextEdit *openFile(QString strFilePath);
    QPlainTextEdit *openNewEditorWidget(QString strContentTitle);
    QString getCurrentDocumentText();
    void setTextToCurrentDocument(QString strText);
    void undo();
    bool isUndoEnabled();
    void redo();
    bool isRedoEnabled();
    void doCopy();
    void doCut();
    bool isPasteEnabled();
    void doPaste();
    void doSelectAll();
    void goToLine(QPlainTextEdit *pTextEdit, int lineNumber);
    QWidget *getFindDialog();
    void removeEditor(QPlainTextEdit *pTextEdit);
    QString getTextWithNewLine(QPlainTextEdit *pTextEdit);
    void clearSearchResults();
private slots:
    void openDetatchedFindDialog();
    void onTextEditorFocused();
    void showGoToLineDialog();
    bool showOptionsDialog();
signals:
    void currentDocumentChanged();
    void searchResultItemSelected(QString strFileName, int lineNumber);
    void showFindDialog();
    void hideFindDialog();
private:
    void populateAlternateContextMenu(QPlainTextEdit *pTextEdit, QMenu *pMenu);
    void loadTranslator(QSettings *settings);

    QWidget *m_MainWindow;
    QWidget *m_pDummyMainWidget;

    ExtensionSystem::PluginManager *m_pPluginManager;
    Core::Internal::CorePlugin *m_pCorePlugin;
    TextEditor::Internal::TextEditorPlugin *m_pTextEditorPlugin;
    QmlJSTools::Internal::QmlJSToolsPlugin *m_pQmlJSToolsPlugin;
    QmlJSEditor::Internal::QmlJSEditorPlugin *m_pQmlJSEditorPlugin;

    JSEditorMenuItems *m_pJSEditorMenuItems;
    QWidget *m_pDetachedFindWindow;
    QList<Core::IEditor *> m_pDetatchedEditors;
    QTranslator m_oTranslator;
};

}// namespace JsEditorTools


#endif // JSEDITORTOOLS_H

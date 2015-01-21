#ifndef MAINWINDOW_APP_H
#define MAINWINDOW_APP_H

#include <QMainWindow>
#include <QPlainTextEdit>

#define USE_MDI_AND_TEXTEDIT_CONTROLS

class QMdiArea;

class CWidget;
class CProjectWgt;
class CPageWgt;
class CStateObj;
class CGroupObj;
class CJSTagObj;
class CFileSystemObj;

namespace Ui {
class MainWindowApp;
}

namespace JsEditorTools {
class JsEditorToolsLib;
class JSEditorMenuItems;
}

class MainWindowApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowApp(QWidget *parent = 0);
    ~MainWindowApp();
private slots:
#ifdef USE_MDI_AND_TEXTEDIT_CONTROLS
    void onFileNewClicked();
    void onFileOpenClicked();
    void onSearchResultItemSelected(QString filename, int lineNumber);
    void onSubWindowAboutToBeActivated();
#endif
private:
    void loadLibrary();
    void createCustomBuiltinTypes();
    void createMenus();

    Ui::MainWindowApp *ui;
    JsEditorTools::JsEditorToolsLib *m_pJsEditorTools;
    QMenu *m_pFileMenu;
    QMenu *m_pEditMenu;
    QMenu *m_pToolsMenu;
    QMenu *m_pWindowMenu;
#ifdef USE_MDI_AND_TEXTEDIT_CONTROLS
    QMdiArea *m_mdiArea;
#else
    QWidget *m_pCentralWidget;
#endif
    
    //Built-in Types
    CProjectWgt *m_pProjectWgt;
    CPageWgt* m_pPageObject;
    CStateObj* m_pStateObject;
    CWidget *m_pWidgetObject;
    CGroupObj* m_pGroupObject;
    CJSTagObj* m_pTagObject;
    CFileSystemObj* m_pFileSystemObject;
    QMap<QString, QPlainTextEdit *> m_oTextEditFileNameMap;
};

#endif // MAINWINDOW_APP_H

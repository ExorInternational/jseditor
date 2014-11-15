#ifndef MAINWINDOW_APP_H
#define MAINWINDOW_APP_H

#include <QMainWindow>

class CWidget;

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
    QWidget *m_pCentralWidget;
    
    //Built-in Types
    CWidget *m_pWidgetObject;
};

#endif // MAINWINDOW_APP_H

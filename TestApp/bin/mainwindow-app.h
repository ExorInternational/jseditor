#ifndef MAINWINDOW_APP_H
#define MAINWINDOW_APP_H

#include <QMainWindow>

namespace Ui {
class MainWindowApp;
}

//namespace Core {
//namespace Internal {
//class CorePlugin;
//}
//}

namespace JsEditorTools {
class JsEditorToolsLib;
}

class MainWindowApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowApp(QWidget *parent = 0);
    ~MainWindowApp();
private slots:
    void onFileOpenClicked();
private:
    Ui::MainWindowApp *ui;
//    Core::Internal::CorePlugin *m_pCorePlugin;
    JsEditorTools::JsEditorToolsLib *m_pJsEditorTools;
};

#endif // MAINWINDOW_APP_H

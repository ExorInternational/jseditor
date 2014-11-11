#ifndef MAINWINDOW_APP_H
#define MAINWINDOW_APP_H

#include <QMainWindow>

namespace Ui {
class MainWindowApp;
}

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

private:
    void loadLibrary();
    void createMenus();

    Ui::MainWindowApp *ui;
    JsEditorTools::JsEditorToolsLib *m_pJsEditorTools;
    QWidget *m_pCentralWidget;
};

#endif // MAINWINDOW_APP_H

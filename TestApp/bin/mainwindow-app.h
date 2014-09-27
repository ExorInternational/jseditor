#ifndef MAINWINDOW_APP_H
#define MAINWINDOW_APP_H

#include <QMainWindow>

namespace Ui {
class MainWindowApp;
}

namespace Core {
namespace Internal {
class CorePlugin;
}
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
    Core::Internal::CorePlugin *m_pCorePlugin;
};

#endif // MAINWINDOW_APP_H

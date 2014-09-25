#ifndef MAINWINDOW_APP_H
#define MAINWINDOW_APP_H

#include <QMainWindow>

namespace Ui {
class MainWindowApp;
}

class MainWindowApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowApp(QWidget *parent = 0);
    ~MainWindowApp();

private:
    Ui::MainWindowApp *ui;
private slots:
    void onFileOpenClicked();
};

#endif // MAINWINDOW_APP_H

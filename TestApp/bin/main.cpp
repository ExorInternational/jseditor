#include "mainwindow-app.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowApp w;
    w.show();

    return a.exec();
}

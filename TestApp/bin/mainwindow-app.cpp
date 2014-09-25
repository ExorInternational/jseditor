#include "mainwindow-app.h"
#include "ui_mainwindow-app.h"

#include <QFileDialog>

//#include <utils/proxyaction.h>//test - remove it

MainWindowApp::MainWindowApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowApp)
{
//    Utils::ProxyAction *pA = new Utils::ProxyAction();//test - remove it

    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->mainToolBar->hide();

    QMenu *fileMenu = ui->menuBar->addMenu("File");
    fileMenu->addAction("Open", this, SLOT(onFileOpenClicked()));
    fileMenu->addAction("Exit", qApp, SLOT(quit()));
}

MainWindowApp::~MainWindowApp()
{
    delete ui;
}
void MainWindowApp::onFileOpenClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home",
                                                     tr("Javascript Files (*.js)"));
}

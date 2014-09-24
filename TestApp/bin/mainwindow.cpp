#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

//#include <utils/proxyaction.h>//test - remove it

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    Utils::ProxyAction *pA = new Utils::ProxyAction();//test - remove it

    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    ui->mainToolBar->hide();

    QMenu *fileMenu = ui->menuBar->addMenu("File");
    fileMenu->addAction("Open", this, SLOT(onFileOpenClicked()));
    fileMenu->addAction("Exit", qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onFileOpenClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home",
                                                     tr("Javascript Files (*.js)"));
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
                                                     tr("Images (*.js)"));
}

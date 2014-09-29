#include "mainwindow-app.h"
#include "ui_mainwindow-app.h"

#include <QFileDialog>

#include <jseditortools/jseditortools.h>

MainWindowApp::MainWindowApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowApp)
{

    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    m_pJsEditorTools = new JsEditorTools::JsEditorToolsLib(this);
}

MainWindowApp::~MainWindowApp()
{
    delete ui;

    if(m_pJsEditorTools)
        delete m_pJsEditorTools;
    m_pJsEditorTools = 0;
}


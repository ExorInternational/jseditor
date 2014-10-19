#include "mainwindow-app.h"
#include "ui_mainwindow-app.h"

#include <QFileDialog>
#include <QMenuBar>

#include <jseditortools/jseditortools.h>

MainWindowApp::MainWindowApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowApp)
{

    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    m_pJsEditorTools = new JsEditorTools::JsEditorToolsLib(this);
    createMenus();
}

MainWindowApp::~MainWindowApp()
{
    delete ui;

    if(m_pJsEditorTools)
        delete m_pJsEditorTools;
    m_pJsEditorTools = 0;
}

void MainWindowApp::createMenus()
{
    QMenuBar *menuBar = new QMenuBar(ui->dockWidget);
    m_pFileMenu = menuBar->addMenu("File");
    m_pFileMenu->addAction("New", this, SLOT(onFileNew()));
    m_pFileMenu->addAction("Open", this, SLOT(onFileOpen()));
}

void MainWindowApp::onFileNew()
{
    m_pJsEditorTools->newFileInEditor();
}
void MainWindowApp::onFileOpen()
{
    m_pJsEditorTools->openFileInEditor();
}

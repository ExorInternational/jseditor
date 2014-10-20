#include "mainwindow-app.h"
#include "ui_mainwindow-app.h"

#include <QFileDialog>
#include <QMenuBar>

#include <jseditortools/jseditortools.h>
#include <jseditortools/jseditormenuitems.h>

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
//    m_pFileMenu->addAction("New", this, SLOT(onFileNew()));
//    m_pFileMenu->addAction("Open", this, SLOT(onFileOpen()));
    QList<QAction *>fileMenuActions = m_pJsEditorTools->getJSEditorMenuItems()->getFileMenuItems()->actions();
    for(int i=0; i<fileMenuActions.count(); i++)
    {
        m_pFileMenu->addAction(fileMenuActions.at(i));
    }
}

//void MainWindowApp::onFileNew()
//{
//    m_pJsEditorTools->getJSEditorMenuItems()->newFileInEditor();
//}
//void MainWindowApp::onFileOpen()
//{
//    m_pJsEditorTools->getJSEditorMenuItems()->openFileInEditor();
//}

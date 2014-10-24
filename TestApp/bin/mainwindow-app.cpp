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
    menuBar->resize(400, menuBar->size().height());
    menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getFileMenu());
    menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getEditMenu());
    menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getToolsMenu());
}


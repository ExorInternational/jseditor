#include "mainwindow-app.h"
#include "ui_mainwindow-app.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QGridLayout>

#include <jseditortools/jseditortools.h>
#include <jseditortools/jseditormenuitems.h>

MainWindowApp::MainWindowApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowApp)
{

    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    m_pCentralWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(m_pCentralWidget);
    gridLayout->setMargin(0);
    setCentralWidget(m_pCentralWidget);

    m_pJsEditorTools = new JsEditorTools::JsEditorToolsLib(m_pCentralWidget);
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
    QMenuBar *menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);
    menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getFileMenu());
    menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getEditMenu());
    menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getToolsMenu());
    menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getWindowMenu());
}


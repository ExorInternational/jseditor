#include "mainwindow-app.h"
#include "ui_mainwindow-app.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QGridLayout>
#include <QLibrary>
#include <QDebug>

#define USE_QLIBRARY_IMPORT true

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
    
    m_pJsEditorTools = NULL;
    loadLibrary();
}

MainWindowApp::~MainWindowApp()
{
    delete ui;

    if(m_pJsEditorTools)
        delete m_pJsEditorTools;
    m_pJsEditorTools = 0;
}
void MainWindowApp::loadLibrary()
{
#ifdef USE_QLIBRARY_IMPORT
    QLibrary jsEditorLibrary;
#if defined(Q_OS_WIN32) 
    jsEditorLibrary.setFileName("../lib/TestApp/JsEditorTools.dll");
#else defined(Q_OS_MAC || Q_OS_LINUX)
    jsEditorLibrary.setFileName("../lib/TestApp/libJsEditorTools");
#endif
    if(jsEditorLibrary.load())
    {
        typedef QObject* (*getJSEditorLibrary)(QWidget *);
        getJSEditorLibrary library=(getJSEditorLibrary)jsEditorLibrary.resolve("create");
        if (library)
        {
            m_pJsEditorTools = (JsEditorTools::JsEditorToolsLib *)library(m_pCentralWidget);
        }
    }
    else
        qDebug() << jsEditorLibrary.errorString();
#else   //default C++ way of linking DLL
    m_pJsEditorTools = new JsEditorTools::JsEditorToolsLib(m_pCentralWidget);
#endif
    createMenus();
}
void MainWindowApp::createMenus()
{
    if(m_pJsEditorTools)
    {
        QMenuBar *menuBar = new QMenuBar(this);
        this->setMenuBar(menuBar);
        menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getFileMenu());
        menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getEditMenu());
        menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getToolsMenu());
        menuBar->addMenu(m_pJsEditorTools->getJSEditorMenuItems()->getWindowMenu());
    }
}


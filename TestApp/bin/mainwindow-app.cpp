#include "mainwindow-app.h"
#include "ui_mainwindow-app.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QGridLayout>
#include <QLibrary>
#include <QDebug>

//#define USE_QLIBRARY_IMPORT true

#include <jseditortools.h>
#include <jseditormenuitems.h>

//builtin-types
#include "CustomTypes/Widget.h"
#include "CustomTypes/ProjectWgt.h"
#include "CustomTypes/PageWgt.h"
#include "CustomTypes/JSObjects.h"
#include "CustomTypes/FileSystemObj.h"

template< class T > void SafeDelete( T*& pVal )
{
    delete pVal;
    pVal = NULL;
}


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
    
    //custom builtin types
    m_pProjectWgt = NULL;
    m_pPageObject = NULL;
    m_pStateObject = NULL;
    m_pWidgetObject = NULL;
    m_pGroupObject = NULL;
    m_pTagObject = NULL;
    m_pFileSystemObject = NULL;
    loadLibrary();
}

MainWindowApp::~MainWindowApp()
{
    delete ui;

    SafeDelete(m_pProjectWgt);
    SafeDelete(m_pPageObject);
    SafeDelete(m_pStateObject);
    SafeDelete(m_pWidgetObject);
    SafeDelete(m_pGroupObject);
    SafeDelete(m_pTagObject);
    SafeDelete(m_pFileSystemObject);
    
    SafeDelete(m_pJsEditorTools);
}
void MainWindowApp::loadLibrary()
{
/*#ifdef USE_QLIBRARY_IMPORT
    QLibrary jsEditorLibrary;
#if defined(Q_OS_WIN32) 
#ifdef QT_DEBUG
    jsEditorLibrary.setFileName("../lib/TestApp/JsEditorToolsd.dll");
#else
    jsEditorLibrary.setFileName("../lib/TestApp/JsEditorTools.dll");
#endif
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

        if(m_pJsEditorTools)
        {
            typedef QMenu* (*getJSEditorMenu)(QString);
            getJSEditorMenu menu=(getJSEditorMenu)jsEditorLibrary.resolve("getMenu");
            if(menu)
            {
                m_pFileMenu = (QMenu*)menu(QLatin1String("File"));
                m_pEditMenu = (QMenu*)menu(QLatin1String("Edit"));
                m_pToolsMenu = (QMenu*)menu(QLatin1String("Tools"));
                m_pWindowMenu = (QMenu*)menu(QLatin1String("Window"));
            }
        }
    }
    else
        qDebug() << jsEditorLibrary.errorString();
#else*/   //default C++ way of linking DLL
    m_pJsEditorTools = new JsEditorTools::JsEditorToolsLib(m_pCentralWidget);
    if(m_pJsEditorTools)
    {
        createCustomBuiltinTypes();
        
        m_pFileMenu = m_pJsEditorTools->getJSEditorMenuItems()->getFileMenu();
        m_pEditMenu = m_pJsEditorTools->getJSEditorMenuItems()->getEditMenu();
        m_pToolsMenu = m_pJsEditorTools->getJSEditorMenuItems()->getToolsMenu();
        m_pWindowMenu = m_pJsEditorTools->getJSEditorMenuItems()->getWindowMenu();
    }
//#endif
    createMenus();
}
void MainWindowApp::createCustomBuiltinTypes()
{
#ifndef USE_QLIBRARY_IMPORT
    if(m_pJsEditorTools)
    {
        QMap<JsEditorTools::JSCustomBuiltinKey, QObject *> oCustomClassTypesList;
        
        //Widget Object
        if(m_pWidgetObject == NULL)
            m_pWidgetObject = new CWidget();
        JsEditorTools::JSCustomBuiltinKey widgetKey;
        widgetKey.m_strClassName = "Widget";
        oCustomClassTypesList.insert(widgetKey, m_pWidgetObject);
        
        //Project Widget
        if(m_pProjectWgt == NULL)
            m_pProjectWgt = new CProjectWgt();
        JsEditorTools::JSCustomBuiltinKey prjKey;
        prjKey.m_strClassName = "Project";
        prjKey.m_bDeclareGlobalObject = true;
        prjKey.m_strObjectName = "project";
        oCustomClassTypesList.insert(prjKey, m_pProjectWgt);
        
        //Page Widget
        if(m_pPageObject == NULL)
            m_pPageObject = new CPageWgt();
        JsEditorTools::JSCustomBuiltinKey pageKey;
        pageKey.m_strClassName = "Page";
        pageKey.m_bDeclareGlobalObject = true;
        pageKey.m_strObjectName = "page";
        oCustomClassTypesList.insert(pageKey, m_pPageObject);
        
        //State Widget
        if(m_pStateObject == NULL)
            m_pStateObject = new CStateObj();
        JsEditorTools::JSCustomBuiltinKey stateKey;
        stateKey.m_strClassName = "State";
        oCustomClassTypesList.insert(stateKey, m_pStateObject);
        
        //Group Object
        if(m_pGroupObject == NULL)
            m_pGroupObject = new CGroupObj();
        JsEditorTools::JSCustomBuiltinKey groupKey;
        groupKey.m_strClassName = "Group";
        oCustomClassTypesList.insert(groupKey, m_pGroupObject);
        
        //Tag Object
        if(m_pTagObject == NULL)
            m_pTagObject = new CJSTagObj();
        JsEditorTools::JSCustomBuiltinKey tagKey;
        tagKey.m_strClassName = "Tag";
        oCustomClassTypesList.insert(tagKey, m_pTagObject);
        
        //File System Object
        if(m_pFileSystemObject == NULL)
            m_pFileSystemObject = new CFileSystemObj();
        JsEditorTools::JSCustomBuiltinKey fsKey;
        fsKey.m_strClassName = "FileSystem";
        fsKey.m_bDeclareGlobalObject = true;
        fsKey.m_strObjectName = "fs";
        oCustomClassTypesList.insert(fsKey, m_pFileSystemObject);
        
        m_pJsEditorTools->setCustomBuiltinTypes(oCustomClassTypesList);
    }
#endif
}

void MainWindowApp::createMenus()
{
    if(m_pJsEditorTools)
    {
        QMenuBar *menuBar = new QMenuBar(this);
        this->setMenuBar(menuBar);
        if(m_pFileMenu)
            menuBar->addMenu(m_pFileMenu);
        if(m_pEditMenu)
            menuBar->addMenu(m_pEditMenu);
        if(m_pToolsMenu)
            menuBar->addMenu(m_pToolsMenu);
        if(m_pWindowMenu)
            menuBar->addMenu(m_pWindowMenu);
    }
}


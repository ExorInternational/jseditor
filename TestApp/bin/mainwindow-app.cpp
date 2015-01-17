#include "mainwindow-app.h"
#include "ui_mainwindow-app.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QGridLayout>
#include <QLibrary>
#include <QDebug>
#include <QMdiArea>
#include <QMdiSubWindow>

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

#ifdef USE_MDI_AND_TEXTEDIT_CONTROLS
    m_mdiArea = new QMdiArea(this);
    m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //to test the appearance by showing if jseditortools internal widgets are overlapping
    QColor backColor;backColor.setNamedColor("LightBlue");
    m_mdiArea->setBackground(backColor);

    setCentralWidget(m_mdiArea);
#else
    m_pCentralWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(m_pCentralWidget);
    gridLayout->setMargin(0);
    setCentralWidget(m_pCentralWidget);
#endif
    
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
#ifdef USE_MDI_AND_TEXTEDIT_CONTROLS
    QWidget *pHiddenWidget = new QWidget(m_mdiArea);
    pHiddenWidget->hide();//comment it and it will enable auto-completion by Ctrl+Space
    m_pJsEditorTools = new JsEditorTools::JsEditorToolsLib(pHiddenWidget);

    connect(m_pJsEditorTools, SIGNAL(searchResultItemSelected(QString, int)), this, SLOT(onSearchResultItemSelected(QString, int) ) );
    createCustomBuiltinTypes();
#else
    m_pJsEditorTools = new JsEditorTools::JsEditorToolsLib(m_pCentralWidget);
    if(m_pJsEditorTools)
    {
        m_pJsEditorTools->setLayout(m_pCentralWidget->layout());
        createCustomBuiltinTypes();
        
        m_pFileMenu = NULL;
        m_pEditMenu = NULL;
        m_pToolsMenu = NULL;
        m_pWindowMenu = NULL;

        if(m_pJsEditorTools->getJSEditorMenuItems()) {
            m_pFileMenu = m_pJsEditorTools->getJSEditorMenuItems()->getFileMenu();
            m_pEditMenu = m_pJsEditorTools->getJSEditorMenuItems()->getEditMenu();
            m_pToolsMenu = m_pJsEditorTools->getJSEditorMenuItems()->getToolsMenu();
            m_pWindowMenu = m_pJsEditorTools->getJSEditorMenuItems()->getWindowMenu();
        }
    }
#endif
    createMenus();
}
void MainWindowApp::createCustomBuiltinTypes()
{
#ifndef USE_QLIBRARY_IMPORT
    if(m_pJsEditorTools)
    {
        QMap<JsEditorTools::JSCustomBuiltinKey, QMetaObject> oCustomClassTypesList;
        
        //Widget Object
        if(m_pWidgetObject == NULL)
            m_pWidgetObject = new CWidget();
        JsEditorTools::JSCustomBuiltinKey widgetKey;
        widgetKey.m_strClassName = "Widget";
        oCustomClassTypesList.insert(widgetKey, *(m_pWidgetObject->metaObject()));
        
        //Project Widget
        if(m_pProjectWgt == NULL)
            m_pProjectWgt = new CProjectWgt();
        JsEditorTools::JSCustomBuiltinKey prjKey;
        prjKey.m_strClassName = "Project";
        prjKey.m_bDeclareGlobalObject = true;
        prjKey.m_strObjectName = "project";
        oCustomClassTypesList.insert(prjKey, *(m_pProjectWgt->metaObject()));
        
        //Page Widget
        if(m_pPageObject == NULL)
            m_pPageObject = new CPageWgt();
        JsEditorTools::JSCustomBuiltinKey pageKey;
        pageKey.m_strClassName = "Page";
        pageKey.m_bDeclareGlobalObject = true;
        pageKey.m_strObjectName = "page";
        oCustomClassTypesList.insert(pageKey, *(m_pPageObject->metaObject()));
        
        //State Widget
        if(m_pStateObject == NULL)
            m_pStateObject = new CStateObj();
        JsEditorTools::JSCustomBuiltinKey stateKey;
        stateKey.m_strClassName = "State";
        oCustomClassTypesList.insert(stateKey, *(m_pStateObject->metaObject()));
        
        //Group Object
        if(m_pGroupObject == NULL)
            m_pGroupObject = new CGroupObj();
        JsEditorTools::JSCustomBuiltinKey groupKey;
        groupKey.m_strClassName = "Group";
        oCustomClassTypesList.insert(groupKey, *(m_pGroupObject->metaObject()));
        
        //Tag Object
        if(m_pTagObject == NULL)
            m_pTagObject = new CJSTagObj();
        JsEditorTools::JSCustomBuiltinKey tagKey;
        tagKey.m_strClassName = "Tag";
        oCustomClassTypesList.insert(tagKey, *(m_pTagObject->metaObject()));
        
        //File System Object
        if(m_pFileSystemObject == NULL)
            m_pFileSystemObject = new CFileSystemObj();
        JsEditorTools::JSCustomBuiltinKey fsKey;
        fsKey.m_strClassName = "FileSystem";
        fsKey.m_bDeclareGlobalObject = true;
        fsKey.m_strObjectName = "fs";
        oCustomClassTypesList.insert(fsKey, *(m_pFileSystemObject->metaObject()));
        
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
#ifdef USE_MDI_AND_TEXTEDIT_CONTROLS
        m_pFileMenu = new QMenu("File", this);
        m_pFileMenu->addAction("New", this, SLOT(onFileNewClicked()));
        m_pFileMenu->addAction("Open", this, SLOT(onFileOpenClicked()));
        menuBar->addMenu(m_pFileMenu);
#else
        if(m_pFileMenu)
            menuBar->addMenu(m_pFileMenu);
        if(m_pEditMenu)
            menuBar->addMenu(m_pEditMenu);
        if(m_pToolsMenu)
            menuBar->addMenu(m_pToolsMenu);
        if(m_pWindowMenu)
            menuBar->addMenu(m_pWindowMenu);
#endif
    }
}
#ifdef USE_MDI_AND_TEXTEDIT_CONTROLS
void MainWindowApp::onFileNewClicked()
{
    if(m_pJsEditorTools)
    {

    }
}
void MainWindowApp::onFileOpenClicked()
{
    if(m_pJsEditorTools)
    {
        QString fileName = QFileDialog::getOpenFileName(this, QString(QLatin1String("Open File")),
                                        QDir::homePath(),
                                        QString(QLatin1String("Javascript Files(*.js)")) );

        if(!fileName.isEmpty()) {
            QPlainTextEdit *pTextEdit = m_pJsEditorTools->openFile(fileName);
            if(pTextEdit)
            {
                m_oTextEditFileNameMap[fileName] = pTextEdit;
                QMdiSubWindow *subWindow1 = m_mdiArea->addSubWindow(pTextEdit, Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint);
                pTextEdit->show();
                subWindow1->setAttribute(Qt::WA_DeleteOnClose);

            }
        }
    }
}
void MainWindowApp::onSearchResultItemSelected(QString filename, int lineNumber)
{
    if(!filename.isEmpty() && m_oTextEditFileNameMap.contains(filename))
    {
        QList<QMdiSubWindow *>list = m_mdiArea->subWindowList();
        for(int i=0;i<list.count();i++) {
            if(list[i]->widget() == m_oTextEditFileNameMap[filename])
            {
                m_mdiArea->setActiveSubWindow(list[i]);
                list[i]->widget()->setFocus();
                m_pJsEditorTools->goToLine(m_oTextEditFileNameMap[filename], lineNumber);
                break;
            }
        }
    }
}
#endif

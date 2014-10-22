/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "mainwindow.h"
#include "icore.h"
#include "coreconstants.h"
//#include "toolsettings.h"//ROOPAK
//#include "mimetypesettings.h"//ROOPAK
#include "fancytabwidget.h"
#include "documentmanager.h"
//#include "generalsettings.h"//ROOPAK
//#include "helpmanager.h"//#720 ROOPAK
#include "idocumentfactory.h"
#include "messagemanager.h"
#include "modemanager.h"
#include "mimedatabase.h"
#include "outputpanemanager.h"
#include "plugindialog.h"
//#include "vcsmanager.h"//#720 ROOPAK
#include "variablemanager.h"
//#include "versiondialog.h"//#720 ROOPAK
//#include "statusbarmanager.h"//#720 ROOPAK
#include "id.h"
//#include "manhattanstyle.h"//#720 ROOPAK
//#include "navigationwidget.h"//#720 ROOPAK
#include "rightpane.h"
#include "editormanager/ieditorfactory.h"
//#include "statusbarwidget.h"//#720 ROOPAK
//#include "externaltoolmanager.h"//ROOPAK
//#include "editormanager/systemeditor.h"//ROOPAK

#if defined(Q_OS_MAC)
#include "macfullscreen.h"
#endif

//#include <app/app_version.h>//#720 - ROOPAK
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actionmanager_p.h>
#include <coreplugin/actionmanager/command.h>
//#include <coreplugin/dialogs/newdialog.h>//ROOPAK
#include <coreplugin/dialogs/settingsdialog.h>
//#include <coreplugin/dialogs/shortcutsettings.h>//ROOPAK
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/icorelistener.h>
//#include <coreplugin/inavigationwidgetfactory.h>//#720 ROOPAK
#include <coreplugin/progressmanager/progressmanager_p.h>
#include <coreplugin/progressmanager/progressview.h>
#include <coreplugin/settingsdatabase.h>
#include <utils/historycompleter.h>
#include <utils/hostosinfo.h>
#include <utils/stylehelper.h>
#include <utils/stringutils.h>
#include <extensionsystem/pluginmanager.h>

#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <QTimer>
#include <QUrl>
#include <QDir>
#include <QMimeData>

#include <QApplication>
#include <QCloseEvent>
#include <QMenu>
#include <QPrinter>
#include <QShortcut>
#include <QStatusBar>
#include <QToolButton>
#include <QMessageBox>
#include <QMenuBar>
#include <QPushButton>
#include <QStyleFactory>

//ADDED BY ROOPAK
//#include "dialogs/iwizard.h"//#720 ROOPAK
#include <QFileDialog>

using namespace ExtensionSystem;

namespace Core {
namespace Internal {

enum { debugMainWindow = 0 };

MainWindow::MainWindow(QMainWindow *mainWindow) :
    Utils::AppMainWindow(mainWindow),
    m_coreImpl(new ICore(this)),
    m_additionalContexts(Constants::C_GLOBAL),
    m_settingsDatabase(new SettingsDatabase(QFileInfo(PluginManager::settings()->fileName()).path(),
                                            QLatin1String(/*"QtCreator"*/Core::Constants::IDE_APPNAME_STR),
                                            this)),
    m_printer(0),
    m_actionManager(new ActionManager(this)),
    m_editorManager(0),
//    m_externalToolManager(0),//ROOPAK
    m_progressManager(new ProgressManagerPrivate),
    m_variableManager(new VariableManager),
//    m_vcsManager(new VcsManager),//#720 ROOPAK
//    m_statusBarManager(0),//#720 ROOPAK
    m_modeManager(0),
    m_mimeDatabase(new MimeDatabase),
//    m_helpManager(new HelpManager),//#720 ROOPAK
    m_modeStack(new FancyTabWidget(this->mainwindow())),//#720 ROOPAK
//    m_navigationWidget(0),//#720 ROOPAK
    m_rightPaneWidget(0),
//    m_versionDialog(0),//#720 ROOPAK
//    m_generalSettings(new GeneralSettings),//ROOPAK
//    m_shortcutSettings(new ShortcutSettings),//ROOPAK
//    m_toolSettings(new ToolSettings),//ROOPAK
//    m_mimeTypeSettings(new MimeTypeSettings),//ROOPAK
//    m_systemEditor(new SystemEditor),//ROOPAK
    m_focusToEditor(0),
//    m_newAction(0),//ROOPAK
    m_openAction(0),
//    m_openWithAction(0),//#720 ROOPAK
    m_saveAllAction(0),
    m_exitAction(0),
    m_optionsAction(0),
    m_toggleSideBarAction(0),
    m_toggleFullScreenAction(0),
    m_minimizeAction(0),
    m_zoomAction(0),
    m_toggleSideBarButton(new QToolButton)
{
    m_mainWindow->installEventFilter(this);

    ActionManager::initialize(); // must be done before registering any actions

    (void) new DocumentManager(this);
    OutputPaneManager::create();

    Utils::HistoryCompleter::setSettings(PluginManager::settings());

//    mainwindow()->setWindowTitle(tr("Qt Creator"));//#720 ROOPAK - START
//    if (!Utils::HostOsInfo::isMacHost())
//        QApplication::setWindowIcon(QIcon(QLatin1String(Constants::ICON_QTLOGO_128)));//#720 ROOPAK - END
    QCoreApplication::setApplicationName(QLatin1String(Core::Constants::IDE_APPNAME_STR));
    QCoreApplication::setApplicationVersion(QLatin1String(Core::Constants::IDE_VERSION_LONG));
    QCoreApplication::setOrganizationName(QLatin1String(Constants::IDE_SETTINGSVARIANT_STR));
    QString baseName = QApplication::style()->objectName();
    if (Utils::HostOsInfo::isAnyUnixHost() && !Utils::HostOsInfo::isMacHost()) {
        if (baseName == QLatin1String("windows")) {
            // Sometimes we get the standard windows 95 style as a fallback
            if (QStyleFactory::keys().contains(QLatin1String("Fusion"))) {
                baseName = QLatin1String("fusion"); // Qt5
            } else { // Qt4
                // e.g. if we are running on a KDE4 desktop
                QByteArray desktopEnvironment = qgetenv("DESKTOP_SESSION");
                if (desktopEnvironment == "kde")
                    baseName = QLatin1String("plastique");
                else
                    baseName = QLatin1String("cleanlooks");
            }
        }
    }
//    qApp->setStyle(new ManhattanStyle(baseName));//#720 ROOPAK

    mainwindow()->setDockNestingEnabled(true);

    mainwindow()->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    mainwindow()->setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    m_modeManager = new ModeManager(this, m_modeStack);

    registerDefaultContainers();
    registerDefaultActions();

//    m_navigationWidget = new NavigationWidget(m_toggleSideBarAction);//#720 ROOPAK
    m_rightPaneWidget = new RightPaneWidget();

//    m_statusBarManager = new StatusBarManager(this);//#720 ROOPAK
    m_messageManager = new MessageManager;
    m_editorManager = new EditorManager(this->mainwindow());
    m_editorManager->hide();
//    m_externalToolManager = new ExternalToolManager();//ROOPAK
    mainwindow()->setCentralWidget(m_modeStack);

    m_progressManager->progressView()->setParent(this->mainwindow());
    m_progressManager->progressView()->setReferenceWidget(/*m_modeStack->statusBar()*/NULL);

    connect(QApplication::instance(), SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(updateFocusWidget(QWidget*,QWidget*)));
    // Add a small Toolbutton for toggling the navigation widget
//    statusBar()->insertPermanentWidget(0, m_toggleSideBarButton);//#720 ROOPAK

//    setUnifiedTitleAndToolBarOnMac(true);
    //if (Utils::HostOsInfo::isAnyUnixHost())
        //signal(SIGINT, handleSigInt);

//    statusBar()->setProperty("p_styled", true);//#720 ROOPAK
    mainwindow()->setAcceptDrops(true);

#if defined(Q_OS_MAC)
    MacFullScreen::addFullScreen(this);
#endif
}

void MainWindow::setSidebarVisible(bool visible)
{
//    if (NavigationWidgetPlaceHolder::current()) {//#720 ROOPAK - START
//        if (m_navigationWidget->isSuppressed() && visible) {
//            m_navigationWidget->setShown(true);
//            m_navigationWidget->setSuppressed(false);
//        } else {
//            m_navigationWidget->setShown(visible);
//        }
//    }//#720 ROOPAK - END
}

void MainWindow::setSuppressNavigationWidget(bool suppress)
{
//    if (NavigationWidgetPlaceHolder::current())//#720 ROOPAK - START
//        m_navigationWidget->setSuppressed(suppress);//#720 ROOPAK - END
}

void MainWindow::setOverrideColor(const QColor &color)
{
    m_overrideColor = color;
}

void MainWindow::setIsFullScreen(bool fullScreen)
{
    if (fullScreen)
        m_toggleFullScreenAction->setText(tr("Exit Full Screen"));
    else
        m_toggleFullScreenAction->setText(tr("Enter Full Screen"));
}

MainWindow::~MainWindow()
{
//    ExtensionSystem::PluginManager::removeObject(m_shortcutSettings);//ROOPAK
//    ExtensionSystem::PluginManager::removeObject(m_generalSettings);//ROOPAK
//    ExtensionSystem::PluginManager::removeObject(m_toolSettings);//ROOPAK
//    ExtensionSystem::PluginManager::removeObject(m_mimeTypeSettings);//ROOPAK
//    ExtensionSystem::PluginManager::removeObject(m_systemEditor);//ROOPAK
//    delete m_externalToolManager;//ROOPAK
//    m_externalToolManager = 0;//ROOPAK
    delete m_messageManager;
    m_messageManager = 0;
//    delete m_shortcutSettings;//ROOPAK
//    m_shortcutSettings = 0;//ROOPAK
//    delete m_generalSettings;//ROOPAK
//    m_generalSettings = 0;//ROOPAK
//    delete m_toolSettings;//ROOPAK
//    m_toolSettings = 0;   //ROOPAK
//    delete m_mimeTypeSettings;//ROOPAK
//    m_mimeTypeSettings = 0;//ROOPAK
//    delete m_systemEditor;//ROOPAK
//    m_systemEditor = 0;//ROOPAK
    delete m_printer;
    m_printer = 0;
//    delete m_vcsManager;//#720 ROOPAK - START
//    m_vcsManager = 0;//#720 ROOPAK - END
    //we need to delete editormanager and statusbarmanager explicitly before the end of the destructor,
    //because they might trigger stuff that tries to access data from editorwindow, like removeContextWidget

    // All modes are now gone
    OutputPaneManager::destroy();

    // Now that the OutputPaneManager is gone, is a good time to delete the view
//    ExtensionSystem::PluginManager::removeObject(m_outputView);//#720 ROOPAK - START
//    delete m_outputView;//#720 ROOPAK - END

    delete m_editorManager;
    m_editorManager = 0;
    delete m_progressManager;
    m_progressManager = 0;
//    delete m_statusBarManager;//#720 ROOPAK - START
//    m_statusBarManager = 0;//#720 ROOPAK - END
    ExtensionSystem::PluginManager::removeObject(m_coreImpl);
    delete m_coreImpl;
    m_coreImpl = 0;

    delete m_rightPaneWidget;
    m_rightPaneWidget = 0;

    delete m_modeManager;
    m_modeManager = 0;
    delete m_mimeDatabase;
    m_mimeDatabase = 0;

//    delete m_helpManager;//#720 ROOPAK - START
//    m_helpManager = 0;//#720 ROOPAK - END
    delete m_variableManager;
    m_variableManager = 0;
}

bool MainWindow::init(QString *errorMessage)
{
    Q_UNUSED(errorMessage)

    if (!MimeDatabase::addMimeTypes(QLatin1String(":/core/editormanager/BinFiles.mimetypes.xml"), errorMessage))
        return false;

    ExtensionSystem::PluginManager::addObject(m_coreImpl);
//    m_statusBarManager->init();//#720 ROOPAK
    m_modeManager->init();
    m_progressManager->init(); // needs the status bar manager

//    ExtensionSystem::PluginManager::addObject(m_generalSettings);//ROOPAK
//    ExtensionSystem::PluginManager::addObject(m_shortcutSettings);//ROOPAK
//    ExtensionSystem::PluginManager::addObject(m_toolSettings);//ROOPAK
//    ExtensionSystem::PluginManager::addObject(m_mimeTypeSettings);//ROOPAK
//    ExtensionSystem::PluginManager::addObject(m_systemEditor);//ROOPAK

    // Add widget to the bottom, we create the view here instead of inside the
    // OutputPaneManager, since the StatusBarManager needs to be initialized before
//    m_outputView = new Core::StatusBarWidget;//#720 ROOPAK - START
//    m_outputView->setWidget(OutputPaneManager::instance()->buttonsWidget());
//    m_outputView->setPosition(Core::StatusBarWidget::Second);
//    ExtensionSystem::PluginManager::addObject(m_outputView);//#720 ROOPAK - END
    MessageManager::init();
    return true;
}

void MainWindow::extensionsInitialized()
{
    m_editorManager->init();
//    m_statusBarManager->extensionsInitalized();//#720 ROOPAK
    OutputPaneManager::instance()->init();
//    m_vcsManager->extensionsInitialized();//#720 ROOPAK
//    m_navigationWidget->setFactories(ExtensionSystem::PluginManager::getObjects<INavigationWidgetFactory>());//#720 ROOPAK

    readSettings();
    updateContext();

    emit m_coreImpl->coreAboutToOpen();
    // Delay restoreWindowState, since it is overridden by LayoutRequest event
    QTimer::singleShot(0, this, SLOT(restoreWindowState()));
    QTimer::singleShot(0, m_coreImpl, SIGNAL(coreOpened()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ICore::saveSettings();

    // Save opened files
    if (!DocumentManager::saveAllModifiedDocuments()) {
        event->ignore();
        return;
    }

    const QList<ICoreListener *> listeners =
        ExtensionSystem::PluginManager::getObjects<ICoreListener>();
    foreach (ICoreListener *listener, listeners) {
        if (!listener->coreAboutToClose()) {
            event->ignore();
            return;
        }
    }

    emit m_coreImpl->coreAboutToClose();

    writeSettings();

//    m_navigationWidget->closeSubWidgets();//#720 ROOPAK

    event->accept();
}

// Check for desktop file manager file drop events

static bool isDesktopFileManagerDrop(const QMimeData *d, QStringList *files = 0)
{
    if (files)
        files->clear();
    // Extract dropped files from Mime data.
    if (!d->hasUrls())
        return false;
    const QList<QUrl> urls = d->urls();
    if (urls.empty())
        return false;
    // Try to find local files
    bool hasFiles = false;
    const QList<QUrl>::const_iterator cend = urls.constEnd();
    for (QList<QUrl>::const_iterator it = urls.constBegin(); it != cend; ++it) {
        const QString fileName = it->toLocalFile();
        if (!fileName.isEmpty()) {
            hasFiles = true;
            if (files)
                files->push_back(fileName);
            else
                break; // No result list, sufficient for checking
        }
    }
    return hasFiles;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (isDesktopFileManagerDrop(event->mimeData()) && m_filesToOpenDelayed.isEmpty())
        event->accept();
    else
        event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QStringList files;
    if (isDesktopFileManagerDrop(event->mimeData(), &files)) {
        event->accept();
        m_filesToOpenDelayed.append(files);
        QTimer::singleShot(50, this, SLOT(openDelayedFiles()));
    } else {
        event->ignore();
    }
}

void MainWindow::openDelayedFiles()
{
    if (m_filesToOpenDelayed.isEmpty())
        return;
    raiseWindow();
    openFiles(m_filesToOpenDelayed, ICore::SwitchMode);
    m_filesToOpenDelayed.clear();
}

IContext *MainWindow::currentContextObject() const
{
    return m_activeContext.isEmpty() ? 0 : m_activeContext.first();
}

//QStatusBar *MainWindow::statusBar() const//#720 ROOPAK - START
//{
//    return m_modeStack->statusBar();
//}//#720 ROOPAK - END

void MainWindow::registerDefaultContainers()
{
    ActionContainer *menubar = ActionManager::createMenuBar(Constants::MENU_BAR);

    if (!Utils::HostOsInfo::isMacHost()) // System menu bar on Mac
        mainwindow()->setMenuBar(menubar->menuBar());
//    menubar->appendGroup(Constants::G_FILE);
    menubar->appendGroup(Constants::G_EDIT);
    menubar->appendGroup(Constants::G_VIEW);
    menubar->appendGroup(Constants::G_TOOLS);
    menubar->appendGroup(Constants::G_WINDOW);
    menubar->appendGroup(Constants::G_HELP);

    // File Menu
//    ActionContainer *filemenu = ActionManager::createMenu(Constants::M_FILE);
//    menubar->addMenu(filemenu, Constants::G_FILE);
//    filemenu->menu()->setTitle(tr("&File"));
//    filemenu->appendGroup(Constants::G_FILE_NEW);//#720 ROOPAK
//    filemenu->appendGroup(Constants::G_FILE_OPEN);//#720 ROOPAK
//    filemenu->appendGroup(Constants::G_FILE_PROJECT);//#720 ROOPAK
//    filemenu->appendGroup(Constants::G_FILE_SAVE);
//    filemenu->appendGroup(Constants::G_FILE_CLOSE);
//    filemenu->appendGroup(Constants::G_FILE_PRINT);
//    filemenu->appendGroup(Constants::G_FILE_OTHER);
//    connect(filemenu->menu(), SIGNAL(aboutToShow()), this, SLOT(aboutToShowRecentFiles()));//#720 ROOPAK


    // Edit Menu
    ActionContainer *medit = ActionManager::createMenu(Constants::M_EDIT);
    menubar->addMenu(medit, Constants::G_EDIT);
    medit->menu()->setTitle(tr("&Edit"));
    medit->appendGroup(Constants::G_EDIT_UNDOREDO);
    medit->appendGroup(Constants::G_EDIT_COPYPASTE);
    medit->appendGroup(Constants::G_EDIT_SELECTALL);
    medit->appendGroup(Constants::G_EDIT_ADVANCED);
    medit->appendGroup(Constants::G_EDIT_FIND);
    medit->appendGroup(Constants::G_EDIT_OTHER);

    // Tools Menu
    ActionContainer *ac = ActionManager::createMenu(Constants::M_TOOLS);
    menubar->addMenu(ac, Constants::G_TOOLS);
    ac->menu()->setTitle(tr("&Tools"));

    // Window Menu
    ActionContainer *mwindow = ActionManager::createMenu(Constants::M_WINDOW);
    menubar->addMenu(mwindow, Constants::G_WINDOW);
    mwindow->menu()->setTitle(tr("&Window"));
    mwindow->appendGroup(Constants::G_WINDOW_SIZE);
    mwindow->appendGroup(Constants::G_WINDOW_VIEWS);
    mwindow->appendGroup(Constants::G_WINDOW_PANES);
    mwindow->appendGroup(Constants::G_WINDOW_SPLIT);
    mwindow->appendGroup(Constants::G_WINDOW_NAVIGATE);
    mwindow->appendGroup(Constants::G_WINDOW_OTHER);

    // Help Menu
    ac = ActionManager::createMenu(Constants::M_HELP);
    menubar->addMenu(ac, Constants::G_HELP);
    ac->menu()->setTitle(tr("&Help"));
    ac->appendGroup(Constants::G_HELP_HELP);
    ac->appendGroup(Constants::G_HELP_SUPPORT);
    ac->appendGroup(Constants::G_HELP_ABOUT);
}

void MainWindow::registerDefaultActions()
{
//    ActionContainer *mfile = ActionManager::actionContainer(Constants::M_FILE);
    ActionContainer *medit = ActionManager::actionContainer(Constants::M_EDIT);
    ActionContainer *mtools = ActionManager::actionContainer(Constants::M_TOOLS);
    ActionContainer *mwindow = ActionManager::actionContainer(Constants::M_WINDOW);
    ActionContainer *mhelp = ActionManager::actionContainer(Constants::M_HELP);

    Context globalContext(Constants::C_GLOBAL);

    // File menu separators
//    mfile->addSeparator(globalContext, Constants::G_FILE_SAVE);
//    mfile->addSeparator(globalContext, Constants::G_FILE_PRINT);
//    mfile->addSeparator(globalContext, Constants::G_FILE_CLOSE);
//    mfile->addSeparator(globalContext, Constants::G_FILE_OTHER);
    // Edit menu separators
    medit->addSeparator(globalContext, Constants::G_EDIT_COPYPASTE);
    medit->addSeparator(globalContext, Constants::G_EDIT_SELECTALL);
    medit->addSeparator(globalContext, Constants::G_EDIT_FIND);
    medit->addSeparator(globalContext, Constants::G_EDIT_ADVANCED);

    // Return to editor shortcut: Note this requires Qt to fix up
    // handling of shortcut overrides in menus, item views, combos....
    m_focusToEditor = new QShortcut(this->mainwindow());
    Command *cmd = ActionManager::registerShortcut(m_focusToEditor, Constants::S_RETURNTOEDITOR, globalContext);
    cmd->setDefaultKeySequence(QKeySequence(Qt::Key_Escape));
    connect(m_focusToEditor, SIGNAL(activated()), this, SLOT(setFocusToEditor()));

    // New File Action
    QIcon icon = QIcon::fromTheme(QLatin1String("document-new"), QIcon(QLatin1String(Constants::ICON_NEWFILE)));
//    m_newAction = new QAction(icon, tr("&New File"), this);//#720 ROOPAK - START
//    cmd = ActionManager::registerAction(m_newAction, Constants::NEW, globalContext);
//    cmd->setDefaultKeySequence(QKeySequence::New);
//    mfile->addAction(cmd, Constants::G_FILE_NEW);
//    connect(m_newAction, SIGNAL(triggered()), this, SLOT(newFile()));//#720 ROOPAK - END

    // Open Action
//    icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(QLatin1String(Constants::ICON_OPENFILE)));
//    m_openAction = new QAction(icon, tr("&Open File or Project..."), this);
//    cmd = ActionManager::registerAction(m_openAction, Constants::OPEN, globalContext);
//    cmd->setDefaultKeySequence(QKeySequence::Open);
//    mfile->addAction(cmd, Constants::G_FILE_OPEN);
//    connect(m_openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    // Open With Action
//    m_openWithAction = new QAction(tr("Open File &With..."), this);//#720 ROOPAK - START
//    cmd = ActionManager::registerAction(m_openWithAction, Constants::OPEN_WITH, globalContext);
//    mfile->addAction(cmd, Constants::G_FILE_OPEN);
//    connect(m_openWithAction, SIGNAL(triggered()), this, SLOT(openFileWith()));//#720 ROOPAK - END

    // File->Recent Files Menu
//    ActionContainer *ac = ActionManager::createMenu(Constants::M_FILE_RECENTFILES);//#720 ROOPAK - START
//    mfile->addMenu(ac, Constants::G_FILE_OPEN);
//    ac->menu()->setTitle(tr("Recent &Files"));
//    ac->setOnAllDisabledBehavior(ActionContainer::Show);//#720 ROOPAK - END

    // Save Action
//    icon = QIcon::fromTheme(QLatin1String("document-save"), QIcon(QLatin1String(Constants::ICON_SAVEFILE)));
//    QAction *tmpaction = new QAction(icon, tr("&Save"), this);
//    tmpaction->setEnabled(false);
//    cmd = ActionManager::registerAction(tmpaction, Constants::SAVE, globalContext);
//    cmd->setDefaultKeySequence(QKeySequence::Save);
//    cmd->setAttribute(Command::CA_UpdateText);
//    cmd->setDescription(tr("Save"));
//    mfile->addAction(cmd, Constants::G_FILE_SAVE);

//    // Save As Action
//    icon = QIcon::fromTheme(QLatin1String("document-save-as"));
//    QAction *tmpaction = new QAction(icon, tr("Save &As..."), this);
//    tmpaction->setEnabled(false);
//    cmd = ActionManager::registerAction(tmpaction, Constants::SAVEAS, globalContext);
//    cmd->setDefaultKeySequence(QKeySequence(UseMacShortcuts ? tr("Ctrl+Shift+S") : QString()));
//    cmd->setAttribute(Command::CA_UpdateText);
//    cmd->setDescription(tr("Save As..."));
//    mfile->addAction(cmd, Constants::G_FILE_SAVE);

    // SaveAll Action
//    m_saveAllAction = new QAction(tr("Save A&ll"), this);
//    cmd = ActionManager::registerAction(m_saveAllAction, Constants::SAVEALL, globalContext);
//    cmd->setDefaultKeySequence(QKeySequence(UseMacShortcuts ? QString() : tr("Ctrl+Shift+S")));
//    mfile->addAction(cmd, Constants::G_FILE_SAVE);
//    connect(m_saveAllAction, SIGNAL(triggered()), this, SLOT(saveAll()));

//    // Print Action
//    icon = QIcon::fromTheme(QLatin1String("document-print"));
//    QAction *tmpaction = new QAction(icon, tr("&Print..."), this);
//    tmpaction->setEnabled(false);
//    cmd = ActionManager::registerAction(tmpaction, Constants::PRINT, globalContext);
//    cmd->setDefaultKeySequence(QKeySequence::Print);
//    mfile->addAction(cmd, Constants::G_FILE_PRINT);

    // Exit Action
//    icon = QIcon::fromTheme(QLatin1String("application-exit"));
//    m_exitAction = new QAction(icon, tr("E&xit"), this);
//    cmd = ActionManager::registerAction(m_exitAction, Constants::EXIT, globalContext);
//    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Q")));
//    mfile->addAction(cmd, Constants::G_FILE_OTHER);
//    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    // Undo Action
    icon = QIcon::fromTheme(QLatin1String("edit-undo"), QIcon(QLatin1String(Constants::ICON_UNDO)));
    QAction *tmpaction = new QAction(icon, tr("&Undo"), this);
    cmd = ActionManager::registerAction(tmpaction, Constants::UNDO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Undo);
    cmd->setAttribute(Command::CA_UpdateText);
    cmd->setDescription(tr("Undo"));
    medit->addAction(cmd, Constants::G_EDIT_UNDOREDO);
    tmpaction->setEnabled(false);

    // Redo Action
    icon = QIcon::fromTheme(QLatin1String("edit-redo"), QIcon(QLatin1String(Constants::ICON_REDO)));
    tmpaction = new QAction(icon, tr("&Redo"), this);
    cmd = ActionManager::registerAction(tmpaction, Constants::REDO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Redo);
    cmd->setAttribute(Command::CA_UpdateText);
    cmd->setDescription(tr("Redo"));
    medit->addAction(cmd, Constants::G_EDIT_UNDOREDO);
    tmpaction->setEnabled(false);

    // Cut Action
    icon = QIcon::fromTheme(QLatin1String("edit-cut"), QIcon(QLatin1String(Constants::ICON_CUT)));
    tmpaction = new QAction(icon, tr("Cu&t"), this);
    cmd = ActionManager::registerAction(tmpaction, Constants::CUT, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Cut);
    medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
    tmpaction->setEnabled(false);

    // Copy Action
    icon = QIcon::fromTheme(QLatin1String("edit-copy"), QIcon(QLatin1String(Constants::ICON_COPY)));
    tmpaction = new QAction(icon, tr("&Copy"), this);
    cmd = ActionManager::registerAction(tmpaction, Constants::COPY, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Copy);
    medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
    tmpaction->setEnabled(false);

    // Paste Action
    icon = QIcon::fromTheme(QLatin1String("edit-paste"), QIcon(QLatin1String(Constants::ICON_PASTE)));
    tmpaction = new QAction(icon, tr("&Paste"), this);
    cmd = ActionManager::registerAction(tmpaction, Constants::PASTE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Paste);
    medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
    tmpaction->setEnabled(false);

    // Select All
    icon = QIcon::fromTheme(QLatin1String("edit-select-all"));
    tmpaction = new QAction(icon, tr("Select &All"), this);
    cmd = ActionManager::registerAction(tmpaction, Constants::SELECTALL, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::SelectAll);
    medit->addAction(cmd, Constants::G_EDIT_SELECTALL);
    tmpaction->setEnabled(false);

    // Goto Action
    icon = QIcon::fromTheme(QLatin1String("go-jump"));
    tmpaction = new QAction(icon, tr("&Go to Line..."), this);
    cmd = ActionManager::registerAction(tmpaction, Constants::GOTO, globalContext);
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+L")));
    medit->addAction(cmd, Constants::G_EDIT_OTHER);
    tmpaction->setEnabled(false);

    // Options Action
    mtools->appendGroup(Constants::G_TOOLS_OPTIONS);
    mtools->addSeparator(globalContext, Constants::G_TOOLS_OPTIONS);
    m_optionsAction = new QAction(tr("&Options..."), this);
    cmd = ActionManager::registerAction(m_optionsAction, Constants::OPTIONS, globalContext);
    if (UseMacShortcuts) {
        cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+,")));
        cmd->action()->setMenuRole(QAction::PreferencesRole);
    }
    mtools->addAction(cmd, Constants::G_TOOLS_OPTIONS);
    connect(m_optionsAction, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));

    if (UseMacShortcuts) {
        // Minimize Action
        m_minimizeAction = new QAction(tr("Minimize"), this);
        cmd = ActionManager::registerAction(m_minimizeAction, Constants::MINIMIZE_WINDOW, globalContext);
        cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+M")));
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
        connect(m_minimizeAction, SIGNAL(triggered()), this, SLOT(showMinimized()));

        // Zoom Action
        m_zoomAction = new QAction(tr("Zoom"), this);
        cmd = ActionManager::registerAction(m_zoomAction, Constants::ZOOM_WINDOW, globalContext);
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
        connect(m_zoomAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

        // Window separator
        mwindow->addSeparator(globalContext, Constants::G_WINDOW_SIZE);
    }

    // Show Sidebar Action
    m_toggleSideBarAction = new QAction(QIcon(QLatin1String(Constants::ICON_TOGGLE_SIDEBAR)),
                                        tr("Show Sidebar"), this);
    m_toggleSideBarAction->setCheckable(true);
    cmd = ActionManager::registerAction(m_toggleSideBarAction, Constants::TOGGLE_SIDEBAR, globalContext);
    cmd->setAttribute(Command::CA_UpdateText);
    cmd->setDefaultKeySequence(QKeySequence(UseMacShortcuts ? tr("Ctrl+0") : tr("Alt+0")));
    connect(m_toggleSideBarAction, SIGNAL(triggered(bool)), this, SLOT(setSidebarVisible(bool)));
    m_toggleSideBarButton->setDefaultAction(cmd->action());
    mwindow->addAction(cmd, Constants::G_WINDOW_VIEWS);
    m_toggleSideBarAction->setEnabled(false);

    // Show Mode Selector Action
    m_toggleModeSelectorAction = new QAction(tr("Show Mode Selector"), this);
    m_toggleModeSelectorAction->setCheckable(true);
    cmd = ActionManager::registerAction(m_toggleModeSelectorAction, Constants::TOGGLE_MODE_SELECTOR, globalContext);
    connect(m_toggleModeSelectorAction, SIGNAL(triggered(bool)), ModeManager::instance(), SLOT(setModeSelectorVisible(bool)));
    mwindow->addAction(cmd, Constants::G_WINDOW_VIEWS);

#if defined(Q_OS_MAC)
    const QString fullScreenActionText(tr("Enter Full Screen"));
    bool supportsFullScreen = MacFullScreen::supportsFullScreen();
#else
    const QString fullScreenActionText(tr("Full Screen"));
    bool supportsFullScreen = true;
#endif
    if (supportsFullScreen) {
        // Full Screen Action
        m_toggleFullScreenAction = new QAction(fullScreenActionText, this);
        m_toggleFullScreenAction->setMenuRole(QAction::NoRole);
        m_toggleFullScreenAction->setCheckable(!Utils::HostOsInfo::isMacHost());
        cmd = ActionManager::registerAction(m_toggleFullScreenAction, Constants::TOGGLE_FULLSCREEN, globalContext);
        cmd->setDefaultKeySequence(QKeySequence(UseMacShortcuts ? tr("Ctrl+Meta+F") : tr("Ctrl+Shift+F11")));
        cmd->setAttribute(Command::CA_UpdateText); /* for Mac */
        mwindow->addAction(cmd, Constants::G_WINDOW_SIZE);
        connect(m_toggleFullScreenAction, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
    }

    // Window->Views
    ActionContainer *mviews = ActionManager::createMenu(Constants::M_WINDOW_VIEWS);
    mwindow->addMenu(mviews, Constants::G_WINDOW_VIEWS);
    mviews->menu()->setTitle(tr("&Views"));

    // "Help" separators
    mhelp->addSeparator(globalContext, Constants::G_HELP_SUPPORT);
    if (!Utils::HostOsInfo::isMacHost())
        mhelp->addSeparator(globalContext, Constants::G_HELP_ABOUT);

    // About IDE Action
//    icon = QIcon::fromTheme(QLatin1String("help-about"));//#720 ROOPAK - START
//    if (Utils::HostOsInfo::isMacHost())
//        tmpaction = new QAction(icon, tr("About &Qt Creator"), this); // it's convention not to add dots to the about menu
//    else
//        tmpaction = new QAction(icon, tr("About &Qt Creator..."), this);
//    cmd = ActionManager::registerAction(tmpaction, Constants::ABOUT_QTCREATOR, globalContext);
//    if (Utils::HostOsInfo::isMacHost())
//        cmd->action()->setMenuRole(QAction::ApplicationSpecificRole);
//    mhelp->addAction(cmd, Constants::G_HELP_ABOUT);
//    tmpaction->setEnabled(true);
//    connect(tmpaction, SIGNAL(triggered()), this,  SLOT(aboutQtCreator()));//#720 ROOPAK - END

    //About Plugins Action
    tmpaction = new QAction(tr("About &Plugins..."), this);
    cmd = ActionManager::registerAction(tmpaction, Constants::ABOUT_PLUGINS, globalContext);
    if (Utils::HostOsInfo::isMacHost())
        cmd->action()->setMenuRole(QAction::ApplicationSpecificRole);
    mhelp->addAction(cmd, Constants::G_HELP_ABOUT);
    tmpaction->setEnabled(true);
    connect(tmpaction, SIGNAL(triggered()), this,  SLOT(aboutPlugins()));
    // About Qt Action
//    tmpaction = new QAction(tr("About &Qt..."), this);
//    cmd = ActionManager::registerAction(tmpaction, Constants:: ABOUT_QT, globalContext);
//    mhelp->addAction(cmd, Constants::G_HELP_ABOUT);
//    tmpaction->setEnabled(true);
//    connect(tmpaction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    // About sep
    if (!Utils::HostOsInfo::isMacHost()) { // doesn't have the "About" actions in the Help menu
        tmpaction = new QAction(this);
        tmpaction->setSeparator(true);
        cmd = ActionManager::registerAction(tmpaction, "QtCreator.Help.Sep.About", globalContext);
        mhelp->addAction(cmd, Constants::G_HELP_ABOUT);
    }
}

void MainWindow::newFile()
{
//    showNewItemDialog(tr("New", "Title of dialog"), IWizard::allWizards(), QString());//#720 ROOPAK

//    QString fileName = QFileDialog::getSaveFileName(NULL, QString(QLatin1String("New File")),
//                                QString(QLatin1String("%1/Untitled.js")).arg(QDir::homePath()),
//                                QString(QLatin1String("Javascript Files(*.js)")) );

//    if(!fileName.isEmpty()) {
//        QFile fileNew(QDir::toNativeSeparators(fileName));
//        fileNew.open(QIODevice::WriteOnly);

//        QStringList filesList;
//        filesList.append(fileNew.fileName());
//        openFiles(filesList, ICore::SwitchMode);
//    }//#720 ROOPAK - END
}

void MainWindow::openFile()
{
//    openFiles(EditorManager::getOpenFileNames(), ICore::SwitchMode);
}

//static QList<IDocumentFactory*> getNonEditorDocumentFactories()
//{
//    const QList<IDocumentFactory*> allFileFactories =
//        ExtensionSystem::PluginManager::getObjects<IDocumentFactory>();
//    QList<IDocumentFactory*> nonEditorFileFactories;
//    foreach (IDocumentFactory *factory, allFileFactories) {
//        if (!qobject_cast<IEditorFactory *>(factory))
//            nonEditorFileFactories.append(factory);
//    }
//    return nonEditorFileFactories;
//}

//static IDocumentFactory *findDocumentFactory(const QList<IDocumentFactory*> &fileFactories,
//                                     const QFileInfo &fi)
//{
//    if (const MimeType mt = MimeDatabase::findByFile(fi)) {
//        const QString type = mt.type();
//        foreach (IDocumentFactory *factory, fileFactories) {
//            if (factory->mimeTypes().contains(type))
//                return factory;
//        }
//    }
//    return 0;
//}

/*! Either opens \a fileNames with editors or loads a project.
 *
 *  \a flags can be used to stop on first failure, indicate that a file name
 *  might include line numbers and/or switch mode to edit mode.
 *
 *  \returns the first opened document. Required to support the -block flag
 *  for client mode.
 *
 *  \sa IPlugin::remoteArguments()
 */
IDocument *MainWindow::openFiles(const QStringList &fileNames, ICore::OpenFilesFlags flags)
{
//    QList<IDocumentFactory*> nonEditorFileFactories = getNonEditorDocumentFactories();
//    IDocument *res = 0;

//    foreach (const QString &fileName, fileNames) {
//        const QFileInfo fi(fileName);
//        const QString absoluteFilePath = fi.absoluteFilePath();
//        if (IDocumentFactory *documentFactory = findDocumentFactory(nonEditorFileFactories, fi)) {
//            IDocument *document = documentFactory->open(absoluteFilePath);
//            if (!document) {
//                if (flags & ICore::StopOnLoadFail)
//                    return res;
//            } else {
//                if (!res)
//                    res = document;
//                if (flags & ICore::SwitchMode)
//                    ModeManager::activateMode(Id(Core::Constants::MODE_EDIT));
//            }
//        } else {
//            QFlags<EditorManager::OpenEditorFlag> emFlags;
//            if (flags & ICore::CanContainLineNumbers)
//                emFlags |=  EditorManager::CanContainLineNumber;
//            IEditor *editor = EditorManager::openEditor(absoluteFilePath, Id(), emFlags);
//            if (!editor) {
//                if (flags & ICore::StopOnLoadFail)
//                    return res;
//            } else if (!res) {
//                res = editor->document();
//            }
//        }
//    }
//    return res;

    return NULL;
}

void MainWindow::setFocusToEditor()
{
    m_editorManager->doEscapeKeyFocusMoveMagic();
}

//void MainWindow::showNewItemDialog(const QString &title,//#720 ROOPAK - START
//                                          const QList<IWizard *> &wizards,
//                                          const QString &defaultLocation,
//                                          const QVariantMap &extraVariables)
//{
    // Scan for wizards matching the filter and pick one. Don't show
    // dialog if there is only one.
//    IWizard *wizard = 0;
//    QString selectedPlatform;
//    switch (wizards.size()) {
//    case 0:
//        break;
//    case 1:
//        wizard = wizards.front();
//        break;
//    default: {
////        NewDialog dlg(this);                      //ROOPAK - START
////        dlg.setWizards(wizards);
////        dlg.setWindowTitle(title);
////        wizard = dlg.showDialog();
////        selectedPlatform = dlg.selectedPlatform();//ROOPAK - END
//    }
//        break;
//    }

//    if (!wizard)
//        return;//#720 ROOPAK - END

//    QString path = defaultLocation;
//    if (path.isEmpty()) {
//        switch (wizard->kind()) {//#720 ROOPAK - START
//        case IWizard::ProjectWizard:
//            // Project wizards: Check for projects directory or
//            // use last visited directory of file dialog. Never start
//            // at current.
//            path = DocumentManager::useProjectsDirectory() ?
//                       DocumentManager::projectsDirectory() :
//                       DocumentManager::fileDialogLastVisitedDirectory();
//            break;
//        default:
//            path = DocumentManager::fileDialogInitialDirectory();
//            break;
//        }
//    }
//    wizard->runWizard(path, this, selectedPlatform, extraVariables);
//}//#720 ROOPAK - END

bool MainWindow::showOptionsDialog(Id category, Id page, QWidget *parent)
{
    emit m_coreImpl->optionsDialogRequested();
    if (!parent)
        parent = this->mainwindow();
    SettingsDialog *dialog = SettingsDialog::getSettingsDialog(parent, category, page);
    return dialog->execDialog();
}

void MainWindow::saveAll()
{
//    DocumentManager::saveAllModifiedDocumentsSilently();
}

void MainWindow::exit()
{
    // this function is most likely called from a user action
    // that is from an event handler of an object
    // since on close we are going to delete everything
    // so to prevent the deleting of that object we
    // just append it
    QTimer::singleShot(0, this,  SLOT(close()));
}

//void MainWindow::openFileWith()//#720 ROOPAK - START
//{
//    foreach (const QString &fileName, EditorManager::getOpenFileNames()) {
//        bool isExternal;
//        const Id editorId = EditorManager::getOpenWithEditorId(fileName, &isExternal);
//        if (!editorId.isValid())
//            continue;
//        if (isExternal)
//            EditorManager::openExternalEditor(fileName, editorId);
//        else
//            EditorManager::openEditor(fileName, editorId);
//    }
//}//#720 ROOPAK - END

IContext *MainWindow::contextObject(QWidget *widget)
{
    return m_contextWidgets.value(widget);
}

void MainWindow::addContextObject(IContext *context)
{
    if (!context)
        return;
    QWidget *widget = context->widget();
    if (m_contextWidgets.contains(widget))
        return;

    m_contextWidgets.insert(widget, context);
}

void MainWindow::removeContextObject(IContext *context)
{
    if (!context)
        return;

    QWidget *widget = context->widget();
    if (!m_contextWidgets.contains(widget))
        return;

    m_contextWidgets.remove(widget);
    if (m_activeContext.removeAll(context) > 0)
        updateContextObject(m_activeContext);
}
bool MainWindow::eventFilter( QObject *dist, QEvent *event )
{
    if(dist == m_mainWindow)
    {
        if( event->type() == QEvent::ActivationChange ||  event->type() == QEvent::WindowStateChange)
            changeEvent(event);
        else if(event->type() == QEvent::Close)
            closeEvent((QCloseEvent *)event);
        else if(event->type() == QEvent::DragEnter)
            dragEnterEvent((QDragEnterEvent *)event);
        else if(event->type() == QEvent::Drop)
            dropEvent((QDropEvent *)event);
    }

    return false;
}
void MainWindow::changeEvent(QEvent *e)
{
//    QMainWindow::changeEvent(e);//#720 ROOPAK TODO - COMMENTED OUT. NEED TO CHECK ITSVALIDITY WHEN APP IS IN RUNNING STATE
    if (e->type() == QEvent::ActivationChange) {
        if (mainwindow()->isActiveWindow()) {
            if (debugMainWindow)
                qDebug() << "main window activated";
            emit windowActivated();
        }
    } else if (e->type() == QEvent::WindowStateChange) {
        if (Utils::HostOsInfo::isMacHost()) {
            bool minimized = mainwindow()->isMinimized();
            if (debugMainWindow)
                qDebug() << "main window state changed to minimized=" << minimized;
            m_minimizeAction->setEnabled(!minimized);
            m_zoomAction->setEnabled(!minimized);
        } else {
            bool isFullScreen = (mainwindow()->windowState() & Qt::WindowFullScreen) != 0;
            m_toggleFullScreenAction->setChecked(isFullScreen);
        }
    }
}

void MainWindow::updateFocusWidget(QWidget *old, QWidget *now)
{
    Q_UNUSED(old)

    // Prevent changing the context object just because the menu or a menu item is activated
    if (qobject_cast<QMenuBar*>(now) || qobject_cast<QMenu*>(now))
        return;

    QList<IContext *> newContext;
    if (QWidget *p = qApp->focusWidget()) {
        IContext *context = 0;
        while (p) {
            context = m_contextWidgets.value(p);
            if (context)
                newContext.append(context);
            p = p->parentWidget();
        }
    }

    // ignore toplevels that define no context, like popups without parent
    if (!newContext.isEmpty() || qApp->focusWidget() == mainwindow()->focusWidget())
        updateContextObject(newContext);
}

void MainWindow::updateContextObject(const QList<IContext *> &context)
{
    emit m_coreImpl->contextAboutToChange(context);
    m_activeContext = context;
    updateContext();
    if (debugMainWindow) {
        qDebug() << "new context objects =" << context;
        foreach (IContext *c, context)
            qDebug() << (c ? c->widget() : 0) << (c ? c->widget()->metaObject()->className() : 0);
    }
}

void MainWindow::aboutToShutdown()
{
    disconnect(QApplication::instance(), SIGNAL(focusChanged(QWidget*,QWidget*)),
               this, SLOT(updateFocusWidget(QWidget*,QWidget*)));
    m_activeContext.clear();
    mainwindow()->hide();
}

static const char settingsGroup[] = "MainWindow";
static const char colorKey[] = "Color";
static const char windowGeometryKey[] = "WindowGeometry";
static const char windowStateKey[] = "WindowState";
static const char modeSelectorVisibleKey[] = "ModeSelectorVisible";

void MainWindow::readSettings()
{
    QSettings *settings = PluginManager::settings();
    settings->beginGroup(QLatin1String(settingsGroup));

    if (m_overrideColor.isValid()) {
        Utils::StyleHelper::setBaseColor(m_overrideColor);
        // Get adapted base color.
        m_overrideColor = Utils::StyleHelper::baseColor();
    } else {
        Utils::StyleHelper::setBaseColor(
                settings->value(QLatin1String(colorKey),
                                  QColor(Utils::StyleHelper::DEFAULT_BASE_COLOR)).value<QColor>());
    }

    bool modeSelectorVisible = false;//settings->value(QLatin1String(modeSelectorVisibleKey), true).toBool();//#720 - ROOPAK
    ModeManager::setModeSelectorVisible(modeSelectorVisible);
    m_toggleModeSelectorAction->setChecked(modeSelectorVisible);

    settings->endGroup();

    m_editorManager->readSettings();
//    m_navigationWidget->restoreSettings(settings);//#720 ROOPAK
    m_rightPaneWidget->readSettings(settings);
}

void MainWindow::writeSettings()
{
    QSettings *settings = PluginManager::settings();
    settings->beginGroup(QLatin1String(settingsGroup));

    if (!(m_overrideColor.isValid() && Utils::StyleHelper::baseColor() == m_overrideColor))
        settings->setValue(QLatin1String(colorKey), Utils::StyleHelper::requestedBaseColor());

    settings->setValue(QLatin1String(windowGeometryKey), mainwindow()->saveGeometry());
    settings->setValue(QLatin1String(windowStateKey), mainwindow()->saveState());
    settings->setValue(QLatin1String(modeSelectorVisibleKey), ModeManager::isModeSelectorVisible());

    settings->endGroup();

    DocumentManager::saveSettings();
    m_actionManager->saveSettings(settings);
    m_editorManager->saveSettings();
//    m_navigationWidget->saveSettings(settings);//#720 ROOPAK
}

void MainWindow::updateAdditionalContexts(const Context &remove, const Context &add)
{
    foreach (const Id id, remove) {
        if (!id.isValid())
            continue;

        int index = m_additionalContexts.indexOf(id);
        if (index != -1)
            m_additionalContexts.removeAt(index);
    }

    foreach (const Id id, add) {
        if (!id.isValid())
            continue;

        if (!m_additionalContexts.contains(id))
            m_additionalContexts.prepend(id);
    }

    updateContext();
}

void MainWindow::updateContext()
{
    Context contexts;

    foreach (IContext *context, m_activeContext)
        contexts.add(context->context());

    contexts.add(m_additionalContexts);

    Context uniquecontexts;
    for (int i = 0; i < contexts.size(); ++i) {
        const Id id = contexts.at(i);
        if (!uniquecontexts.contains(id))
            uniquecontexts.add(id);
    }

    m_actionManager->setContext(uniquecontexts);
    emit m_coreImpl->contextChanged(m_activeContext, m_additionalContexts);
}

//void MainWindow::aboutToShowRecentFiles()//#720 ROOPAK - START
//{
//    ActionContainer *aci =
//        ActionManager::actionContainer(Constants::M_FILE_RECENTFILES);
//    aci->menu()->clear();

//    bool hasRecentFiles = false;
//    foreach (const DocumentManager::RecentFile &file, DocumentManager::recentFiles()) {
//        hasRecentFiles = true;
//        QAction *action = aci->menu()->addAction(
//                    QDir::toNativeSeparators(Utils::withTildeHomePath(file.first)));
//        action->setData(qVariantFromValue(file));
//        connect(action, SIGNAL(triggered()), this, SLOT(openRecentFile()));
//    }
//    aci->menu()->setEnabled(hasRecentFiles);

//    // add the Clear Menu item
//    if (hasRecentFiles) {
//        aci->menu()->addSeparator();
//        QAction *action = aci->menu()->addAction(QCoreApplication::translate(
//                                                     "Core", Core::Constants::TR_CLEAR_MENU));
//        connect(action, SIGNAL(triggered()), DocumentManager::instance(), SLOT(clearRecentFiles()));
//    }
//}

//void MainWindow::openRecentFile()
//{
//    if (const QAction *action = qobject_cast<const QAction*>(sender())) {
//        const DocumentManager::RecentFile file = action->data().value<DocumentManager::RecentFile>();
//        EditorManager::openEditor(file.first, file.second);
//    }
//}//#720 ROOPAK - END

//void MainWindow::aboutQtCreator()//#720 ROOPAK - START
//{
//    if (!m_versionDialog) {
//        m_versionDialog = new VersionDialog(this);
//        connect(m_versionDialog, SIGNAL(finished(int)),
//                this, SLOT(destroyVersionDialog()));
//    }
//    m_versionDialog->show();
//}//#720 ROOPAK - END

//void MainWindow::destroyVersionDialog()//#720 ROOPAK - START
//{
//    if (m_versionDialog) {
//        m_versionDialog->deleteLater();
//        m_versionDialog = 0;
//    }
//}//#720 ROOPAK - END

void MainWindow::aboutPlugins()
{
    PluginDialog dialog(this->mainwindow());
    dialog.exec();
}

QPrinter *MainWindow::printer() const
{
    if (!m_printer)
        m_printer = new QPrinter(QPrinter::HighResolution);
    return m_printer;
}

void MainWindow::setFullScreen(bool on)
{
#if defined(Q_OS_MAC)
    Q_UNUSED(on)
    MacFullScreen::toggleFullScreen(this);
#else
    if (bool(mainwindow()->windowState() & Qt::WindowFullScreen) == on)
        return;

    if (on) {
        mainwindow()->setWindowState(mainwindow()->windowState() | Qt::WindowFullScreen);
        //statusBar()->hide();
        //menuBar()->hide();
    } else {
        mainwindow()->setWindowState(mainwindow()->windowState() & ~Qt::WindowFullScreen);
        //menuBar()->show();
        //statusBar()->show();
    }
#endif
}

// Display a warning with an additional button to open
// the debugger settings dialog if settingsId is nonempty.

bool MainWindow::showWarningWithOptions(const QString &title,
                                        const QString &text,
                                        const QString &details,
                                        Id settingsCategory,
                                        Id settingsId,
                                        QWidget *parent)
{
    if (parent == 0)
        parent = this->mainwindow();
    QMessageBox msgBox(QMessageBox::Warning, title, text,
                       QMessageBox::Ok, parent);
    if (!details.isEmpty())
        msgBox.setDetailedText(details);
    QAbstractButton *settingsButton = 0;
    if (settingsId.isValid() || settingsCategory.isValid())
        settingsButton = msgBox.addButton(tr("Settings..."), QMessageBox::AcceptRole);
    msgBox.exec();
    if (settingsButton && msgBox.clickedButton() == settingsButton)
        return showOptionsDialog(settingsCategory, settingsId);
    return false;
}

void MainWindow::restoreWindowState()
{
    QSettings *settings = PluginManager::settings();
    settings->beginGroup(QLatin1String(settingsGroup));
    if (!mainwindow()->restoreGeometry(settings->value(QLatin1String(windowGeometryKey)).toByteArray()))
        mainwindow()->resize(1008, 700); // size without window decoration
    mainwindow()->restoreState(settings->value(QLatin1String(windowStateKey)).toByteArray());
    settings->endGroup();
    mainwindow()->show();
}

} // namespace Internal
} // namespace Core

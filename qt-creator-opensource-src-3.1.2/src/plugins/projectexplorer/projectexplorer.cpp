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

#include "projectexplorer.h"

//#include "buildsteplist.h"//ROOPAK
//#include "customwizard/customwizard.h"//ROOPAK
//#include "deployablefile.h"//ROOPAK
//#include "deployconfiguration.h"//ROOPAK
//#include "gcctoolchainfactories.h"//ROOPAK
//#include "project.h"//#720 ROOPAK
//#include "projectexplorersettings.h"//ROOPAK
//#include "projectmacroexpander.h"//ROOPAK
//#include "removetaskhandler.h"//ROOPAK
//#include "unconfiguredprojectpanel.h"//ROOPAK
//#include "kitmanager.h"//#720 ROOPAK
//#include "kitoptionspage.h"//ROOPAK
//#include "target.h"//#720 ROOPAK
//#include "toolchainmanager.h"//#720 ROOPAK
//#include "toolchainoptionspage.h"//ROOPAK
//#include "copytaskhandler.h"//ROOPAK
//#include "showineditortaskhandler.h"//ROOPAK
//#include "vcsannotatetaskhandler.h"//ROOPAK
//#include "localapplicationruncontrol.h"//ROOPAK
//#include "allprojectsfilter.h"//ROOPAK
//#include "allprojectsfind.h"//#720 ROOPAK
//#include "buildmanager.h"//ROOPAK
//#include "buildsettingspropertiespage.h"//ROOPAK
//#include "currentprojectfind.h"//#720 ROOPAK
//#include "currentprojectfilter.h"//ROOPAK
//#include "editorsettingspropertiespage.h"//ROOPAK
//#include "codestylesettingspropertiespage.h"//ROOPAK
//#include "dependenciespanel.h"//ROOPAK
//#include "foldernavigationwidget.h"//ROOPAK
//#include "iprojectmanager.h"//#720 ROOPAK
//#include "nodesvisitor.h"//ROOPAK
//#include "appoutputpane.h"//ROOPAK
//#include "pluginfilefactory.h"//ROOPAK
//#include "processstep.h"//ROOPAK
//#include "kitinformation.h"//#720 ROOPAK
//#include "projectfilewizardextension.h"//ROOPAK
//#include "projecttreewidget.h"//ROOPAK
//#include "projectwindow.h"//ROOPAK
//#include "runsettingspropertiespage.h"//ROOPAK
//#include "session.h"//#720 ROOPAK
//#include "projectnodes.h"//ROOPAK
//#include "sessiondialog.h"//ROOPAK
//#include "projectexplorersettingspage.h"//ROOPAK
//#include "corelistenercheckingforrunningbuild.h"//ROOPAK
//#include "buildconfiguration.h"//ROOPAK
//#include "miniprojecttargetselector.h"#ROOPAK
//#include "taskhub.h"//#720 ROOPAK
//#include "customtoolchain.h"//ROOPAK
//#include "selectablefilesmodel.h"//ROOPAK
//#include <projectexplorer/customwizard/customwizard.h>//ROOPAK
//#include "devicesupport/desktopdevice.h"//ROOPAK
//#include "devicesupport/desktopdevicefactory.h"//ROOPAK
//#include "devicesupport/devicemanager.h"//ROOPAK
//#include "devicesupport/devicesettingspage.h"//ROOPAK

#ifdef Q_OS_WIN
//#    include "windebuginterface.h"//#720 ROOPAK
//#    include "msvctoolchain.h"//ROOPAK
//#    include "wincetoolchain.h"//ROOPAK
#endif

#define HAS_WELCOME_PAGE (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))

#if HAS_WELCOME_PAGE
#include "projectwelcomepage.h"
#endif

#include <extensionsystem/pluginspec.h>
#include <extensionsystem/pluginmanager.h>
#include <coreplugin/icore.h>
#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/id.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/documentmanager.h>
#include <coreplugin/imode.h>
#include <coreplugin/mimedatabase.h>
#include <coreplugin/modemanager.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/infobar.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/findplaceholder.h>
#include <coreplugin/vcsmanager.h>
#include <coreplugin/iversioncontrol.h>
#include <coreplugin/variablemanager.h>
#include <coreplugin/fileutils.h>
//#include <coreplugin/removefiledialog.h>//ROOPAK
#include <texteditor/findinfiles.h>
#include <utils/fileutils.h>
#include <utils/parameteraction.h>
#include <utils/qtcassert.h>

#include <QtPlugin>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QTimer>
#include <QWizard>

//ADDED BY ROOPAK
#include <QLayout>
#include <QPushButton>
#include <coreplugin/basefilewizard.h>
//#include "runconfiguration.h"#720 #ROOPAK
#include <utils/stringutils.h>
//ROOPAK - END
/*!
    \namespace ProjectExplorer
    The ProjectExplorer namespace contains the classes to explore projects.
*/

/*!
    \namespace ProjectExplorer::Internal
    The ProjectExplorer::Internal namespace is the internal namespace of the
    ProjectExplorer plugin.
    \internal
*/

/*!
    \class ProjectExplorer::ProjectExplorerPlugin

    \brief The ProjectExplorerPlugin class contains static accessor and utility
    functions to obtain the current project, open projects, and so on.
*/

namespace {
bool debug = false;
const char EXTERNAL_FILE_WARNING[] = "ExternalFile";
}

using namespace Core;

namespace ProjectExplorer {

struct ProjectExplorerPluginPrivate {
    ProjectExplorerPluginPrivate();

//    QMenu *m_sessionContextMenu;//#720 ROOPAK
//    QMenu *m_sessionMenu;//#720 ROOPAK
    QMenu *m_projectMenu;
    QMenu *m_subProjectMenu;
    QMenu *m_folderMenu;
    QMenu *m_fileMenu;
    QMenu *m_openWithMenu;

    QMultiMap<int, QObject*> m_actionMap;
//    QAction *m_sessionManagerAction;//#720 ROOPAK
//    QAction *m_newAction;//ROOPAK
    QAction *m_loadAction;
//    Utils::ParameterAction *m_unloadAction;//#720 ROOPAK
//    QAction *m_closeAllProjects;//#720 ROOPAK
    QAction *m_buildProjectOnlyAction;
    Utils::ParameterAction *m_buildAction;
    QAction *m_buildActionContextMenu;
//    QAction *m_buildSessionAction;//#720 ROOPAK
    QAction *m_rebuildProjectOnlyAction;
    Utils::ParameterAction *m_rebuildAction;
    QAction *m_rebuildActionContextMenu;
//    QAction *m_rebuildSessionAction;//#720 ROOPAK
    QAction *m_cleanProjectOnlyAction;
    QAction *m_deployProjectOnlyAction;
    Utils::ParameterAction *m_deployAction;
    QAction *m_deployActionContextMenu;
//    QAction *m_deploySessionAction;//#720 ROOPAK
    Utils::ParameterAction *m_cleanAction;
    QAction *m_cleanActionContextMenu;
//    QAction *m_cleanSessionAction;//#720 ROOPAK
    QAction *m_runAction;
    QAction *m_runActionContextMenu;
    QAction *m_runWithoutDeployAction;
    QAction *m_cancelBuildAction;
    QAction *m_addNewFileAction;
    QAction *m_addExistingFilesAction;
    QAction *m_addExistingDirectoryAction;
    QAction *m_addNewSubprojectAction;
    QAction *m_removeFileAction;
    QAction *m_removeProjectAction;
    QAction *m_deleteFileAction;
    QAction *m_renameFileAction;
    QAction *m_openFileAction;
    QAction *m_projectTreeCollapseAllAction;
    QAction *m_searchOnFileSystem;
    QAction *m_showInGraphicalShell;
    QAction *m_openTerminalHere;
    Utils::ParameterAction *m_setStartupProjectAction;
    QAction *m_projectSelectorAction;
    QAction *m_projectSelectorActionMenu;
    QAction *m_projectSelectorActionQuick;
    QAction *m_runSubProject;

//    Internal::ProjectWindow *m_proWindow;//ROOPAK
    QString m_sessionToRestoreAtStartup;

//    Project *m_currentProject;//#720 ROOPAK
    Context m_lastProjectContext;
//    Node *m_currentNode;//ROOPAK

//    QList<Internal::ProjectFileFactory*> m_fileFactories;//ROOPAK
    QStringList m_profileMimeTypes;
//    Internal::AppOutputPane *m_outputPane;//ROOPAK

    QList<QPair<QString, QString> > m_recentProjects; // pair of filename, displayname
    static const int m_maxRecentProjects = 25;

    QString m_lastOpenDirectory;
//    QPointer<RunConfiguration> m_delayedRunConfiguration;#720 #ROOPAK
    bool m_shouldHaveRunConfiguration;
//    RunMode m_runMode;//#720 ROOPAK
    QString m_projectFilterString;
//    Internal::MiniProjectTargetSelector * m_targetSelector;//ROOPAK
//    Internal::ProjectExplorerSettings m_projectExplorerSettings;//ROOPAK


#if HAS_WELCOME_PAGE
    Internal::ProjectWelcomePage *m_welcomePage;
#endif
    IMode *m_projectsMode;

//    TaskHub *m_taskHub;//#720 ROOPAK
//    KitManager *m_kitManager;//#720 ROOPAK
//    ToolChainManager *m_toolChainManager;//#720 ROOPAK
    bool m_shuttingDown;
    bool m_ignoreDocumentManagerChangedFile;
    QStringList m_arguments;
};

ProjectExplorerPluginPrivate::ProjectExplorerPluginPrivate() :
//    m_currentProject(0),//#720 ROOPAK
//    m_currentNode(0),//ROOPAK
    m_shouldHaveRunConfiguration(false),
//    m_runMode(NoRunMode),//#720 ROOPAK
    m_projectsMode(0),
//    m_kitManager(0),//#720 ROOPAK
//    m_toolChainManager(0),//#720 ROOPAK
    m_shuttingDown(false),
    m_ignoreDocumentManagerChangedFile(false)
{
}

class ProjectsMode : public IMode
{
public:
    ProjectsMode(QWidget *proWindow)
    {
        setWidget(proWindow);
        setContext(Context(/*Constants::C_PROJECTEXPLORER*/"Project Explorer"));//#720 ROOPAK
        setDisplayName(QCoreApplication::translate("ProjectExplorer::ProjectsMode", "Projects"));
//        setIcon(QIcon(QLatin1String(":/fancyactionbar/images/mode_Project.png")));//ROOPAK
        setIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon));//ROOPAK
        setPriority(/*Constants::P_MODE_SESSION*/85);//#720 ROOPAK
        setId(/*Constants::MODE_SESSION*/"Project");//#720 ROOPAK
        setContextHelpId(QLatin1String("Managing Projects"));
    }
};

}  // namespace ProjectExplorer

using namespace ProjectExplorer;
using namespace ProjectExplorer::Internal;


ProjectExplorerPlugin *ProjectExplorerPlugin::m_instance = 0;

ProjectExplorerPlugin::ProjectExplorerPlugin()
    : d(new ProjectExplorerPluginPrivate)
{
    m_instance = this;
}

ProjectExplorerPlugin::~ProjectExplorerPlugin()
{
#if HAS_WELCOME_PAGE
    removeObject(d->m_welcomePage);
    delete d->m_welcomePage;
#endif
    removeObject(this);
    // Force sequence of deletion:
//    delete d->m_kitManager; // remove all the profile informations//#720 ROOPAK
//    delete d->m_toolChainManager;//#720 ROOPAK

    delete d;
}

ProjectExplorerPlugin *ProjectExplorerPlugin::instance()
{
    return m_instance;
}

bool ProjectExplorerPlugin::parseArguments(const QStringList &arguments, QString * /* error */)
{
//    CustomWizard::setVerbose(arguments.count(QLatin1String("-customwizard-verbose")));//ROOPAK
    return true;
}

bool ProjectExplorerPlugin::initialize(const QStringList &arguments, QString *error)
{
//    qRegisterMetaType<ProjectExplorer::RunControl *>();//#720 ROOPAK
//    qRegisterMetaType<ProjectExplorer::DeployableFile>("ProjectExplorer::DeployableFile");//ROOPAK

    if (!parseArguments(arguments, error))
        return false;
    addObject(this);

//    addAutoReleasedObject(new DeviceManager);//ROOPAK

    // Add ToolChainFactories:
#ifdef Q_OS_WIN
//    addAutoReleasedObject(new WinDebugInterface);//#720 ROOPAK

//    addAutoReleasedObject(new Internal::MsvcToolChainFactory);//ROOPAK
//    addAutoReleasedObject(new Internal::WinCEToolChainFactory);//ROOPAK
#else
//    addAutoReleasedObject(new Internal::LinuxIccToolChainFactory);//ROOPAK
#endif
#ifndef Q_OS_MAC
//    addAutoReleasedObject(new Internal::MingwToolChainFactory); // Mingw offers cross-compiling to windows//ROOPAK
#endif
//    addAutoReleasedObject(new Internal::GccToolChainFactory);
//    addAutoReleasedObject(new Internal::ClangToolChainFactory);//ROOPAK
//    addAutoReleasedObject(new Internal::CustomToolChainFactory);//ROOPAK

//    addAutoReleasedObject(new Internal::DesktopDeviceFactory);//ROOPAK

//    d->m_kitManager = new KitManager; // register before ToolChainManager//#720 ROOPAK
//    d->m_toolChainManager = new ToolChainManager;//#720 ROOPAK

    // Register KitInformation:
//    KitManager::registerKitInformation(new DeviceTypeKitInformation);//#720 ROOPAK - START
//    KitManager::registerKitInformation(new DeviceKitInformation);
//    KitManager::registerKitInformation(new ToolChainKitInformation);
//    KitManager::registerKitInformation(new SysRootKitInformation);//#720 ROOPAK - END

//    addAutoReleasedObject(new Internal::ToolChainOptionsPage);//ROOPAK
//    addAutoReleasedObject(new KitOptionsPage);//ROOPAK

//    addAutoReleasedObject(new TaskHub);//#720 ROOPAK

    connect(ICore::instance(), SIGNAL(newItemsDialogRequested()), this, SLOT(loadCustomWizards()));

#if HAS_WELCOME_PAGE
    d->m_welcomePage = new ProjectWelcomePage;
    connect(d->m_welcomePage, SIGNAL(manageSessions()), this, SLOT(showSessionManager()));
    addObject(d->m_welcomePage);
#endif

    connect(DocumentManager::instance(), SIGNAL(currentFileChanged(QString)),
            this, SLOT(setCurrentFile(QString)));

//    QObject *sessionManager = new SessionManager(this);//#720 ROOPAK - START

//    connect(sessionManager, SIGNAL(projectAdded(ProjectExplorer::Project*)),
//            this, SIGNAL(fileListChanged()));
//    connect(sessionManager, SIGNAL(aboutToRemoveProject(ProjectExplorer::Project*)),
//            this, SLOT(invalidateProject(ProjectExplorer::Project*)));
//    connect(sessionManager, SIGNAL(projectRemoved(ProjectExplorer::Project*)),
//            this, SIGNAL(fileListChanged()));
//    connect(sessionManager, SIGNAL(projectAdded(ProjectExplorer::Project*)),
//            this, SLOT(projectAdded(ProjectExplorer::Project*)));
//    connect(sessionManager, SIGNAL(projectRemoved(ProjectExplorer::Project*)),
//            this, SLOT(projectRemoved(ProjectExplorer::Project*)));
//    connect(sessionManager, SIGNAL(startupProjectChanged(ProjectExplorer::Project*)),
//            this, SLOT(startupProjectChanged()));
//    connect(sessionManager, SIGNAL(projectDisplayNameChanged(ProjectExplorer::Project*)),
//            this, SLOT(projectDisplayNameChanged(ProjectExplorer::Project*)));
//    connect(sessionManager, SIGNAL(dependencyChanged(ProjectExplorer::Project*,ProjectExplorer::Project*)),
//            this, SLOT(updateActions()));
//    connect(sessionManager, SIGNAL(sessionLoaded(QString)),
//            this, SLOT(updateActions()));
//    connect(sessionManager, SIGNAL(sessionLoaded(QString)),
//            this, SLOT(updateWelcomePage()));//#720 ROOPAK - END

//    addAutoReleasedObject(new CustomWizardFactory<CustomProjectWizard>(Core::IWizard::ProjectWizard));//ROOPAK - START
//    addAutoReleasedObject(new CustomWizardFactory<CustomWizard>(Core::IWizard::FileWizard));
//    addAutoReleasedObject(new CustomWizardFactory<CustomWizard>(Core::IWizard::ClassWizard));//ROOPAK - END

//    d->m_proWindow = new ProjectWindow;//ROOPAK
//    addAutoReleasedObject(d->m_proWindow);//ROOPAK

//    Context globalcontext(Core::Constants::C_GLOBAL);
//    Context projecTreeContext(Constants::C_PROJECT_TREE);

//    d->m_projectsMode = new ProjectsMode(new QWidget/*d->m_proWindow*/);//ROOPAK
//    d->m_projectsMode->setEnabled(false);
//    addAutoReleasedObject(d->m_projectsMode);
////    d->m_proWindow->layout()->addWidget(new FindToolBarPlaceHolder(d->m_proWindow));//ROOPAK

////    addAutoReleasedObject(new CopyTaskHandler);//ROOPAK
////    addAutoReleasedObject(new ShowInEditorTaskHandler);//ROOPAK
////    addAutoReleasedObject(new VcsAnnotateTaskHandler);//ROOPAK
////    addAutoReleasedObject(new RemoveTaskHandler);//ROOPAK
////    addAutoReleasedObject(new CoreListener);//ROOPAK

////    d->m_outputPane = new AppOutputPane;      //ROOPAK - START
////    addAutoReleasedObject(d->m_outputPane);
////    connect(SessionManager::instance(), SIGNAL(projectRemoved(ProjectExplorer::Project*)),
////            d->m_outputPane, SLOT(projectRemoved()));

////    connect(d->m_outputPane, SIGNAL(runControlStarted(ProjectExplorer::RunControl*)),
////            this, SIGNAL(runControlStarted(ProjectExplorer::RunControl*)));
////    connect(d->m_outputPane, SIGNAL(runControlFinished(ProjectExplorer::RunControl*)),
////            this, SIGNAL(runControlFinished(ProjectExplorer::RunControl*)));//ROOPAK - END

////    addAutoReleasedObject(new AllProjectsFilter);//ROOPAK
////    addAutoReleasedObject(new CurrentProjectFilter);//ROOPAK

////    addAutoReleasedObject(new BuildSettingsPanelFactory);//ROOPAK
////    addAutoReleasedObject(new RunSettingsPanelFactory);//ROOPAK
////    addAutoReleasedObject(new EditorSettingsPanelFactory);//ROOPAK
////    addAutoReleasedObject(new CodeStyleSettingsPanelFactory);//ROOPAK
////    addAutoReleasedObject(new DependenciesPanelFactory);//ROOPAK

////    addAutoReleasedObject(new ProcessStepFactory);//ROOPAK
////    addAutoReleasedObject(new UnconfiguredProjectPanel);//ROOPAK

////    addAutoReleasedObject(new AllProjectsFind);//#720 ROOPAK
////    addAutoReleasedObject(new CurrentProjectFind);//#720 ROOPAK

////    addAutoReleasedObject(new LocalApplicationRunControlFactory);//ROOPAK

////    addAutoReleasedObject(new ProjectFileWizardExtension);//ROOPAK

//    // Settings pages
////    addAutoReleasedObject(new ProjectExplorerSettingsPage);//ROOPAK
////    addAutoReleasedObject(new DeviceSettingsPage);//ROOPAK

//    // context menus
////    ActionContainer *msessionContextMenu =//#720 ROOPAK
////        ActionManager::createMenu(Constants::M_SESSIONCONTEXT);//#720 ROOPAK - END
//    ActionContainer *mprojectContextMenu =
//        ActionManager::createMenu(Constants::M_PROJECTCONTEXT);
//    ActionContainer *msubProjectContextMenu =
//        ActionManager::createMenu(Constants::M_SUBPROJECTCONTEXT);
//    ActionContainer *mfolderContextMenu =
//        ActionManager::createMenu(Constants::M_FOLDERCONTEXT);
//    ActionContainer *mfileContextMenu =
//        ActionManager::createMenu(Constants::M_FILECONTEXT);

////    d->m_sessionContextMenu = msessionContextMenu->menu();//#720 ROOPAK
//    d->m_projectMenu = mprojectContextMenu->menu();
//    d->m_subProjectMenu = msubProjectContextMenu->menu();
//    d->m_folderMenu = mfolderContextMenu->menu();
//    d->m_fileMenu = mfileContextMenu->menu();

//    ActionContainer *mfile =
//        ActionManager::actionContainer(Core::Constants::M_FILE);
//    ActionContainer *menubar =
//        ActionManager::actionContainer(Core::Constants::MENU_BAR);

//    // build menu
//    ActionContainer *mbuild =
//        ActionManager::createMenu(Constants::M_BUILDPROJECT);
//    mbuild->menu()->setTitle(tr("&Build"));
//    menubar->addMenu(mbuild, Core::Constants::G_VIEW);

//    // debug menu
//    ActionContainer *mdebug =
//        ActionManager::createMenu(Constants::M_DEBUG);
//    mdebug->menu()->setTitle(tr("&Debug"));
//    menubar->addMenu(mdebug, Core::Constants::G_VIEW);

//    ActionContainer *mstartdebugging =
//        ActionManager::createMenu(Constants::M_DEBUG_STARTDEBUGGING);
//    mstartdebugging->menu()->setTitle(tr("&Start Debugging"));
//    mdebug->addMenu(mstartdebugging, Core::Constants::G_DEFAULT_ONE);

//    //
//    // Groups
//    //

//    mbuild->appendGroup(Constants::G_BUILD_BUILD);
//    mbuild->appendGroup(Constants::G_BUILD_DEPLOY);
//    mbuild->appendGroup(Constants::G_BUILD_REBUILD);
//    mbuild->appendGroup(Constants::G_BUILD_CLEAN);
//    mbuild->appendGroup(Constants::G_BUILD_CANCEL);
//    mbuild->appendGroup(Constants::G_BUILD_RUN);

////    msessionContextMenu->appendGroup(Constants::G_SESSION_BUILD);//#720 ROOPAK - START
////    msessionContextMenu->appendGroup(Constants::G_SESSION_REBUILD);
////    msessionContextMenu->appendGroup(Constants::G_SESSION_FILES);
////    msessionContextMenu->appendGroup(Constants::G_SESSION_OTHER);
////    msessionContextMenu->appendGroup(Constants::G_PROJECT_TREE);//#720 ROOPAK - END

//    mprojectContextMenu->appendGroup(Constants::G_PROJECT_FIRST);
//    mprojectContextMenu->appendGroup(Constants::G_PROJECT_BUILD);
//    mprojectContextMenu->appendGroup(Constants::G_PROJECT_RUN);
//    mprojectContextMenu->appendGroup(Constants::G_PROJECT_REBUILD);
//    mprojectContextMenu->appendGroup(Constants::G_PROJECT_FILES);
//    mprojectContextMenu->appendGroup(Constants::G_PROJECT_LAST);
//    mprojectContextMenu->appendGroup(Constants::G_PROJECT_TREE);

//    msubProjectContextMenu->appendGroup(Constants::G_PROJECT_FIRST);
//    msubProjectContextMenu->appendGroup(Constants::G_PROJECT_BUILD);
//    msubProjectContextMenu->appendGroup(Constants::G_PROJECT_RUN);
//    msubProjectContextMenu->appendGroup(Constants::G_PROJECT_FILES);
//    msubProjectContextMenu->appendGroup(Constants::G_PROJECT_LAST);
//    msubProjectContextMenu->appendGroup(Constants::G_PROJECT_TREE);

//    ActionContainer *runMenu = ActionManager::createMenu(Constants::RUNMENUCONTEXTMENU);
//    runMenu->setOnAllDisabledBehavior(ActionContainer::Hide);
//    QIcon runIcon = QIcon(QLatin1String(Constants::ICON_RUN));
//    runIcon.addFile(QLatin1String(Constants::ICON_RUN_SMALL));
//    runMenu->menu()->setIcon(runIcon);
//    runMenu->menu()->setTitle(tr("Run"));
//    msubProjectContextMenu->addMenu(runMenu, ProjectExplorer::Constants::G_PROJECT_RUN);

//    mfolderContextMenu->appendGroup(Constants::G_FOLDER_FILES);
//    mfolderContextMenu->appendGroup(Constants::G_FOLDER_OTHER);
//    mfolderContextMenu->appendGroup(Constants::G_FOLDER_CONFIG);
//    mfolderContextMenu->appendGroup(Constants::G_PROJECT_TREE);

//    mfileContextMenu->appendGroup(Constants::G_FILE_OPEN);
//    mfileContextMenu->appendGroup(Constants::G_FILE_OTHER);
//    mfileContextMenu->appendGroup(Constants::G_FILE_CONFIG);
//    mfileContextMenu->appendGroup(Constants::G_PROJECT_TREE);
//    // "open with" submenu
//    ActionContainer * const openWith =
//            ActionManager::createMenu(ProjectExplorer::Constants::M_OPENFILEWITHCONTEXT);
//    openWith->setOnAllDisabledBehavior(ActionContainer::Show);
//    d->m_openWithMenu = openWith->menu();
//    d->m_openWithMenu->setTitle(tr("Open With"));

//    connect(d->m_openWithMenu, SIGNAL(triggered(QAction*)),
//            DocumentManager::instance(), SLOT(executeOpenWithMenuAction(QAction*)));

//    //
//    // Separators
//    //

//    Command *cmd;

////    msessionContextMenu->addSeparator(projecTreeContext, Constants::G_SESSION_REBUILD);//#720 ROOPAK

////    msessionContextMenu->addSeparator(projecTreeContext, Constants::G_SESSION_FILES);//#720 ROOPAK
//    mprojectContextMenu->addSeparator(projecTreeContext, Constants::G_PROJECT_FILES);
//    msubProjectContextMenu->addSeparator(projecTreeContext, Constants::G_PROJECT_FILES);
//    mfile->addSeparator(globalcontext, Core::Constants::G_FILE_PROJECT);
//    mbuild->addSeparator(globalcontext, Constants::G_BUILD_REBUILD);
////    msessionContextMenu->addSeparator(globalcontext, Constants::G_SESSION_OTHER);//#720 ROOPAK
//    mbuild->addSeparator(globalcontext, Constants::G_BUILD_CANCEL);
//    mbuild->addSeparator(globalcontext, Constants::G_BUILD_RUN);
//    mprojectContextMenu->addSeparator(globalcontext, Constants::G_PROJECT_REBUILD);

//    //
//    // Actions
//    //

//    // new action
////    d->m_newAction = new QAction(tr("New Project..."), this);     //ROOPAK - START
////    cmd = ActionManager::registerAction(d->m_newAction, Constants::NEWPROJECT, globalcontext);
////    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+N")));
////    msessionContextMenu->addAction(cmd, Constants::G_SESSION_FILES);//ROOPAK - END

//    // open action
//    d->m_loadAction = new QAction(tr("Load Project..."), this);
//    cmd = ActionManager::registerAction(d->m_loadAction, Constants::LOAD, globalcontext);
//#ifndef Q_OS_MAC
//    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+O")));
//#endif
////    msessionContextMenu->addAction(cmd, Constants::G_SESSION_FILES);//#720 ROOPAK

//    // Default open action
//    d->m_openFileAction = new QAction(tr("Open File"), this);
//    cmd = ActionManager::registerAction(d->m_openFileAction, ProjectExplorer::Constants::OPENFILE,
//                       projecTreeContext);
//    mfileContextMenu->addAction(cmd, Constants::G_FILE_OPEN);

//    d->m_searchOnFileSystem = new QAction(FileUtils::msgFindInDirectory(), this);
//    cmd = ActionManager::registerAction(d->m_searchOnFileSystem, ProjectExplorer::Constants::SEARCHONFILESYSTEM, projecTreeContext);

//    mfileContextMenu->addAction(cmd, Constants::G_FILE_OTHER);
//    mfolderContextMenu->addAction(cmd, Constants::G_FOLDER_CONFIG);
//    msubProjectContextMenu->addAction(cmd, Constants::G_PROJECT_LAST);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_LAST);

//    d->m_showInGraphicalShell = new QAction(FileUtils::msgGraphicalShellAction(), this);
//    cmd = ActionManager::registerAction(d->m_showInGraphicalShell, ProjectExplorer::Constants::SHOWINGRAPHICALSHELL,
//                       projecTreeContext);
//    mfileContextMenu->addAction(cmd, Constants::G_FILE_OPEN);
//    mfolderContextMenu->addAction(cmd, Constants::G_FOLDER_FILES);

//    d->m_openTerminalHere = new QAction(FileUtils::msgTerminalAction(), this);
//    cmd = ActionManager::registerAction(d->m_openTerminalHere, ProjectExplorer::Constants::OPENTERMIANLHERE,
//                       projecTreeContext);
//    mfileContextMenu->addAction(cmd, Constants::G_FILE_OPEN);
//    mfolderContextMenu->addAction(cmd, Constants::G_FOLDER_FILES);

//    // Open With menu
//    mfileContextMenu->addMenu(openWith, ProjectExplorer::Constants::G_FILE_OPEN);

//    // recent projects menu
////    ActionContainer *mrecent =//#720 ROOPAK - START
////        ActionManager::createMenu(Constants::M_RECENTPROJECTS);
////    mrecent->menu()->setTitle(tr("Recent P&rojects"));
////    mrecent->setOnAllDisabledBehavior(ActionContainer::Show);
////    mfile->addMenu(mrecent, Core::Constants::G_FILE_OPEN);
////    connect(mfile->menu(), SIGNAL(aboutToShow()),
////        this, SLOT(updateRecentProjectMenu()));//#720 ROOPAK - END

//    // session menu
////    ActionContainer *msession = ActionManager::createMenu(Constants::M_SESSION);//#720 ROOPAK - START
////    msession->menu()->setTitle(tr("Sessions"));
////    msession->setOnAllDisabledBehavior(ActionContainer::Show);
////    mfile->addMenu(msession, Core::Constants::G_FILE_OPEN);
////    d->m_sessionMenu = msession->menu();
////    connect(mfile->menu(), SIGNAL(aboutToShow()),
////            this, SLOT(updateSessionMenu()));//#720 ROOPAK - END

//    // session manager action
////    d->m_sessionManagerAction = new QAction(tr("Session Manager..."), this);//#720 ROOPAK - START
////    cmd = ActionManager::registerAction(d->m_sessionManagerAction, Constants::NEWSESSION, globalcontext);
////    mfile->addAction(cmd, Core::Constants::G_FILE_OPEN);
////    cmd->setDefaultKeySequence(QKeySequence());//#720 ROOPAK - END


//    // XXX same action?
//    // unload action
////    d->m_unloadAction = new Utils::ParameterAction(tr("Close Project"), tr("Close Project \"%1\""),//#720 ROOPAK - START
////                                                      Utils::ParameterAction::EnabledWithParameter, this);
////    cmd = ActionManager::registerAction(d->m_unloadAction, Constants::UNLOAD, globalcontext);
////    cmd->setAttribute(Command::CA_UpdateText);
////    cmd->setDescription(d->m_unloadAction->text());
////    mfile->addAction(cmd, Core::Constants::G_FILE_PROJECT);//#720 ROOPAK - END

//    // unload session action
////    d->m_closeAllProjects = new QAction(tr("Close All Projects and Editors"), this);//#720 ROOPAK - START
////    cmd = ActionManager::registerAction(d->m_closeAllProjects, Constants::CLEARSESSION, globalcontext);
////    mfile->addAction(cmd, Core::Constants::G_FILE_PROJECT);
////    msessionContextMenu->addAction(cmd, Constants::G_SESSION_FILES);//#720 ROOPAK - END

//    // build session action
//    QIcon buildIcon = QIcon(QLatin1String(Constants::ICON_BUILD));
//    buildIcon.addFile(QLatin1String(Constants::ICON_BUILD_SMALL));
////    d->m_buildSessionAction = new QAction(buildIcon, tr("Build All"), this);//#720 ROOPAK - START
////    cmd = ActionManager::registerAction(d->m_buildSessionAction, Constants::BUILDSESSION, globalcontext);
////    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+B")));
////    mbuild->addAction(cmd, Constants::G_BUILD_BUILD);
////    msessionContextMenu->addAction(cmd, Constants::G_SESSION_BUILD);//#720 ROOPAK - END

//    // deploy session
////    d->m_deploySessionAction = new QAction(tr("Deploy All"), this);//#720 ROOPAK - START
////    cmd = ActionManager::registerAction(d->m_deploySessionAction, Constants::DEPLOYSESSION, globalcontext);
////    mbuild->addAction(cmd, Constants::G_BUILD_DEPLOY);
////    msessionContextMenu->addAction(cmd, Constants::G_SESSION_BUILD);//#720 ROOPAK - END

//    // rebuild session action
//    QIcon rebuildIcon = QIcon(QLatin1String(Constants::ICON_REBUILD));
//    rebuildIcon.addFile(QLatin1String(Constants::ICON_REBUILD_SMALL));
////    d->m_rebuildSessionAction = new QAction(rebuildIcon, tr("Rebuild All"), this);//#720 ROOPAK - START
////    cmd = ActionManager::registerAction(d->m_rebuildSessionAction, Constants::REBUILDSESSION, globalcontext);
////    mbuild->addAction(cmd, Constants::G_BUILD_REBUILD);
////    msessionContextMenu->addAction(cmd, Constants::G_SESSION_REBUILD);//#720 ROOPAK - END

//    // clean session
//    QIcon cleanIcon = QIcon(QLatin1String(Constants::ICON_CLEAN));
//    cleanIcon.addFile(QLatin1String(Constants::ICON_CLEAN_SMALL));
////    d->m_cleanSessionAction = new QAction(cleanIcon, tr("Clean All"), this);//#720 ROOPAK - START
////    cmd = ActionManager::registerAction(d->m_cleanSessionAction, Constants::CLEANSESSION, globalcontext);
////    mbuild->addAction(cmd, Constants::G_BUILD_CLEAN);
////    msessionContextMenu->addAction(cmd, Constants::G_SESSION_REBUILD);//#720 ROOPAK - END

//    // build action
//    d->m_buildAction = new Utils::ParameterAction(tr("Build Project"), tr("Build Project \"%1\""),
//                                                     Utils::ParameterAction::AlwaysEnabled, this);
//    d->m_buildAction->setIcon(buildIcon);
//    cmd = ActionManager::registerAction(d->m_buildAction, Constants::BUILD, globalcontext);
//    cmd->setAttribute(Command::CA_UpdateText);
//    cmd->setDescription(d->m_buildAction->text());
//    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+B")));
//    mbuild->addAction(cmd, Constants::G_BUILD_BUILD);

//    // Add to mode bar
//    ModeManager::addAction(cmd->action(), Constants::P_ACTION_BUILDPROJECT);

//    // deploy action
//    d->m_deployAction = new Utils::ParameterAction(tr("Deploy Project"), tr("Deploy Project \"%1\""),
//                                                     Utils::ParameterAction::AlwaysEnabled, this);
//    cmd = ActionManager::registerAction(d->m_deployAction, Constants::DEPLOY, globalcontext);
//    cmd->setAttribute(Command::CA_UpdateText);
//    cmd->setDescription(d->m_deployAction->text());
//    mbuild->addAction(cmd, Constants::G_BUILD_DEPLOY);

//    // rebuild action
//    d->m_rebuildAction = new Utils::ParameterAction(tr("Rebuild Project"), tr("Rebuild Project \"%1\""),
//                                                       Utils::ParameterAction::AlwaysEnabled, this);
//    cmd = ActionManager::registerAction(d->m_rebuildAction, Constants::REBUILD, globalcontext);
//    cmd->setAttribute(Command::CA_UpdateText);
//    cmd->setDescription(d->m_rebuildAction->text());
//    mbuild->addAction(cmd, Constants::G_BUILD_REBUILD);

//    // clean action
//    d->m_cleanAction = new Utils::ParameterAction(tr("Clean Project"), tr("Clean Project \"%1\""),
//                                                     Utils::ParameterAction::AlwaysEnabled, this);
//    cmd = ActionManager::registerAction(d->m_cleanAction, Constants::CLEAN, globalcontext);
//    cmd->setAttribute(Command::CA_UpdateText);
//    cmd->setDescription(d->m_cleanAction->text());
//    mbuild->addAction(cmd, Constants::G_BUILD_CLEAN);

//    // cancel build action
//    QIcon stopIcon = QIcon(QLatin1String(Constants::ICON_STOP));
//    stopIcon.addFile(QLatin1String(Constants::ICON_STOP_SMALL));
//    d->m_cancelBuildAction = new QAction(stopIcon, tr("Cancel Build"), this);
//    cmd = ActionManager::registerAction(d->m_cancelBuildAction, Constants::CANCELBUILD, globalcontext);
//    mbuild->addAction(cmd, Constants::G_BUILD_CANCEL);

//    // run action
//    d->m_runAction = new QAction(runIcon, tr("Run"), this);
//    cmd = ActionManager::registerAction(d->m_runAction, Constants::RUN, globalcontext);
//    cmd->setAttribute(Command::CA_UpdateText);

//    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+R")));
//    mbuild->addAction(cmd, Constants::G_BUILD_RUN);

//    ModeManager::addAction(cmd->action(), Constants::P_ACTION_RUN);

//    // Run without deployment action
//    d->m_runWithoutDeployAction = new QAction(tr("Run Without Deployment"), this);
//    cmd = ActionManager::registerAction(d->m_runWithoutDeployAction, Constants::RUNWITHOUTDEPLOY, globalcontext);
//    mbuild->addAction(cmd, Constants::G_BUILD_RUN);

//    // build action (context menu)
//    d->m_buildActionContextMenu = new QAction(tr("Build"), this);
//    cmd = ActionManager::registerAction(d->m_buildActionContextMenu, Constants::BUILDCM, projecTreeContext);
//    cmd->setAttribute(Command::CA_UpdateText);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_BUILD);

//    // rebuild action (context menu)
//    d->m_rebuildActionContextMenu = new QAction(tr("Rebuild"), this);
//    cmd = ActionManager::registerAction(d->m_rebuildActionContextMenu, Constants::REBUILDCM, projecTreeContext);
//    cmd->setAttribute(Command::CA_UpdateText);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_REBUILD);

//    // clean action (context menu)
//    d->m_cleanActionContextMenu = new QAction(tr("Clean"), this);
//    cmd = ActionManager::registerAction(d->m_cleanActionContextMenu, Constants::CLEANCM, projecTreeContext);
//    cmd->setAttribute(Command::CA_UpdateText);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_REBUILD);

//    // build without dependencies action
//    d->m_buildProjectOnlyAction = new QAction(tr("Build Without Dependencies"), this);
//    cmd = ActionManager::registerAction(d->m_buildProjectOnlyAction, Constants::BUILDPROJECTONLY, globalcontext);

//    // rebuild without dependencies action
//    d->m_rebuildProjectOnlyAction = new QAction(tr("Rebuild Without Dependencies"), this);
//    cmd = ActionManager::registerAction(d->m_rebuildProjectOnlyAction, Constants::REBUILDPROJECTONLY, globalcontext);

//    // deploy without dependencies action
//    d->m_deployProjectOnlyAction = new QAction(tr("Deploy Without Dependencies"), this);
//    cmd = ActionManager::registerAction(d->m_deployProjectOnlyAction, Constants::DEPLOYPROJECTONLY, globalcontext);

//    // clean without dependencies action
//    d->m_cleanProjectOnlyAction = new QAction(tr("Clean Without Dependencies"), this);
//    cmd = ActionManager::registerAction(d->m_cleanProjectOnlyAction, Constants::CLEANPROJECTONLY, globalcontext);

//    // deploy action (context menu)
//    d->m_deployActionContextMenu = new QAction(tr("Deploy"), this);
//    cmd = ActionManager::registerAction(d->m_deployActionContextMenu, Constants::DEPLOYCM, projecTreeContext);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_RUN);

//    d->m_runActionContextMenu = new QAction(runIcon, tr("Run"), this);
//    cmd = ActionManager::registerAction(d->m_runActionContextMenu, Constants::RUNCONTEXTMENU, projecTreeContext);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_RUN);
//    msubProjectContextMenu->addAction(cmd, Constants::G_PROJECT_RUN);

//    // add new file action
//    d->m_addNewFileAction = new QAction(tr("Add New..."), this);
//    cmd = ActionManager::registerAction(d->m_addNewFileAction, ProjectExplorer::Constants::ADDNEWFILE,
//                       projecTreeContext);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);
//    msubProjectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);
//    mfolderContextMenu->addAction(cmd, Constants::G_FOLDER_FILES);

//    // add existing file action
//    d->m_addExistingFilesAction = new QAction(tr("Add Existing Files..."), this);
//    cmd = ActionManager::registerAction(d->m_addExistingFilesAction, ProjectExplorer::Constants::ADDEXISTINGFILES,
//                       projecTreeContext);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);
//    msubProjectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);
//    mfolderContextMenu->addAction(cmd, Constants::G_FOLDER_FILES);

//    // add existing directory action
//    d->m_addExistingDirectoryAction = new QAction(tr("Add Existing Directory..."), this);
//    cmd = Core::ActionManager::registerAction(d->m_addExistingDirectoryAction,
//                                              ProjectExplorer::Constants::ADDEXISTINGDIRECTORY,
//                                              projecTreeContext);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);
//    msubProjectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);
//    mfolderContextMenu->addAction(cmd, Constants::G_FOLDER_FILES);

//    // new subproject action
//    d->m_addNewSubprojectAction = new QAction(tr("New Subproject..."), this);
//    cmd = ActionManager::registerAction(d->m_addNewSubprojectAction, ProjectExplorer::Constants::ADDNEWSUBPROJECT,
//                       projecTreeContext);
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);
//    msubProjectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);

//    // unload project again, in right position
//    mprojectContextMenu->addAction(ActionManager::command(Constants::UNLOAD), Constants::G_PROJECT_LAST);

//    // remove file action
//    d->m_removeFileAction = new QAction(tr("Remove File..."), this);
//    cmd = ActionManager::registerAction(d->m_removeFileAction, ProjectExplorer::Constants::REMOVEFILE,
//                       projecTreeContext);
//    cmd->setDefaultKeySequence(QKeySequence::Delete);
//    mfileContextMenu->addAction(cmd, Constants::G_FILE_OTHER);

//    //: Remove project from parent profile (Project explorer view); will not physically delete any files.
//    d->m_removeProjectAction = new QAction(tr("Remove Project..."), this);
//    cmd = ActionManager::registerAction(d->m_removeProjectAction, ProjectExplorer::Constants::REMOVEPROJECT,
//                       projecTreeContext);
//    msubProjectContextMenu->addAction(cmd, Constants::G_PROJECT_FILES);

//    // delete file action
//    d->m_deleteFileAction = new QAction(tr("Delete File..."), this);
//    cmd = ActionManager::registerAction(d->m_deleteFileAction, ProjectExplorer::Constants::DELETEFILE,
//                             projecTreeContext);
//    cmd->setDefaultKeySequence(QKeySequence::Delete);
//    mfileContextMenu->addAction(cmd, Constants::G_FILE_OTHER);

//    // renamefile action
//    d->m_renameFileAction = new QAction(tr("Rename..."), this);
//    cmd = ActionManager::registerAction(d->m_renameFileAction, ProjectExplorer::Constants::RENAMEFILE,
//                       projecTreeContext);
//    mfileContextMenu->addAction(cmd, Constants::G_FILE_OTHER);
//    // Not yet used by anyone, so hide for now
////    mfolder->addAction(cmd, Constants::G_FOLDER_FILES);
////    msubProject->addAction(cmd, Constants::G_FOLDER_FILES);
////    mproject->addAction(cmd, Constants::G_FOLDER_FILES);

//    // set startup project action
//    d->m_setStartupProjectAction = new Utils::ParameterAction(tr("Set as Active Project"),
//                                                              tr("Set \"%1\" as Active Project"),
//                                                              Utils::ParameterAction::AlwaysEnabled, this);
//    cmd = ActionManager::registerAction(d->m_setStartupProjectAction, ProjectExplorer::Constants::SETSTARTUP,
//                             projecTreeContext);
//    cmd->setAttribute(Command::CA_UpdateText);
//    cmd->setDescription(d->m_setStartupProjectAction->text());
//    mprojectContextMenu->addAction(cmd, Constants::G_PROJECT_FIRST);

//    // Collapse All.
//    d->m_projectTreeCollapseAllAction = new QAction(tr("Collapse All"), this);
//    cmd = ActionManager::registerAction(d->m_projectTreeCollapseAllAction, Constants::PROJECTTREE_COLLAPSE_ALL,
//                             projecTreeContext);
//    const Id treeGroup = Constants::G_PROJECT_TREE;
//    mfileContextMenu->addSeparator(globalcontext, treeGroup);
//    mfileContextMenu->addAction(cmd, treeGroup);
//    msubProjectContextMenu->addSeparator(globalcontext, treeGroup);
//    msubProjectContextMenu->addAction(cmd, treeGroup);
//    mfolderContextMenu->addSeparator(globalcontext, treeGroup);
//    mfolderContextMenu->addAction(cmd, treeGroup);
//    mprojectContextMenu->addSeparator(globalcontext, treeGroup);
//    mprojectContextMenu->addAction(cmd, treeGroup);
////    msessionContextMenu->addSeparator(globalcontext, treeGroup);//#720 ROOPAK
////    msessionContextMenu->addAction(cmd, treeGroup);//#720 ROOPAK

//    // target selector
//    d->m_projectSelectorAction = new QAction(this);
//    d->m_projectSelectorAction->setCheckable(true);
//    d->m_projectSelectorAction->setEnabled(false);
//    QWidget *mainWindow = ICore::mainWindow();
////    d->m_targetSelector = new Internal::MiniProjectTargetSelector(d->m_projectSelectorAction, mainWindow);//ROOPAK
////    connect(d->m_projectSelectorAction, SIGNAL(triggered()), d->m_targetSelector, SLOT(show()));//ROOPAK
//    ModeManager::addProjectSelector(d->m_projectSelectorAction);

//    d->m_projectSelectorActionMenu = new QAction(this);
//    d->m_projectSelectorActionMenu->setEnabled(false);
//    d->m_projectSelectorActionMenu->setText(tr("Open Build and Run Kit Selector..."));
////    connect(d->m_projectSelectorActionMenu, SIGNAL(triggered()), d->m_targetSelector, SLOT(toggleVisible()));//ROOPAK
//    cmd = ActionManager::registerAction(d->m_projectSelectorActionMenu, ProjectExplorer::Constants::SELECTTARGET,
//                       globalcontext);
//    mbuild->addAction(cmd, Constants::G_BUILD_RUN);

//    d->m_projectSelectorActionQuick = new QAction(this);
//    d->m_projectSelectorActionQuick->setEnabled(false);
//    d->m_projectSelectorActionQuick->setText(tr("Quick Switch Kit Selector"));
////    connect(d->m_projectSelectorActionQuick, SIGNAL(triggered()), d->m_targetSelector, SLOT(nextOrShow()));//ROOPAK
//    cmd = ActionManager::registerAction(d->m_projectSelectorActionQuick, ProjectExplorer::Constants::SELECTTARGETQUICK, globalcontext);
//    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+T")));

//    connect(ICore::instance(), SIGNAL(saveSettingsRequested()),
//        this, SLOT(savePersistentSettings()));

////    addAutoReleasedObject(new ProjectTreeWidgetFactory);//ROOPAK
////    addAutoReleasedObject(new FolderNavigationWidgetFactory);//ROOPAK
////    addAutoReleasedObject(new DeployConfigurationFactory);//ROOPAK

//    QSettings *s = ICore::settings();
//    const QStringList fileNames =
//            s->value(QLatin1String("ProjectExplorer/RecentProjects/FileNames")).toStringList();
//    const QStringList displayNames =
//            s->value(QLatin1String("ProjectExplorer/RecentProjects/DisplayNames")).toStringList();
//    if (fileNames.size() == displayNames.size()) {
//        for (int i = 0; i < fileNames.size(); ++i) {
//            if (QFileInfo(fileNames.at(i)).isFile())
//                d->m_recentProjects.append(qMakePair(fileNames.at(i), displayNames.at(i)));
//        }
//    }

////    d->m_projectExplorerSettings.buildBeforeDeploy =              //ROOPAK - START
////            s->value(QLatin1String("ProjectExplorer/Settings/BuildBeforeDeploy"), true).toBool();
////    d->m_projectExplorerSettings.deployBeforeRun =
////            s->value(QLatin1String("ProjectExplorer/Settings/DeployBeforeRun"), true).toBool();
////    d->m_projectExplorerSettings.saveBeforeBuild =
////            s->value(QLatin1String("ProjectExplorer/Settings/SaveBeforeBuild"), false).toBool();
////    d->m_projectExplorerSettings.showCompilerOutput =
////            s->value(QLatin1String("ProjectExplorer/Settings/ShowCompilerOutput"), false).toBool();
////    d->m_projectExplorerSettings.showRunOutput =
////            s->value(QLatin1String("ProjectExplorer/Settings/ShowRunOutput"), true).toBool();
////    d->m_projectExplorerSettings.showDebugOutput =
////            s->value(QLatin1String("ProjectExplorer/Settings/ShowDebugOutput"), false).toBool();
////    d->m_projectExplorerSettings.cleanOldAppOutput =
////            s->value(QLatin1String("ProjectExplorer/Settings/CleanOldAppOutput"), false).toBool();
////    d->m_projectExplorerSettings.mergeStdErrAndStdOut =
////            s->value(QLatin1String("ProjectExplorer/Settings/MergeStdErrAndStdOut"), false).toBool();
////    d->m_projectExplorerSettings.wrapAppOutput =
////            s->value(QLatin1String("ProjectExplorer/Settings/WrapAppOutput"), true).toBool();
////    d->m_projectExplorerSettings.useJom =
////            s->value(QLatin1String("ProjectExplorer/Settings/UseJom"), true).toBool();
////    d->m_projectExplorerSettings.autorestoreLastSession =
////            s->value(QLatin1String("ProjectExplorer/Settings/AutoRestoreLastSession"), false).toBool();
////    d->m_projectExplorerSettings.prompToStopRunControl =
////            s->value(QLatin1String("ProjectExplorer/Settings/PromptToStopRunControl"), false).toBool();
////    d->m_projectExplorerSettings.maxAppOutputLines =
////            s->value(QLatin1String("ProjectExplorer/Settings/MaxAppOutputLines"), 100000).toInt();
////    d->m_projectExplorerSettings.environmentId =
////            QUuid(s->value(QLatin1String("ProjectExplorer/Settings/EnvironmentId")).toByteArray());
////    if (d->m_projectExplorerSettings.environmentId.isNull())
////        d->m_projectExplorerSettings.environmentId = QUuid::createUuid(); //ROOPAK - END

////    connect(d->m_sessionManagerAction, SIGNAL(triggered()), this, SLOT(showSessionManager()));//#720 ROOPAK
////    connect(d->m_newAction, SIGNAL(triggered()), this, SLOT(newProject()));
//    connect(d->m_loadAction, SIGNAL(triggered()), this, SLOT(loadAction()));
//    connect(d->m_buildProjectOnlyAction, SIGNAL(triggered()), this, SLOT(buildProjectOnly()));
//    connect(d->m_buildAction, SIGNAL(triggered()), this, SLOT(buildProject()));
//    connect(d->m_buildActionContextMenu, SIGNAL(triggered()), this, SLOT(buildProjectContextMenu()));
////    connect(d->m_buildSessionAction, SIGNAL(triggered()), this, SLOT(buildSession()));//#720 ROOPAK
//    connect(d->m_rebuildProjectOnlyAction, SIGNAL(triggered()), this, SLOT(rebuildProjectOnly()));
//    connect(d->m_rebuildAction, SIGNAL(triggered()), this, SLOT(rebuildProject()));
//    connect(d->m_rebuildActionContextMenu, SIGNAL(triggered()), this, SLOT(rebuildProjectContextMenu()));
////    connect(d->m_rebuildSessionAction, SIGNAL(triggered()), this, SLOT(rebuildSession()));//#720 ROOPAK
//    connect(d->m_deployProjectOnlyAction, SIGNAL(triggered()), this, SLOT(deployProjectOnly()));
//    connect(d->m_deployAction, SIGNAL(triggered()), this, SLOT(deployProject()));
//    connect(d->m_deployActionContextMenu, SIGNAL(triggered()), this, SLOT(deployProjectContextMenu()));
////    connect(d->m_deploySessionAction, SIGNAL(triggered()), this, SLOT(deploySession()));//#720 ROOPAK
//    connect(d->m_cleanProjectOnlyAction, SIGNAL(triggered()), this, SLOT(cleanProjectOnly()));
//    connect(d->m_cleanAction, SIGNAL(triggered()), this, SLOT(cleanProject()));
//    connect(d->m_cleanActionContextMenu, SIGNAL(triggered()), this, SLOT(cleanProjectContextMenu()));
////    connect(d->m_cleanSessionAction, SIGNAL(triggered()), this, SLOT(cleanSession()));//#720 ROOPAK
//    connect(d->m_runAction, SIGNAL(triggered()), this, SLOT(runProject()));
//    connect(d->m_runActionContextMenu, SIGNAL(triggered()), this, SLOT(runProjectContextMenu()));
//    connect(d->m_runWithoutDeployAction, SIGNAL(triggered()), this, SLOT(runProjectWithoutDeploy()));
//    connect(d->m_cancelBuildAction, SIGNAL(triggered()), this, SLOT(cancelBuild()));
////    connect(d->m_unloadAction, SIGNAL(triggered()), this, SLOT(unloadProject()));//#720 ROOPAK
////    connect(d->m_closeAllProjects, SIGNAL(triggered()), this, SLOT(closeAllProjects()));//#720 ROOPAK
//    connect(d->m_addNewFileAction, SIGNAL(triggered()), this, SLOT(addNewFile()));
//    connect(d->m_addExistingFilesAction, SIGNAL(triggered()), this, SLOT(addExistingFiles()));
//    connect(d->m_addExistingDirectoryAction, SIGNAL(triggered()), this, SLOT(addExistingDirectory()));
//    connect(d->m_addNewSubprojectAction, SIGNAL(triggered()), this, SLOT(addNewSubproject()));
//    connect(d->m_removeProjectAction, SIGNAL(triggered()), this, SLOT(removeProject()));
//    connect(d->m_openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
//    connect(d->m_searchOnFileSystem, SIGNAL(triggered()), this, SLOT(searchOnFileSystem()));
//    connect(d->m_showInGraphicalShell, SIGNAL(triggered()), this, SLOT(showInGraphicalShell()));
//    connect(d->m_openTerminalHere, SIGNAL(triggered()), this, SLOT(openTerminalHere()));
//    connect(d->m_removeFileAction, SIGNAL(triggered()), this, SLOT(removeFile()));
//    connect(d->m_deleteFileAction, SIGNAL(triggered()), this, SLOT(deleteFile()));
//    connect(d->m_renameFileAction, SIGNAL(triggered()), this, SLOT(renameFile()));
//    connect(d->m_setStartupProjectAction, SIGNAL(triggered()), this, SLOT(setStartupProject()));

//    connect(this, SIGNAL(updateRunActions()), this, SLOT(slotUpdateRunActions()));
//    connect(this, SIGNAL(settingsChanged()), this, SLOT(updateRunWithoutDeployMenu()));

////    QObject *buildManager = new BuildManager(this, d->m_cancelBuildAction);//ROOPAK - START
////    connect(buildManager, SIGNAL(buildStateChanged(ProjectExplorer::Project*)),
////            this, SLOT(buildStateChanged(ProjectExplorer::Project*)));
////    connect(buildManager, SIGNAL(buildQueueFinished(bool)),
////            this, SLOT(buildQueueFinished(bool)), Qt::QueuedConnection);//ROOPAK - END

//    updateActions();

//    connect(ICore::instance(), SIGNAL(coreAboutToOpen()),
//            this, SLOT(determineSessionToRestoreAtStartup()));
//    connect(ICore::instance(), SIGNAL(coreOpened()), this, SLOT(restoreSession()));

//    updateWelcomePage();

//    VariableManager::registerFileVariables(Constants::VAR_CURRENTPROJECT_PREFIX, tr("Current project's main file"));
//    VariableManager::registerVariable(Constants::VAR_CURRENTPROJECT_BUILDPATH,
//        tr("Full build path of the current project's active build configuration."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTPROJECT_NAME, tr("The current project's name."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTKIT_NAME, tr("The currently active kit's name."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTKIT_FILESYSTEMNAME,
//                         tr("The currently active kit's name in a filesystem friendly version."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTKIT_ID, tr("The currently active kit's id."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTDEVICE_HOSTADDRESS,
//            tr("The host address of the device in the currently active kit."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTDEVICE_SSHPORT,
//            tr("The SSH port of the device in the currently active kit."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTDEVICE_USERNAME,
//            tr("The user name with which to log into the device in the currently active kit."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTDEVICE_PRIVATEKEYFILE,
//            tr("The private key file with which to authenticate when logging into the device "
//               "in the currently active kit."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTBUILD_NAME, tr("The currently active build configuration's name."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTBUILD_TYPE, tr("The currently active build configuration's type."));
//    VariableManager::registerFileVariables(Constants::VAR_CURRENTSESSION_PREFIX, tr("File where current session is saved."));
//    VariableManager::registerVariable(Constants::VAR_CURRENTSESSION_NAME, tr("Name of current session."));

//    connect(VariableManager::instance(), SIGNAL(variableUpdateRequested(QByteArray)),
//            this, SLOT(updateVariable(QByteArray)));

    return true;
}

void ProjectExplorerPlugin::loadAction()
{
    if (debug)
        qDebug() << "ProjectExplorerPlugin::loadAction";


    QString dir = d->m_lastOpenDirectory;

    // for your special convenience, we preselect a pro file if it is
    // the current file
    if (const IDocument *document = EditorManager::currentDocument()) {
        const QString fn = document->filePath();
        const bool isProject = d->m_profileMimeTypes.contains(document->mimeType());
        dir = isProject ? fn : QFileInfo(fn).absolutePath();
    }

    QString filename = QFileDialog::getOpenFileName(Core::ICore::dialogParent(),
                                                    tr("Load Project"), dir,
                                                    d->m_projectFilterString);
    if (filename.isEmpty())
        return;
    QString errorMessage;
//    openProject(filename, &errorMessage);//#720 ROOPAK - START

    if (!errorMessage.isEmpty())
        QMessageBox::critical(ICore::mainWindow(), tr("Failed to open project."), errorMessage);
    updateActions();
}

//void ProjectExplorerPlugin::unloadProject()//#720 ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::unloadProject";

////    if (BuildManager::isBuilding(d->m_currentProject)) {//ROOPAK - START
////        QMessageBox box;
////        QPushButton *closeAnyway = box.addButton(tr("Cancel Build && Unload"), QMessageBox::AcceptRole);
////        QPushButton *cancelClose = box.addButton(tr("Do Not Unload"), QMessageBox::RejectRole);
////        box.setDefaultButton(cancelClose);
////        box.setWindowTitle(tr("Unload Project %1?").arg(d->m_currentProject->displayName()));
////        box.setText(tr("The project %1 is currently being built.").arg(d->m_currentProject->displayName()));
////        box.setInformativeText(tr("Do you want to cancel the build process and unload the project anyway?"));
////        box.exec();
////        if (box.clickedButton() != closeAnyway)
////            return;
////        BuildManager::cancel();
////    }//ROOPAK - END

//    IDocument *document = d->m_currentProject->document();

//    if (!document || document->filePath().isEmpty()) //nothing to save?
//        return;

//    if (!DocumentManager::saveModifiedDocumentSilently(document))
//        return;

//    addToRecentProjects(document->filePath(), d->m_currentProject->displayName());
//    unloadProject(d->m_currentProject);
//}

//void ProjectExplorerPlugin::unloadProject(Project *project)
//{
////    SessionManager::removeProject(project);//#720 ROOPAK
//    updateActions();
//}//#720 ROOPAK - END

//void ProjectExplorerPlugin::closeAllProjects()//#720 ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::closeAllProject";

//    if (!EditorManager::closeAllEditors())
//        return; // Action has been cancelled

////    SessionManager::closeAllProjects();//#720 ROOPAK
//    updateActions();

//#if HAS_WELCOME_PAGE
//    ModeManager::activateMode(Core::Constants::MODE_WELCOME);
//#endif
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::extensionsInitialized()
{
//    d->m_proWindow->extensionsInitialized();//ROOPAK
//    d->m_fileFactories = ProjectFileFactory::createFactories(&d->m_projectFilterString);//ROOPAK - START
//    foreach (ProjectFileFactory *pf, d->m_fileFactories) {
//        d->m_profileMimeTypes += pf->mimeTypes();
//        addAutoReleasedObject(pf);
//    }//ROOPAK - END
//    BuildManager::extensionsInitialized();//ROOPAK

//    DeviceManager::instance()->addDevice(IDevice::Ptr(new DesktopDevice));//ROOPAK
//    DeviceManager::instance()->load();//ROOPAK
//    ToolChainManager::restoreToolChains();//#720 ROOPAK
//    d->m_kitManager->restoreKits();//#720 ROOPAK
}

void ProjectExplorerPlugin::loadCustomWizards()
{
    // Add custom wizards, for which other plugins might have registered
    // class factories
//    static bool firstTime = true;//ROOPAK - START
//    if (firstTime) {
//        firstTime = false;
//        foreach (IWizard *cpw, ProjectExplorer::CustomWizard::createWizards())
//            addAutoReleasedObject(cpw);
//    }//ROOPAK - END
}

void ProjectExplorerPlugin::updateVariable(const QByteArray &variable)
{
//    if (variable == Constants::VAR_CURRENTPROJECT_BUILDPATH) {//#720 ROOPAK - START
//        if (currentProject() /*&& currentProject()->activeTarget() && currentProject()->activeTarget()->activeBuildConfiguration()*/) {//ROOPAK
////            VariableManager::insert(variable,
////                                          currentProject()->activeTarget()->activeBuildConfiguration()->buildDirectory().toUserOutput());//ROOPAK
//        } else {
//            VariableManager::remove(variable);
//        }
//    } else if (variable == Constants::VAR_CURRENTBUILD_TYPE) {
//        if (currentProject() /*&& currentProject()->activeTarget() && currentProject()->activeTarget()->activeBuildConfiguration()*/) {//ROOPAK
////            BuildConfiguration::BuildType type = currentProject()->activeTarget()->activeBuildConfiguration()->buildType();//ROOPAK - START
////            QString typeString;
////            if (type == BuildConfiguration::Debug)
////                typeString = tr("debug");
////            else if (type == BuildConfiguration::Release)
////                typeString = tr("release");
////            else
////                typeString = tr("unknown");
////            VariableManager::insert(variable, typeString);//ROOPAK - END
//        } else {
//            VariableManager::remove(variable);
//        }
//    } else if (variable == Constants::VAR_CURRENTSESSION_NAME) {
////        if (!SessionManager::activeSession().isEmpty())//#720 ROOPAK - START
////            VariableManager::insert(variable, SessionManager::activeSession());
////        else
////            VariableManager::remove(variable);//#720 ROOPAK - END
//    } else if (Core::VariableManager::isFileVariable(
//                   variable, ProjectExplorer::Constants::VAR_CURRENTSESSION_PREFIX)) {
////        if (!SessionManager::activeSession().isEmpty()) {//#720 ROOPAK - START
////            VariableManager::insert(variable, Core::VariableManager::fileVariableValue(variable,
////                 ProjectExplorer::Constants::VAR_CURRENTSESSION_PREFIX,
////                 SessionManager::sessionNameToFileName(SessionManager::activeSession()).toFileInfo()));
////        } else {
////            VariableManager::remove(variable);
////        }//#720 ROOPAK - END
//    } else {
//        QString projectName;
//        QString projectFilePath;
////        Kit *kit = 0;//#720 ROOPAK
//        QString buildConfigurationName;
//        if (Project *project = currentProject()) {
//            projectName = project->displayName();
//            if (IDocument *doc = project->document())
//                projectFilePath = doc->filePath();
////            if (Target *target = project->activeTarget()) {//#720 ROOPAK - START
////                kit = target->kit();
//////                if (BuildConfiguration *buildConfiguration = target->activeBuildConfiguration())//ROOPAK
//////                    buildConfigurationName = buildConfiguration->displayName();//ROOPAK
////            }//#720 ROOPAK - END
//        }
////        ProjectMacroExpander expander(projectFilePath, projectName, kit, buildConfigurationName);//ROOPAK - START
////        QString result;
////        if (expander.resolveProjectMacro(QString::fromUtf8(variable), &result))
////            VariableManager::insert(variable, result);
////        else
////            VariableManager::remove(variable);//ROOPAK - END
//    }//#720 ROOPAK - END
}

void ProjectExplorerPlugin::updateRunWithoutDeployMenu()
{
//    d->m_runWithoutDeployAction->setVisible(d->m_projectExplorerSettings.deployBeforeRun);//ROOPAK
}

ExtensionSystem::IPlugin::ShutdownFlag ProjectExplorerPlugin::aboutToShutdown()
{
//    d->m_proWindow->aboutToShutdown(); // disconnect from session//ROOPAK
//    SessionManager::closeAllProjects();//#720 ROOPAK
    d->m_projectsMode = 0;
    d->m_shuttingDown = true;
    // Attempt to synchronously shutdown all run controls.
    // If that fails, fall back to asynchronous shutdown (Debugger run controls
    // might shutdown asynchronously).
//    if (d->m_outputPane->closeTabs(AppOutputPane::CloseTabNoPrompt /* No prompt any more */))//ROOPAK - START
//        return SynchronousShutdown;//ROOPAK
//    connect(d->m_outputPane, SIGNAL(allRunControlsFinished()),
//            this, SIGNAL(asynchronousShutdownFinished()));//ROOPAK - END
    return AsynchronousShutdown;
}

//void ProjectExplorerPlugin::newProject()//ROOPAK
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::newProject";

//    ICore::showNewItemDialog(tr("New Project", "Title of dialog"),
//                              IWizard::wizardsOfKind(IWizard::ProjectWizard));
//    updateActions();
//}//ROOPAK

//void ProjectExplorerPlugin::showSessionManager()//#720 ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::showSessionManager";

////    if (SessionManager::isDefaultVirgin()) {//#720 ROOPAK - START
////        // do not save new virgin default sessions
////    } else {
////        SessionManager::save();
////    }//#720 ROOPAK - END
////    SessionDialog sessionDialog(ICore::mainWindow());//ROOPAK - START
////    sessionDialog.setAutoLoadSession(d->m_projectExplorerSettings.autorestoreLastSession);
////    sessionDialog.exec();
////    d->m_projectExplorerSettings.autorestoreLastSession = sessionDialog.autoLoadSession();//ROOPAK - END

//    updateActions();

//#if HAS_WELCOME_PAGE
//    IMode *welcomeMode = ModeManager::mode(Core::Constants::MODE_WELCOME);
//    if (ModeManager::currentMode() == welcomeMode)
//        updateWelcomePage();
//#endif
//}//#720 ROOPAK - END

//void ProjectExplorerPlugin::setStartupProject(Project *project)//#720 ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::setStartupProject";

//    if (!project)
//        return;
////    SessionManager::setStartupProject(project);//#720 ROOPAK
//    updateActions();
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::savePersistentSettings()
{
    if (debug)
        qDebug()<<"ProjectExplorerPlugin::savePersistentSettings()";

    if (d->m_shuttingDown)
        return;

//    if (!SessionManager::loadingSession())  {//#720 ROOPAK - START
//        foreach (Project *pro, SessionManager::projects())
//            pro->saveSettings();

//        if (SessionManager::isDefaultVirgin()) {
//            // do not save new virgin default sessions
//        } else {
//            SessionManager::save();
//        }
//    }//#720 ROOPAK - END

    QSettings *s = ICore::settings();
//    s->setValue(QLatin1String("ProjectExplorer/StartupSession"), SessionManager::activeSession());//#720 ROOPAK
    s->remove(QLatin1String("ProjectExplorer/RecentProjects/Files"));

    QStringList fileNames;
    QStringList displayNames;
    QList<QPair<QString, QString> >::const_iterator it, end;
    end = d->m_recentProjects.constEnd();
    for (it = d->m_recentProjects.constBegin(); it != end; ++it) {
        fileNames << (*it).first;
        displayNames << (*it).second;
    }

    s->setValue(QLatin1String("ProjectExplorer/RecentProjects/FileNames"), fileNames);
    s->setValue(QLatin1String("ProjectExplorer/RecentProjects/DisplayNames"), displayNames);

//    s->setValue(QLatin1String("ProjectExplorer/Settings/BuildBeforeDeploy"), d->m_projectExplorerSettings.buildBeforeDeploy);//ROOPAK - START
//    s->setValue(QLatin1String("ProjectExplorer/Settings/DeployBeforeRun"), d->m_projectExplorerSettings.deployBeforeRun);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/SaveBeforeBuild"), d->m_projectExplorerSettings.saveBeforeBuild);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/ShowCompilerOutput"), d->m_projectExplorerSettings.showCompilerOutput);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/ShowRunOutput"), d->m_projectExplorerSettings.showRunOutput);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/ShowDebugOutput"), d->m_projectExplorerSettings.showDebugOutput);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/CleanOldAppOutput"), d->m_projectExplorerSettings.cleanOldAppOutput);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/MergeStdErrAndStdOut"), d->m_projectExplorerSettings.mergeStdErrAndStdOut);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/WrapAppOutput"), d->m_projectExplorerSettings.wrapAppOutput);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/UseJom"), d->m_projectExplorerSettings.useJom);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/AutoRestoreLastSession"), d->m_projectExplorerSettings.autorestoreLastSession);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/PromptToStopRunControl"), d->m_projectExplorerSettings.prompToStopRunControl);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/MaxAppOutputLines"), d->m_projectExplorerSettings.maxAppOutputLines);
//    s->setValue(QLatin1String("ProjectExplorer/Settings/EnvironmentId"), d->m_projectExplorerSettings.environmentId.toByteArray());//ROOPAK - END
}

void ProjectExplorerPlugin::openProjectWelcomePage(const QString &fileName)
{
    QString errorMessage;
//    openProject(fileName, &errorMessage);//#720 ROOPAK
    if (!errorMessage.isEmpty())
        QMessageBox::critical(ICore::mainWindow(), tr("Failed to Open Project"), errorMessage);
}

//Project *ProjectExplorerPlugin::openProject(const QString &fileName, QString *errorString)//#720 ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::openProject";

//    QList<Project *> list = openProjects(QStringList() << fileName, errorString);
//    if (!list.isEmpty()) {
//        addToRecentProjects(fileName, list.first()->displayName());
////        SessionManager::setStartupProject(list.first());//#720 ROOPAK
//        return list.first();
//    }
//    return 0;
//}//#720 ROOPAK - END

//static inline QList<IProjectManager*> allProjectManagers()//#720 ROOPAK - START
//{
//    return ExtensionSystem::PluginManager::getObjects<IProjectManager>();
//}//#720 ROOPAK - END

static void appendError(QString *errorString, const QString &error)
{
    if (!errorString || error.isEmpty())
        return;

    if (!errorString->isEmpty())
        errorString->append(QLatin1Char('\n'));
    errorString->append(error);
}

//QList<Project *> ProjectExplorerPlugin::openProjects(const QStringList &fileNames, QString *errorString)//#720 ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin - opening projects " << fileNames;

////    const QList<IProjectManager*> projectManagers = allProjectManagers();//#720 ROOPAK

//    QList<Project*> openedPro;
//    foreach (const QString &fileName, fileNames) {
//        QTC_ASSERT(!fileName.isEmpty(), continue);

//        QFileInfo fi = QFileInfo(fileName);
//        QString filePath = fileName;
//        if (fi.exists()) // canonicalFilePath will be empty otherwise!
//            filePath = fi.canonicalFilePath();
//        bool found = false;
////        foreach (Project *pi, SessionManager::projects()) {//#720 ROOPAK - END
////            if (filePath == pi->projectFilePath()) {
////                found = true;
////                break;
////            }
////        }//#720 ROOPAK - END
//        if (found) {
//            appendError(errorString, tr("Failed opening project '%1': Project already open.")
//                        .arg(QDir::toNativeSeparators(fileName)));
////            SessionManager::reportProjectLoadingProgress();//#720 ROOPAK
//            continue;
//        }

//        if (const MimeType mt = MimeDatabase::findByFile(QFileInfo(fileName))) {
//            bool foundProjectManager = false;
////            foreach (IProjectManager *manager, projectManagers) {//#720 ROOPAK - START
////                if (manager->mimeType() == mt.type()) {
////                    foundProjectManager = true;
////                    QString tmp;
////                    if (Project *pro = manager->openProject(filePath, &tmp)) {
////                        if (pro->restoreSettings()) {
////                            connect(pro, SIGNAL(fileListChanged()), this, SIGNAL(fileListChanged()));
////                            SessionManager::addProject(pro);
////                            // Make sure we always have a current project / node
//////                            if (!d->m_currentProject && !openedPro.isEmpty())//ROOPAK
//////                                setCurrentNode(pro->rootProjectNode());//ROOPAK
////                            openedPro += pro;
////                        } else {
////                            appendError(errorString, tr("Failed opening project '%1': Settings could not be restored.")
////                                        .arg(QDir::toNativeSeparators(fileName)));
////                            delete pro;
////                        }
////                    }
////                    if (!tmp.isEmpty())
////                        appendError(errorString, tmp);
////                    break;
////                }
////            }//#720 ROOPAK - END
//            if (!foundProjectManager) {
//                appendError(errorString, tr("Failed opening project '%1': No plugin can open project type '%2'.")
//                            .arg(QDir::toNativeSeparators(fileName))
//                            .arg((mt.type())));
//            }
//        } else {
//            appendError(errorString, tr("Failed opening project '%1': Unknown project type.")
//                        .arg(QDir::toNativeSeparators(fileName)));
//        }
////        SessionManager::reportProjectLoadingProgress();//#720 ROOPAK
//    }
//    updateActions();

//    bool switchToProjectsMode = false;
//    foreach (Project *p, openedPro) {
//        if (p->needsConfiguration()) {
//            switchToProjectsMode = true;
//            break;
//        }
//    }

//    if (!openedPro.isEmpty()) {
//        if (switchToProjectsMode)
//            ModeManager::activateMode(ProjectExplorer::Constants::MODE_SESSION);
//        else
//            ModeManager::activateMode(Core::Constants::MODE_EDIT);
//        ModeManager::setFocusToCurrentMode();
//    }

//    return openedPro;
//}//#720 ROOPAK - END

//Project *ProjectExplorerPlugin::currentProject()//#720 ROOPAK - START
//{
//    Project *project = m_instance->d->m_currentProject;
//    if (debug) {
//        if (project)
//            qDebug() << "ProjectExplorerPlugin::currentProject returns " << project->displayName();
//        else
//            qDebug() << "ProjectExplorerPlugin::currentProject returns 0";
//    }
//    return project;
//}//#720 ROOPAK - END

//Node *ProjectExplorerPlugin::currentNode() const//ROOPAk - START
//{
//    return d->m_currentNode;
//}//ROOPAK - END

//void ProjectExplorerPlugin::setCurrentFile(Project *project, const QString &filePath)//#720 ROOPAK - START
//{
//    setCurrent(project, filePath, 0);//ROOPAK
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::setCurrentFile(const QString &filePath)
{
    if (d->m_ignoreDocumentManagerChangedFile)
        return;
//    Project *project = SessionManager::projectForFile(filePath);//#720 ROOPAK
    // If the file is not in any project, stay with the current project
    // e.g. on opening a git diff buffer, git log buffer, we don't change the project
    // I'm not 100% sure this is correct
//    if (!project)
//        project = d->m_currentProject;
//    setCurrent(project, filePath, 0);//ROOPAK
}

//void ProjectExplorerPlugin::setCurrentNode(Node *node)//ROOPAK - START
//{
//    setCurrent(SessionManager::projectForNode(node), QString(), node);
//}//ROOPAK - END

void ProjectExplorerPlugin::updateWelcomePage()
{
#if HAS_WELCOME_PAGE
    d->m_welcomePage->reloadWelcomeScreenData();
#endif
}

void ProjectExplorerPlugin::currentModeChanged(IMode *mode, IMode *oldMode)
{
    if (oldMode && oldMode->id() == "Project"/*ProjectExplorer::Constants::MODE_SESSION*/)//#720 ROOPAK
        ICore::saveSettings();
    if (mode && mode->id() == Core::Constants::MODE_WELCOME)
        updateWelcomePage();
}

void ProjectExplorerPlugin::determineSessionToRestoreAtStartup()
{
    // Process command line arguments first:
//    if (pluginSpec()->arguments().contains(QLatin1String("-lastsession")))//#720 ROOPAK - START
//        d->m_sessionToRestoreAtStartup = SessionManager::lastSession();
//    QStringList arguments = ExtensionSystem::PluginManager::arguments();
//    if (d->m_sessionToRestoreAtStartup.isNull()) {
//        QStringList sessions = SessionManager::sessions();
//        // We have command line arguments, try to find a session in them
//        // Default to no session loading
//        foreach (const QString &arg, arguments) {
//            if (sessions.contains(arg)) {
//                // Session argument
//                d->m_sessionToRestoreAtStartup = arg;
//                break;
//            }
//        }
//    }//#720 ROOPAK - END
    // Handle settings only after command line arguments:
//    if (d->m_sessionToRestoreAtStartup.isNull()//ROOPAK - START
//        && d->m_projectExplorerSettings.autorestoreLastSession)
//        d->m_sessionToRestoreAtStartup = SessionManager::lastSession();//ROOPAK - END

    if (!d->m_sessionToRestoreAtStartup.isNull())
        ModeManager::activateMode(Core::Constants::MODE_EDIT);
}

// Return a list of glob patterns for project files ("*.pro", etc), use first, main pattern only.
static inline QStringList projectFileGlobs()
{
    QStringList result;
//    foreach (const IProjectManager *ipm, ExtensionSystem::PluginManager::getObjects<IProjectManager>()) {//#720 ROOPAK - START
//        if (const MimeType mimeType = MimeDatabase::findByType(ipm->mimeType())) {
//            const QList<MimeGlobPattern> patterns = mimeType.globPatterns();
//            if (!patterns.isEmpty())
//                result.push_back(patterns.front().pattern());
//        }
//    }//#720 ROOPAK - END
    return result;
}

/*!
    This function is connected to the ICore::coreOpened signal.  If
    there was no session explicitly loaded, it creates an empty new
    default session and puts the list of recent projects and sessions
    onto the welcome page.
*/
void ProjectExplorerPlugin::restoreSession()
{
    if (debug)
        qDebug() << "ProjectExplorerPlugin::restoreSession";

    // We have command line arguments, try to find a session in them
    QStringList arguments = ExtensionSystem::PluginManager::arguments();
    if (!d->m_sessionToRestoreAtStartup.isEmpty() && !arguments.isEmpty())
        arguments.removeOne(d->m_sessionToRestoreAtStartup);

    // Massage the argument list.
    // Be smart about directories: If there is a session of that name, load it.
    //   Other than that, look for project files in it. The idea is to achieve
    //   'Do what I mean' functionality when starting Creator in a directory with
    //   the single command line argument '.' and avoid editor warnings about not
    //   being able to open directories.
    // In addition, convert "filename" "+45" or "filename" ":23" into
    //   "filename+45"   and "filename:23".
    if (!arguments.isEmpty()) {
//        const QStringList sessions = SessionManager::sessions();//#720 ROOPAK
        QStringList projectGlobs = projectFileGlobs();
        for (int a = 0; a < arguments.size(); ) {
            const QString &arg = arguments.at(a);
            const QFileInfo fi(arg);
            if (fi.isDir()) {
                const QDir dir(fi.absoluteFilePath());
                // Does the directory name match a session?
                if (d->m_sessionToRestoreAtStartup.isEmpty()
                    /*&& sessions.contains(dir.dirName())*/) {//#720 ROOPAK
                    d->m_sessionToRestoreAtStartup = dir.dirName();
                    arguments.removeAt(a);
                    continue;
                } else {
                    // Are there project files in that directory?
                    const QFileInfoList proFiles
                        = dir.entryInfoList(projectGlobs, QDir::Files);
                    if (!proFiles.isEmpty()) {
                        arguments[a] = proFiles.front().absoluteFilePath();
                        ++a;
                        continue;
                    }
                }
                // Cannot handle: Avoid mime type warning for directory.
                qWarning("Skipping directory '%s' passed on to command line.",
                         qPrintable(QDir::toNativeSeparators(arg)));
                arguments.removeAt(a);
                continue;
            } // Done directories.
            // Converts "filename" "+45" or "filename" ":23" into "filename+45" and "filename:23"
            if (a && (arg.startsWith(QLatin1Char('+')) || arg.startsWith(QLatin1Char(':')))) {
                arguments[a - 1].append(arguments.takeAt(a));
                continue;
            }
            ++a;
        } // for arguments
    } // !arguments.isEmpty()
    // Restore latest session or what was passed on the command line
//    if (!d->m_sessionToRestoreAtStartup.isEmpty())//#720 ROOPAK - START
//        SessionManager::loadSession(d->m_sessionToRestoreAtStartup);//#720 ROOPAK - END

    // update welcome page
    connect(ModeManager::instance(),
            SIGNAL(currentModeChanged(Core::IMode*,Core::IMode*)),
            SLOT(currentModeChanged(Core::IMode*,Core::IMode*)));
#if HAS_WELCOME_PAGE
    connect(d->m_welcomePage, SIGNAL(requestSession(QString)), this, SLOT(loadSession(QString)));
    connect(d->m_welcomePage, SIGNAL(requestProject(QString)), this, SLOT(openProjectWelcomePage(QString)));
#endif
    d->m_arguments = arguments;
    QTimer::singleShot(0, this, SLOT(restoreSession2()));
    updateActions();
}

void ProjectExplorerPlugin::restoreSession2()
{
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    ICore::openFiles(d->m_arguments, ICore::OpenFilesFlags(ICore::CanContainLineNumbers | ICore::SwitchMode));
}

void ProjectExplorerPlugin::loadSession(const QString &session)
{
    if (debug)
        qDebug() << "ProjectExplorerPlugin::loadSession" << session;
//    SessionManager::loadSession(session);//#720 ROOPAK
}


//void ProjectExplorerPlugin::showContextMenu(QWidget *view, const QPoint &globalPos, Node *node)//ROOPAK - START
//{
//    QMenu *contextMenu = 0;

//    if (!node)
//        node = SessionManager::sessionNode();

//    if (node->nodeType() != SessionNodeType) {
//        Project *project = SessionManager::projectForNode(node);
//        setCurrentNode(node);

//        emit aboutToShowContextMenu(project, node);
//        switch (node->nodeType()) {
//        case ProjectNodeType:
//            if (node->parentFolderNode() == SessionManager::sessionNode())
//                contextMenu = d->m_projectMenu;
//            else
//                contextMenu = d->m_subProjectMenu;
//            break;
//        case VirtualFolderNodeType:
//        case FolderNodeType:
//            contextMenu = d->m_folderMenu;
//            break;
//        case FileNodeType:
//            populateOpenWithMenu();
//            contextMenu = d->m_fileMenu;
//            break;
//        default:
//            qWarning("ProjectExplorerPlugin::showContextMenu - Missing handler for node type");
//        }
//    } else { // session item
//        emit aboutToShowContextMenu(0, node);

//        contextMenu = d->m_sessionContextMenu;
//    }

//    updateContextMenuActions();
//    d->m_projectTreeCollapseAllAction->disconnect(SIGNAL(triggered()));
//    connect(d->m_projectTreeCollapseAllAction, SIGNAL(triggered()), view, SLOT(collapseAll()));
//    if (contextMenu && contextMenu->actions().count() > 0)
//        contextMenu->popup(globalPos);
//}//ROOPAk - END

//void ProjectExplorerPlugin::buildStateChanged(Project * pro)//#720 ROOPAK - START
//{
//    if (debug) {
//        qDebug() << "buildStateChanged";
////        qDebug() << pro->projectFilePath() << "isBuilding()" << BuildManager::isBuilding(pro);//ROOPAK
//    }
//    Q_UNUSED(pro)
//    updateActions();
//}//#720 ROOPAK - END

//void ProjectExplorerPlugin::executeRunConfiguration(RunConfiguration *runConfiguration, RunMode runMode)//ROOPAK - START
//{
//    QString errorMessage;
//    if (!runConfiguration->ensureConfigured(&errorMessage)) {
//        showRunErrorMessage(errorMessage);
//        return;
//    }
//    if (IRunControlFactory *runControlFactory = findRunControlFactory(runConfiguration, runMode)) {
//        emit aboutToExecuteProject(runConfiguration->target()->project(), runMode);

//        RunControl *control = runControlFactory->create(runConfiguration, runMode, &errorMessage);
//        if (!control) {
//            showRunErrorMessage(errorMessage);
//            return;
//        }
//        startRunControl(control, runMode);
//    }
//}//ROOPAK - END

void ProjectExplorerPlugin::showRunErrorMessage(const QString &errorMessage)
{
    // Empty, non-null means 'canceled' (custom executable dialog for libraries), whereas
    // empty, null means an error occurred, but message was not set
    if (!errorMessage.isEmpty() || errorMessage.isNull())
        QMessageBox::critical(ICore::mainWindow(), errorMessage.isNull() ? tr("Unknown error") : tr("Could Not Run"), errorMessage);
}

//void ProjectExplorerPlugin::startRunControl(RunControl *runControl, RunMode runMode)//ROOPAK - START
//{
//    d->m_outputPane->createNewOutputWindow(runControl);
//    d->m_outputPane->flash(); // one flash for starting
//    d->m_outputPane->showTabFor(runControl);
//    bool popup = (runMode == NormalRunMode && d->m_projectExplorerSettings.showRunOutput)
//            || ((runMode == DebugRunMode || runMode == DebugRunModeWithBreakOnMain)
//                && d->m_projectExplorerSettings.showDebugOutput);
//    d->m_outputPane->setBehaviorOnOutput(runControl, popup ? AppOutputPane::Popup : AppOutputPane::Flash);
//    connect(runControl, SIGNAL(finished()), this, SLOT(runControlFinished()));
//    runControl->start();
//    emit updateRunActions();
//}//ROOPAK - END

//QList<RunControl *> ProjectExplorerPlugin::runControls() const//#720 ROOPAK - START
//{
////    return d->m_outputPane->runControls();//ROOPAK
//      QList<RunControl *> result;
//      return result;
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::initiateInlineRenaming()
{
    renameFile();
}

void ProjectExplorerPlugin::buildQueueFinished(bool success)
{
    if (debug)
        qDebug() << "buildQueueFinished()" << success;

    updateActions();

    bool ignoreErrors = true;
//    if (!d->m_delayedRunConfiguration.isNull() && success && BuildManager::getErrorTaskCount() > 0) {//ROOPAK - START
//        ignoreErrors = QMessageBox::question(ICore::dialogParent(),
//                                             tr("Ignore All Errors?"),
//                                             tr("Found some build errors in current task.\n"
//                                                "Do you want to ignore them?"),
//                                             QMessageBox::Yes | QMessageBox::No,
//                                             QMessageBox::No) == QMessageBox::Yes;
//    }
//    if (d->m_delayedRunConfiguration.isNull() && d->m_shouldHaveRunConfiguration) {
//        QMessageBox::warning(ICore::dialogParent(),
//                             tr("Run Configuration Removed"),
//                             tr("The configuration that was supposed to run is no longer "
//                                "available."), QMessageBox::Ok);
//    }

//    if (success && ignoreErrors && !d->m_delayedRunConfiguration.isNull()) {
//        executeRunConfiguration(d->m_delayedRunConfiguration.data(), d->m_runMode);
//    } else {
//        if (BuildManager::tasksAvailable())//ROOPAK
//            BuildManager::showTaskWindow();//ROOPAK
//    }
//    d->m_delayedRunConfiguration = 0;//ROOPAK - END
    d->m_shouldHaveRunConfiguration = false;
//    d->m_runMode = NoRunMode;//#720 ROOPAK
}

void ProjectExplorerPlugin::updateExternalFileWarning()
{
    IDocument *document = qobject_cast<IDocument *>(sender());
    if (!document || document->filePath().isEmpty())
        return;
    InfoBar *infoBar = document->infoBar();
    Id externalFileId(EXTERNAL_FILE_WARNING);
    if (!document->isModified()) {
        infoBar->removeInfo(externalFileId);
        return;
    }
//    if (!d->m_currentProject || !infoBar->canInfoBeAdded(externalFileId))//#720 ROOPAK - START
//        return;
//    Utils::FileName fileName = Utils::FileName::fromString(document->filePath());
//    Utils::FileName projectDir = Utils::FileName::fromString(d->m_currentProject->projectDirectory());
//    if (projectDir.isEmpty() || fileName.isChildOf(projectDir))
//        return;
//    // External file. Test if it under the same VCS
//    QString topLevel;
//    if (VcsManager::findVersionControlForDirectory(projectDir.toString(), &topLevel)
//            && fileName.isChildOf(Utils::FileName::fromString(topLevel))) {
//        return;
//    }//#720 ROOPAK - END
    infoBar->addInfo(InfoBarEntry(externalFileId,
                             tr("<b>Warning:</b> This file is outside the project directory."),
                                        InfoBarEntry::GlobalSuppressionEnabled));
}

void ProjectExplorerPlugin::updateContext()
{
    Context oldContext;
    oldContext.add(d->m_lastProjectContext);

    Context newContext;
    /*if (d->m_currentProject) {//#720 ROOPAK - START
        newContext.add(d->m_currentProject->projectContext());
        newContext.add(d->m_currentProject->projectLanguages());

        d->m_lastProjectContext = newContext;
    } else */{                  //#720 ROOPAK - END
        d->m_lastProjectContext = Context();
    }

    ICore::updateAdditionalContexts(oldContext, newContext);
}

//void ProjectExplorerPlugin::setCurrent(Project *project, QString filePath, Node *node)//ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorer - setting path to " << (node ? pathFor(node) : filePath)
//                << " and project to " << (project ? project->displayName() : QLatin1String("0"));

//    if (node)
//        filePath = pathFor(node);
//    else
//        node = SessionManager::nodeForFile(filePath, project);

//    bool projectChanged = false;
//    if (d->m_currentProject != project) {
//        if (d->m_currentProject) {
//            disconnect(d->m_currentProject, SIGNAL(projectContextUpdated()),
//                       this, SLOT(updateContext()));
//            disconnect(d->m_currentProject, SIGNAL(projectLanguagesUpdated()),
//                       this, SLOT(updateContext()));
//        }
//        if (project) {
//            connect(project, SIGNAL(projectContextUpdated()),
//                    this, SLOT(updateContext()));
//            connect(project, SIGNAL(projectLanguagesUpdated()),
//                    this, SLOT(updateContext()));
//        }
//        projectChanged = true;
//    }
//    d->m_currentProject = project;

//    if (!node && EditorManager::currentDocument()) {
//        connect(EditorManager::currentDocument(), SIGNAL(changed()),
//                this, SLOT(updateExternalFileWarning()), Qt::UniqueConnection);
//    }
//    if (projectChanged || d->m_currentNode != node) {
//        d->m_currentNode = node;
//        if (debug)
//            qDebug() << "ProjectExplorer - currentNodeChanged(" << (node ? node->path() : QLatin1String("0")) << ", " << (project ? project->displayName() : QLatin1String("0")) << ')';
//        emit currentNodeChanged(d->m_currentNode, project);
//        updateContextMenuActions();
//    }
//    if (projectChanged) {
//        if (debug)
//            qDebug() << "ProjectExplorer - currentProjectChanged(" << (project ? project->displayName() : QLatin1String("0")) << ')';
//        emit currentProjectChanged(project);
//        updateActions();
//    }

//    d->m_ignoreDocumentManagerChangedFile = true;
//    DocumentManager::setCurrentFile(filePath);
//    updateContext();
//    d->m_ignoreDocumentManagerChangedFile = false;
//}//ROOPAK - END

void ProjectExplorerPlugin::updateActions()
{
    if (debug)
        qDebug() << "ProjectExplorerPlugin::updateActions";

//    Project *project = SessionManager::startupProject();//#720 ROOPAK

    QPair<bool, QString> buildActionState;// = buildSettingsEnabled(/*project*/NULL);//#720 ROOPAK
    QPair<bool, QString> buildActionContextState;// = buildSettingsEnabled(d->m_currentProject);//#720 ROOPAK
    QPair<bool, QString> buildSessionState = buildSettingsEnabledForSession();

    QString projectName = /*project ? project->displayName() :*/ QString();//#720 ROOPAK
    QString projectNameContextMenu ;//= d->m_currentProject ? d->m_currentProject->displayName() : QString();//#720 ROOPAK

//    d->m_unloadAction->setParameter(projectNameContextMenu);//#720 ROOPAK

    // Normal actions
    d->m_buildAction->setParameter(projectName);
    d->m_rebuildAction->setParameter(projectName);
    d->m_cleanAction->setParameter(projectName);

    d->m_buildAction->setEnabled(buildActionState.first);
    d->m_rebuildAction->setEnabled(buildActionState.first);
    d->m_cleanAction->setEnabled(buildActionState.first);

    d->m_buildAction->setToolTip(buildActionState.second);
    d->m_rebuildAction->setToolTip(buildActionState.second);
    d->m_cleanAction->setToolTip(buildActionState.second);

    // Context menu actions
    d->m_setStartupProjectAction->setParameter(projectNameContextMenu);

//    bool hasDependencies = SessionManager::projectOrder(d->m_currentProject).size() > 1;//#720 ROOPAK - START
//    if (hasDependencies) {
//        d->m_buildActionContextMenu->setText(tr("Build Without Dependencies"));
//        d->m_rebuildActionContextMenu->setText(tr("Rebuild Without Dependencies"));
//        d->m_cleanActionContextMenu->setText(tr("Clean Without Dependencies"));
//    } else {
//        d->m_buildActionContextMenu->setText(tr("Build"));
//        d->m_rebuildActionContextMenu->setText(tr("Rebuild"));
//        d->m_cleanActionContextMenu->setText(tr("Clean"));
//    }//#720 ROOPAK - END

    d->m_buildActionContextMenu->setEnabled(buildActionContextState.first);
    d->m_rebuildActionContextMenu->setEnabled(buildActionContextState.first);
    d->m_cleanActionContextMenu->setEnabled(buildActionContextState.first);

    d->m_buildActionContextMenu->setToolTip(buildActionState.second);
    d->m_rebuildActionContextMenu->setToolTip(buildActionState.second);
    d->m_cleanActionContextMenu->setToolTip(buildActionState.second);

    // build project only
    d->m_buildProjectOnlyAction->setEnabled(buildActionState.first);
    d->m_rebuildProjectOnlyAction->setEnabled(buildActionState.first);
    d->m_cleanProjectOnlyAction->setEnabled(buildActionState.first);

    d->m_buildProjectOnlyAction->setToolTip(buildActionState.second);
    d->m_rebuildProjectOnlyAction->setToolTip(buildActionState.second);
    d->m_cleanProjectOnlyAction->setToolTip(buildActionState.second);

    // Session actions
//    d->m_closeAllProjects->setEnabled(SessionManager::hasProjects());//#720 ROOPAK

//    d->m_buildSessionAction->setEnabled(buildSessionState.first);//#720 ROOPAK
//    d->m_rebuildSessionAction->setEnabled(buildSessionState.first);//#720 ROOPAK
//    d->m_cleanSessionAction->setEnabled(buildSessionState.first);//#720 ROOPAK

//    d->m_buildSessionAction->setToolTip(buildSessionState.second);//#720 ROOPAK
//    d->m_rebuildSessionAction->setToolTip(buildSessionState.second);//#720 ROOPAK
//    d->m_cleanSessionAction->setToolTip(buildSessionState.second);//#720 ROOPAK

//    d->m_cancelBuildAction->setEnabled(BuildManager::isBuilding());//ROOPAK

    const bool hasProjects = false;//SessionManager::hasProjects();//#720 ROOPAK - START
    d->m_projectSelectorAction->setEnabled(hasProjects);
    d->m_projectSelectorActionMenu->setEnabled(hasProjects);
    d->m_projectSelectorActionQuick->setEnabled(hasProjects);

    updateDeployActions();
    updateRunWithoutDeployMenu();
}

// NBS TODO check projectOrder()
// what we want here is all the projects pro depends on
//QStringList ProjectExplorerPlugin::allFilesWithDependencies(Project *pro)//#720 ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::allFilesWithDependencies(" << pro->projectFilePath() << ")";

//    QStringList filesToSave;
////    foreach (Project *p, SessionManager::projectOrder(pro)) {//#720 ROOPAK - END
////        FindAllFilesVisitor filesVisitor;//ROOPAK
////        p->rootProjectNode()->accept(&filesVisitor);//ROOPAK
////        filesToSave << filesVisitor.filePaths();//ROOPAK
////    }//#720 ROOPAK - END
//    qSort(filesToSave);
//    return filesToSave;
//}//#720 ROOPAK - END

bool ProjectExplorerPlugin::saveModifiedFiles()
{
    if (debug)
        qDebug() << "ProjectExplorerPlugin::saveModifiedFiles";

    QList<IDocument *> documentsToSave = DocumentManager::modifiedDocuments();
    if (!documentsToSave.isEmpty()) {
//        if (d->m_projectExplorerSettings.saveBeforeBuild) {//ROOPAK - START
//            bool cancelled = false;
//            DocumentManager::saveModifiedDocumentsSilently(documentsToSave, &cancelled);
//            if (cancelled)
//                return false;
//        } else {
//            bool cancelled = false;
//            bool alwaysSave = false;
//            if (!DocumentManager::saveModifiedDocuments(documentsToSave, QString(), &cancelled,
//                                                        tr("Always save files before build"), &alwaysSave)) {
//                if (cancelled)
//                    return false;
//            }

//            if (alwaysSave)
//                d->m_projectExplorerSettings.saveBeforeBuild = true;
//        }//ROOPAK - END
    }
    return true;
}

//NBS handle case where there is no activeBuildConfiguration
// because someone delete all build configurations

//void ProjectExplorerPlugin::deploy(QList<Project *> projects)//#720 ROOPAK - START
//{
//    QList<Id> steps;
////    if (d->m_projectExplorerSettings.buildBeforeDeploy)//ROOPAK
////        steps << Id(Constants::BUILDSTEPS_BUILD);//ROOPAK
//    steps << Id(Constants::BUILDSTEPS_DEPLOY);
//    queue(projects, steps);
//}//#720 ROOPAK - END

QString ProjectExplorerPlugin::displayNameForStepId(Id stepId)
{
//    if (stepId == Constants::BUILDSTEPS_CLEAN)//#720 ROOPAK - START
//        return tr("Clean");
//    if (stepId == Constants::BUILDSTEPS_BUILD)
//        return tr("Build", "Build step");
//    if (stepId == Constants::BUILDSTEPS_DEPLOY)
//        return tr("Deploy");//#720 ROOPAK - END
    return tr("Build", "Build step");
}

//int ProjectExplorerPlugin::queue(QList<Project *> projects, QList<Id> stepIds)//#720 ROOPAK - START
//{
//    if (debug) {
//        QStringList projectNames, stepNames;
//        foreach (const Project *p, projects)
//            projectNames << p->displayName();
//        foreach (const Id id, stepIds)
//            stepNames << id.toString();
//        qDebug() << "Building" << stepNames << "for projects" << projectNames;
//    }

//    if (!saveModifiedFiles())
//        return -1;

////    QList<BuildStepList *> stepLists;//ROOPAK
//    QStringList names;
//    QStringList preambleMessage;

//    foreach (Project *pro, projects)
//        if (pro && pro->needsConfiguration())
//            preambleMessage.append(tr("The project %1 is not configured, skipping it.")
//                                   .arg(pro->displayName()) + QLatin1Char('\n'));
//    foreach (Id id, stepIds) {
//        foreach (Project *pro, projects) {
////            if (!pro || !pro->activeTarget())//#720 ROOPAK - START
////                continue;
////            BuildStepList *bsl = 0;
////            if (id == Constants::BUILDSTEPS_DEPLOY
////                && pro->activeTarget()->activeDeployConfiguration())
////                bsl = pro->activeTarget()->activeDeployConfiguration()->stepList();
////            else if (pro->activeTarget()->activeBuildConfiguration())
////                bsl = pro->activeTarget()->activeBuildConfiguration()->stepList(id);

////            if (!bsl || bsl->isEmpty())
////                continue;
////            stepLists << bsl;//ROOPAK - END
//            names << displayNameForStepId(id);
//        }
//    }

////    if (stepLists.isEmpty())//ROOPAK - START
////        return 0;

////    if (!BuildManager::buildLists(stepLists, names, preambleMessage))
////        return -1;//ROOPAK - END
//    return 0/*stepLists.count()*/;//ROOPAK
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::buildProjectOnly()
{
//    queue(QList<Project *>() << SessionManager::startupProject(), QList<Id>() << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK
}

//void ProjectExplorerPlugin::buildProject(Project *p)//#720 ROOPAK - START
//{
//    queue(SessionManager::projectOrder(p),//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK - END
//}

//void ProjectExplorerPlugin::requestProjectModeUpdate(Project *p)
//{
////    d->m_proWindow->projectUpdated(p);//ROOPAK
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::buildProject()
{
//    queue(SessionManager::projectOrder(SessionManager::startupProject()),//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK - END
}

void ProjectExplorerPlugin::buildProjectContextMenu()
{
//    queue(QList<Project *>() <<  d->m_currentProject,//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK - END
}

//void ProjectExplorerPlugin::buildSession()//#720 ROOPAK - START
//{
//    queue(SessionManager::projectOrder(),//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK - END
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::rebuildProjectOnly()
{
//    queue(QList<Project *>() << SessionManager::startupProject(),//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_CLEAN) << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK - END
}

void ProjectExplorerPlugin::rebuildProject()
{
//    queue(SessionManager::projectOrder(SessionManager::startupProject()),//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_CLEAN) << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK - END
}

void ProjectExplorerPlugin::rebuildProjectContextMenu()
{
//    queue(QList<Project *>() <<  d->m_currentProject,//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_CLEAN) << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK - END
}

//void ProjectExplorerPlugin::rebuildSession()//#720 ROOPAK - START
//{
//    queue(SessionManager::projectOrder(),//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_CLEAN) << Id(Constants::BUILDSTEPS_BUILD));//#720 ROOPAK - END
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::deployProjectOnly()
{
//    deploy(QList<Project *>() << SessionManager::startupProject());//#720 ROOPAK
}

void ProjectExplorerPlugin::deployProject()
{
//    deploy(SessionManager::projectOrder(SessionManager::startupProject()));//#720 ROOPAK
}

void ProjectExplorerPlugin::deployProjectContextMenu()
{
//    deploy(QList<Project *>() << d->m_currentProject);//#720 ROOPAK - START
}

//void ProjectExplorerPlugin::deploySession()//#720 ROOPAK - START
//{
//    deploy(SessionManager::projectOrder());//#720 ROOPAK
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::cleanProjectOnly()
{
//    queue(QList<Project *>() << SessionManager::startupProject(),//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_CLEAN));//#720 ROOPAK - END
}

void ProjectExplorerPlugin::cleanProject()
{
//    queue(SessionManager::projectOrder(SessionManager::startupProject()),//#720 ROOPAK - END
//          QList<Id>() << Id(Constants::BUILDSTEPS_CLEAN));//#720 ROOPAK - END
}

void ProjectExplorerPlugin::cleanProjectContextMenu()
{
//    queue(QList<Project *>() <<  d->m_currentProject,//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_CLEAN));//#720 ROOPAK - END
}

//void ProjectExplorerPlugin::cleanSession()//#720 ROOPAK
//{
//    queue(SessionManager::projectOrder(),//#720 ROOPAK - START
//          QList<Id>() << Id(Constants::BUILDSTEPS_CLEAN));//#720 ROOPAK - END
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::runProject()
{
//    runProject(SessionManager::startupProject(), NormalRunMode);//#720 ROOPAK
}

void ProjectExplorerPlugin::runProjectWithoutDeploy()
{
//    runProject(SessionManager::startupProject(), NormalRunMode, true);//#720 ROOPAK
}

void ProjectExplorerPlugin::runProjectContextMenu()
{
    /*ProjectNode *projectNode = qobject_cast<ProjectNode*>(d->m_currentNode);//ROOPAK - START
    if (projectNode == d->m_currentProject->rootProjectNode() || !projectNode) {
        runProject(d->m_currentProject, NormalRunMode);
    } else */{//ROOPAK - END
        QAction *act = qobject_cast<QAction *>(sender());
        if (!act)
            return;
//        RunConfiguration *rc = act->data().value<RunConfiguration *>();//#720 ROOPAK - START
//        if (!rc)
//            return;
//        runRunConfiguration(rc, NormalRunMode);//#720 ROOPAK - END
    }
}

//bool ProjectExplorerPlugin::hasBuildSettings(Project *pro)//#720 ROOPAK - START
//{
//    foreach (Project *project, SessionManager::projectOrder(pro))//#720 ROOPAK - START
//        if (project
//                && project->activeTarget()//#720 ROOPAK
//                /*&& project->activeTarget()->activeBuildConfiguration()*/)//ROOPAK
//            return true;//#720 ROOPAK - END
//    return false;
//}

//QPair<bool, QString> ProjectExplorerPlugin::buildSettingsEnabled(Project *pro)//#720 ROOPAK - START
//{
//    QPair<bool, QString> result;
//    result.first = true;
//    if (!pro) {
//        result.first = false;
//        result.second = tr("No project loaded.");
//    } /*else if (BuildManager::isBuilding(pro)) {//ROOPAK - START
//        result.first = false;
//        result.second = tr("Currently building the active project.");
//    } */else if (pro->needsConfiguration()) {//ROOPAK - END
//        result.first = false;
//        result.second = tr("The project %1 is not configured.").arg(pro->displayName());
//    } else if (!hasBuildSettings(pro)) {
//        result.first = false;
//        result.second = tr("Project has no build settings.");
//    } else {
////        const QList<Project *> & projects = SessionManager::projectOrder(pro);//#720 ROOPAK - START
////        foreach (Project *project, projects) {
////            if (project
//////                    && project->activeTarget()//#720 ROOPAK
//////                    && project->activeTarget()->activeBuildConfiguration()//ROOPAK
////                    /*&& !project->activeTarget()->activeBuildConfiguration()->isEnabled()*/) {//ROOPAK
////                result.first = false;
////                result.second += tr("Building '%1' is disabled:");// %2<br>")//ROOPAK - START
//////                        .arg(project->displayName(),
//////                             project->activeTarget()->activeBuildConfiguration()->disabledReason());//ROOPAK - END
////            }
////        }//#720 ROOPAK - END
//    }
//    return result;
//}//#720 ROOPAK - END

QPair<bool, QString> ProjectExplorerPlugin::buildSettingsEnabledForSession()
{
    QPair<bool, QString> result;
//    result.first = true;//#720 ROOPAK - START
//    /*if (!SessionManager::hasProjects()) {
//        result.first = false;
//        result.second = tr("No project loaded");
//    } else if (BuildManager::isBuilding()) {//ROOPAK - START
//        result.first = false;
//        result.second = tr("A build is in progress");
//    } else*/ if (!hasBuildSettings(0)) {//ROOPAK - END
//        result.first = false;
//        result.second = tr("Project has no build settings");
//    } else {
////        foreach (Project *project, SessionManager::projectOrder(0)) {//#720 ROOPAK - START
////            if (project
//////                    && project->activeTarget()//#720 ROOPAK
//////                    && project->activeTarget()->activeBuildConfiguration()//ROOPAK
////                    /*&& !project->activeTarget()->activeBuildConfiguration()->isEnabled()*/) {//ROOPAK
////                result.first = false;
////                result.second += tr("Building '%1' is disabled:");// %2")//ROOPAK - START
//////                        .arg(project->displayName(),
//////                             project->activeTarget()->activeBuildConfiguration()->disabledReason());//ROOPAK - END
////                result.second += QLatin1Char('\n');
////            }
////        }//#720 ROOPAK - END
//    }//#720 ROOPAK - END
    return result;
}

bool ProjectExplorerPlugin::coreAboutToClose()
{
//    if (BuildManager::isBuilding()) {//ROOPAK - START
//        QMessageBox box;
//        QPushButton *closeAnyway = box.addButton(tr("Cancel Build && Close"), QMessageBox::AcceptRole);
//        QPushButton *cancelClose = box.addButton(tr("Do Not Close"), QMessageBox::RejectRole);
//        box.setDefaultButton(cancelClose);
//        box.setWindowTitle(tr("Close Qt Creator?"));
//        box.setText(tr("A project is currently being built."));
//        box.setInformativeText(tr("Do you want to cancel the build process and close Qt Creator anyway?"));
//        box.exec();
//        if (box.clickedButton() != closeAnyway)
//            return false;
//    }//ROOPAK - END
//    if (!d->m_outputPane->aboutToClose())//ROOPAK
//        return false;//ROOPAK
    return true;
}

//bool ProjectExplorerPlugin::hasDeploySettings(Project *pro)//#720 ROOPAK - START
//{
//    foreach (Project *project, SessionManager::projectOrder(pro))//#720 ROOPAK - START
//        if (project->activeTarget()
////                && project->activeTarget()->activeDeployConfiguration()//ROOPAK
//                /*&& !project->activeTarget()->activeDeployConfiguration()->stepList()->isEmpty()*/)//ROOPAK
//            return true;//#720 ROOPAK - END
//    return false;
//}//#720 ROOPAK - END

//void ProjectExplorerPlugin::runProject(Project *pro, RunMode mode, const bool forceSkipDeploy)//#720 ROOPAK - START
//{
//    if (!pro)
//        return;

////    if (Target *target = pro->activeTarget())//#720 ROOPAK - START
////        if (RunConfiguration *rc = target->activeRunConfiguration())
////            runRunConfiguration(rc, mode, forceSkipDeploy);//#720 ROOPAK - END
//}//#720 ROOPAK - END

//void ProjectExplorerPlugin::runRunConfiguration(RunConfiguration *rc,             //#720 ROOPAK - START
//                                                RunMode runMode,
//                                                const bool forceSkipDeploy)
//{
//    if (!rc->isEnabled())
//        return;

//    QList<Id> stepIds;
//    if (!forceSkipDeploy && d->m_projectExplorerSettings.deployBeforeRun) {//ROOPAK - START
//        if (d->m_projectExplorerSettings.buildBeforeDeploy)
//            stepIds << Id(Constants::BUILDSTEPS_BUILD);
//        stepIds << Id(Constants::BUILDSTEPS_DEPLOY);
//    }//ROOPAK - END

//    Project *pro = rc->target()->project();
//    int queueCount = queue(SessionManager::projectOrder(pro), stepIds);

//    if (queueCount < 0) // something went wrong
//        return;

//    if (queueCount > 0) {
//        // delay running till after our queued steps were processed
//        d->m_runMode = runMode;
//        d->m_delayedRunConfiguration = rc;
//        d->m_shouldHaveRunConfiguration = true;
//    } else {
//        executeRunConfiguration(rc, runMode);
//    }
//    emit updateRunActions();
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::runControlFinished()
{
    emit updateRunActions();
}

//void ProjectExplorerPlugin::projectAdded(ProjectExplorer::Project *pro)//#720 ROOPAK - START
//{
//    if (d->m_projectsMode)
//        d->m_projectsMode->setEnabled(true);
//    // more specific action en and disabling ?
//    connect(pro, SIGNAL(buildConfigurationEnabledChanged()),
//            this, SLOT(updateActions()));
//}

//void ProjectExplorerPlugin::projectRemoved(ProjectExplorer::Project * pro)
//{
////    if (d->m_projectsMode)//#720 ROOPAK - START
////        d->m_projectsMode->setEnabled(SessionManager::hasProjects());//#720 ROOPAK - END
//    // more specific action en and disabling ?
//    disconnect(pro, SIGNAL(buildConfigurationEnabledChanged()),
//               this, SLOT(updateActions()));
//}

//void ProjectExplorerPlugin::projectDisplayNameChanged(Project *pro)
//{
//    addToRecentProjects(pro->projectFilePath(), pro->displayName());
//    updateActions();
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::startupProjectChanged()
{
//    static QPointer<Project> previousStartupProject = 0;//#720 ROOPAK - START
//    Project *project = SessionManager::startupProject();
//    if (project == previousStartupProject)
//        return;//#720 ROOPAK - END

//    if (previousStartupProject) {
//        disconnect(previousStartupProject, SIGNAL(activeTargetChanged(ProjectExplorer::Target*)),
//                   this, SLOT(activeTargetChanged()));
//    }//#720 ROOPAK - END

//    previousStartupProject = project;//#720 ROOPAK - START

//    if (project) {
//        connect(project, SIGNAL(activeTargetChanged(ProjectExplorer::Target*)),
//                this, SLOT(activeTargetChanged()));
//    }//#720 ROOPAK - END

    activeTargetChanged();
    updateActions();
}

void ProjectExplorerPlugin::activeTargetChanged()
{
//    static QPointer<Target> previousTarget = 0;//#720 ROOPAK - START
//    Target *target = 0;
//    Project *startupProject = SessionManager::startupProject();
//    if (startupProject)
//        target = startupProject->activeTarget();
//    if (target == previousTarget)
//        return;//#720 ROOPAK - END

//    if (previousTarget) {//#720 ROOPAK - END
//        disconnect(previousTarget, SIGNAL(activeRunConfigurationChanged(ProjectExplorer::RunConfiguration*)),
//                   this, SLOT(activeRunConfigurationChanged()));
//    }//#720 ROOPAK - END
//    previousTarget = target;
//    if (target) {//#720 ROOPAK - START
//        connect(target, SIGNAL(activeRunConfigurationChanged(ProjectExplorer::RunConfiguration*)),
//                this, SLOT(activeRunConfigurationChanged()));
//    }

//    activeRunConfigurationChanged();//#720 ROOPAK - END
    updateDeployActions();
}

//void ProjectExplorerPlugin::activeRunConfigurationChanged()//#720 ROOPAK - START
//{
//    static QPointer<RunConfiguration> previousRunConfiguration = 0;
//    RunConfiguration *rc = 0;
//    Project *startupProject = SessionManager::startupProject();
//    if (startupProject && startupProject->activeTarget())
//        rc = startupProject->activeTarget()->activeRunConfiguration();
//    if (rc == previousRunConfiguration)
//        return;
//    if (previousRunConfiguration) {
//        disconnect(previousRunConfiguration, SIGNAL(requestRunActionsUpdate()),
//                   this, SIGNAL(updateRunActions()));
//    }
//    previousRunConfiguration = rc;
//    if (rc) {
//        connect(rc, SIGNAL(requestRunActionsUpdate()),
//                this, SIGNAL(updateRunActions()));
//    }
//    emit updateRunActions();
//}//#720 ROOPAK - END

// NBS TODO implement more than one runner
//IRunControlFactory *ProjectExplorerPlugin::findRunControlFactory(RunConfiguration *config, RunMode mode)//#720 ROOPAK - START
//{
//    const QList<IRunControlFactory *> factories = ExtensionSystem::PluginManager::getObjects<IRunControlFactory>();
//    foreach (IRunControlFactory *f, factories)
//        if (f->canRun(config, mode))
//            return f;
//    return 0;
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::updateDeployActions()
{
//    Project *project = NULL;// SessionManager::startupProject();//#720 ROOPAK - START

//    bool enableDeployActions = false;//project//#720 ROOPAK - START
//            //&& !BuildManager::isBuilding(project)//ROOPAK
////            && hasDeploySettings(project);//#720 ROOPAK - END
//    bool enableDeployActionsContextMenu = d->m_currentProject
////                              && !BuildManager::isBuilding(d->m_currentProject)//ROOPAK
//                              && hasDeploySettings(d->m_currentProject);

////    if (d->m_projectExplorerSettings.buildBeforeDeploy) {//ROOPAK - START
////        if (hasBuildSettings(project)
////                && !buildSettingsEnabled(project).first)
////            enableDeployActions = false;
////        if (hasBuildSettings(d->m_currentProject)
////                && !buildSettingsEnabled(d->m_currentProject).first)
////            enableDeployActionsContextMenu = false;
////    }//ROOPAK - END

//    const QString projectName = project ? project->displayName() : QString();
////    bool hasProjects = SessionManager::hasProjects();//#720 ROOPAK

//    d->m_deployAction->setParameter(projectName);
//    d->m_deployAction->setEnabled(enableDeployActions);

//    d->m_deployActionContextMenu->setEnabled(enableDeployActionsContextMenu);

//    d->m_deployProjectOnlyAction->setEnabled(enableDeployActions);

//    bool enableDeploySessionAction = true;
////    if (d->m_projectExplorerSettings.buildBeforeDeploy) {//ROOPAK - START
////        foreach (Project *project, SessionManager::projectOrder(0)) {
////            if (project
////                    && project->activeTarget()
////                    && project->activeTarget()->activeBuildConfiguration()
////                    && !project->activeTarget()->activeBuildConfiguration()->isEnabled()) {
////                enableDeploySessionAction = false;
////                break;
////            }
////        }
////    }//ROOPAK - END
//    if (/*!hasProjects ||*/ !hasDeploySettings(0) /*|| BuildManager::isBuilding()*/)//ROOPAK
//        enableDeploySessionAction = false;
////    d->m_deploySessionAction->setEnabled(enableDeploySessionAction);//#720 ROOPAK

//    emit updateRunActions();//#720 ROOPAK - END
}

//bool ProjectExplorerPlugin::canRun(Project *project, RunMode runMode)//#720 ROOPAK - START
//{
//    if (!project/* ||
//        !project->activeTarget() ||//#720 ROOPAK
//        !project->activeTarget()->activeRunConfiguration()*/) {
//        return false;
//    }

////    if (d->m_projectExplorerSettings.buildBeforeDeploy//ROOPAK - START
////            && d->m_projectExplorerSettings.deployBeforeRun
////            && hasBuildSettings(project)
////            && !buildSettingsEnabled(project).first)
////        return false;//ROOPAK = END


////    RunConfiguration *activeRC = project->activeTarget()->activeRunConfiguration();//#720 ROOPAK - START

////    bool canRun = findRunControlFactory(activeRC, runMode)
////                  && activeRC->isEnabled();
//    return false/*canRun && !BuildManager::isBuilding()*/;//#720 ROOPAK - END
//}

//QString ProjectExplorerPlugin::cannotRunReason(Project *project, RunMode runMode)
//{
//    if (!project)
//        return tr("No active project.");

//    if (project->needsConfiguration())
//        return tr("The project %1 is not configured.").arg(project->displayName());

////    if (!project->activeTarget())//#720 ROOPAK - START
////        return tr("The project '%1' has no active kit.").arg(project->displayName());//#720 ROOPAK - END

////    if (!project->activeTarget()->activeRunConfiguration())//#720 ROOPAK - START
////        return tr("The kit '%1' for the project '%2' has no active run configuration.")
////                .arg(project->activeTarget()->displayName(), project->displayName());//#720 ROOPAK - END


////    if (d->m_projectExplorerSettings.buildBeforeDeploy//ROOPAK - START
////            && d->m_projectExplorerSettings.deployBeforeRun
////            && hasBuildSettings(project)) {
////        QPair<bool, QString> buildState = buildSettingsEnabled(project);
////        if (!buildState.first)
////            return buildState.second;
////    }//ROOPAk - END


////    RunConfiguration *activeRC = project->activeTarget()->activeRunConfiguration();//#720 ROOPAK - START
////    if (!activeRC->isEnabled())
////        return activeRC->disabledReason();

////    // shouldn't actually be shown to the user...
////    if (!findRunControlFactory(activeRC, runMode))
////        return tr("Cannot run '%1'.").arg(activeRC->displayName());//#720 ROOPAK - END

////    if (BuildManager::isBuilding())//ROOPAK
////        return tr("A build is still in progress.");//ROOPAK
//    return QString();
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::slotUpdateRunActions()
{
//    Project *project = false;//SessionManager::startupProject();//#720 ROOPAK - START//#720 ROOPAK - START
//    const bool state = canRun(project, NormalRunMode);
//    d->m_runAction->setEnabled(state);
//    d->m_runAction->setToolTip(cannotRunReason(project, NormalRunMode));
//    d->m_runWithoutDeployAction->setEnabled(state);//#720 ROOPAK - END
}

void ProjectExplorerPlugin::cancelBuild()
{
    if (debug)
        qDebug() << "ProjectExplorerPlugin::cancelBuild";

//    if (BuildManager::isBuilding())//ROOPAK
//        BuildManager::cancel();//ROOPAK
}

void ProjectExplorerPlugin::addToRecentProjects(const QString &fileName, const QString &displayName)
{
    if (debug)
        qDebug() << "ProjectExplorerPlugin::addToRecentProjects(" << fileName << ")";

    if (fileName.isEmpty())
        return;
    QString prettyFileName(QDir::toNativeSeparators(fileName));

    QList<QPair<QString, QString> >::iterator it;
    for (it = d->m_recentProjects.begin(); it != d->m_recentProjects.end();)
        if ((*it).first == prettyFileName)
            it = d->m_recentProjects.erase(it);
        else
            ++it;

    if (d->m_recentProjects.count() > d->m_maxRecentProjects)
        d->m_recentProjects.removeLast();
    d->m_recentProjects.prepend(qMakePair(prettyFileName, displayName));
    QFileInfo fi(prettyFileName);
    d->m_lastOpenDirectory = fi.absolutePath();
    emit recentProjectsChanged();
}

//void ProjectExplorerPlugin::updateRecentProjectMenu()//#720 ROOPAK - START
//{
//    typedef QList<QPair<QString, QString> >::const_iterator StringPairListConstIterator;
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::updateRecentProjectMenu";

//    ActionContainer *aci =
//        ActionManager::actionContainer(Constants::M_RECENTPROJECTS);
//    QMenu *menu = aci->menu();
//    menu->clear();

//    bool hasRecentProjects = false;
//    //projects (ignore sessions, they used to be in this list)
//    const StringPairListConstIterator end = d->m_recentProjects.constEnd();
//    for (StringPairListConstIterator it = d->m_recentProjects.constBegin(); it != end; ++it) {
//        const QPair<QString, QString> &s = *it;
//        if (s.first.endsWith(QLatin1String(".qws")))
//            continue;
//        QAction *action = menu->addAction(Utils::withTildeHomePath(s.first));
//        action->setData(s.first);
//        connect(action, SIGNAL(triggered()), this, SLOT(openRecentProject()));
//        hasRecentProjects = true;
//    }
//    menu->setEnabled(hasRecentProjects);

//    // add the Clear Menu item
//    if (hasRecentProjects) {
//        menu->addSeparator();
//        QAction *action = menu->addAction(QCoreApplication::translate(
//                                          "Core", Core::Constants::TR_CLEAR_MENU));
//        connect(action, SIGNAL(triggered()), this, SLOT(clearRecentProjects()));
//    }
//    emit recentProjectsChanged();
//}

//void ProjectExplorerPlugin::clearRecentProjects()
//{
//    d->m_recentProjects.clear();
//    updateWelcomePage();
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::openRecentProject()
{
    if (debug)
        qDebug() << "ProjectExplorerPlugin::openRecentProject()";

    QAction *a = qobject_cast<QAction*>(sender());
    if (!a)
        return;
    QString fileName = a->data().toString();
    if (!fileName.isEmpty()) {
        QString errorMessage;
//        openProject(fileName, &errorMessage);//#720 ROOPAK
        if (!errorMessage.isEmpty())
            QMessageBox::critical(ICore::mainWindow(), tr("Failed to open project."), errorMessage);
    }
}

//void ProjectExplorerPlugin::invalidateProject(Project *project)//#720 ROOPAK - START
//{
//    if (debug)
//        qDebug() << "ProjectExplorerPlugin::invalidateProject" << project->displayName();
//    if (d->m_currentProject == project) {
//        //
//        // Workaround for a bug in QItemSelectionModel
//        // - currentChanged etc are not emitted if the
//        // item is removed from the underlying data model
//        //
////        setCurrent(0, QString(), 0);//ROOPAK
//    }

//    disconnect(project, SIGNAL(fileListChanged()), this, SIGNAL(fileListChanged()));
//    updateActions();
//}//#720 ROOPAK - END

void ProjectExplorerPlugin::updateContextMenuActions()
{
    d->m_addExistingFilesAction->setEnabled(false);
    d->m_addExistingDirectoryAction->setEnabled(false);
    d->m_addNewFileAction->setEnabled(false);
    d->m_addNewSubprojectAction->setEnabled(false);
    d->m_removeFileAction->setEnabled(false);
    d->m_deleteFileAction->setEnabled(false);
    d->m_renameFileAction->setEnabled(false);

    d->m_addExistingFilesAction->setVisible(true);
    d->m_addExistingDirectoryAction->setVisible(true);
    d->m_removeFileAction->setVisible(true);
    d->m_deleteFileAction->setVisible(true);
    d->m_runActionContextMenu->setVisible(false);

    d->m_openTerminalHere->setVisible(true);
    d->m_showInGraphicalShell->setVisible(true);
    d->m_searchOnFileSystem->setVisible(true);

    ActionContainer *runMenu = ActionManager::actionContainer(/*Constants::RUNMENUCONTEXTMENU*/"Project.RunMenu");//#720 ROOPAK
    runMenu->menu()->clear();

//    if (d->m_currentNode && d->m_currentNode->projectNode()) {//ROOPAK - START
//        QList<ProjectExplorer::ProjectAction> actions =
//                d->m_currentNode->supportedActions(d->m_currentNode);

//        if (ProjectNode *pn = qobject_cast<ProjectNode *>(d->m_currentNode)) {
//            if (pn == d->m_currentProject->rootProjectNode()) {
//                d->m_runActionContextMenu->setVisible(true);
//            } else {
//                QList<RunConfiguration *> runConfigs = pn->runConfigurationsFor(pn);
//                if (runConfigs.count() == 1) {
//                    d->m_runActionContextMenu->setVisible(true);
//                    d->m_runActionContextMenu->setData(QVariant::fromValue(runConfigs.first()));
//                } else if (runConfigs.count() > 1) {
//                    foreach (RunConfiguration *rc, runConfigs) {
//                        QAction *act = new QAction(runMenu->menu());
//                        act->setData(QVariant::fromValue(rc));
//                        act->setText(tr("Run %1").arg(rc->displayName()));
//                        runMenu->menu()->addAction(act);
//                        connect(act, SIGNAL(triggered()),
//                                this, SLOT(runProjectContextMenu()));
//                    }
//                }
//            }
//        }
//        if (qobject_cast<FolderNode*>(d->m_currentNode)) {
//            // Also handles ProjectNode
//            d->m_addNewFileAction->setEnabled(actions.contains(ProjectExplorer::AddNewFile));
//            d->m_addNewSubprojectAction->setEnabled(d->m_currentNode->nodeType() == ProjectNodeType
//                                                    && actions.contains(ProjectExplorer::AddSubProject));
//            d->m_addExistingFilesAction->setEnabled(actions.contains(ProjectExplorer::AddExistingFile));
//            d->m_addExistingDirectoryAction->setEnabled(actions.contains(ProjectExplorer::AddExistingDirectory));
//            d->m_renameFileAction->setEnabled(actions.contains(ProjectExplorer::Rename));
//        } else if (qobject_cast<FileNode*>(d->m_currentNode)) {
//            // Enable and show remove / delete in magic ways:
//            // If both are disabled show Remove
//            // If both are enabled show both (can't happen atm)
//            // If only removeFile is enabled only show it
//            // If only deleteFile is enable only show it
//            bool enableRemove = actions.contains(ProjectExplorer::RemoveFile);
//            d->m_removeFileAction->setEnabled(enableRemove);
//            bool enableDelete = actions.contains(ProjectExplorer::EraseFile);
//            d->m_deleteFileAction->setEnabled(enableDelete);
//            d->m_deleteFileAction->setVisible(enableDelete);

//            d->m_removeFileAction->setVisible(!enableDelete || enableRemove);
//            d->m_renameFileAction->setEnabled(actions.contains(ProjectExplorer::Rename));
//        }

//        if (actions.contains(ProjectExplorer::HidePathActions)) {
//            d->m_openTerminalHere->setVisible(false);
//            d->m_showInGraphicalShell->setVisible(false);
//            d->m_searchOnFileSystem->setVisible(false);
//        }
//    }//ROOPAK - END
}

//QString pathOrDirectoryFor(Node *node, bool dir)//ROOPAK - END
//{
//    QString path = node->path();
//    QString location;
//    FolderNode *folder = qobject_cast<FolderNode *>(node);
//    if (node->nodeType() == ProjectExplorer::VirtualFolderNodeType && folder) {
//        // Virtual Folder case
//        // If there are files directly below or no subfolders, take the folder path
//        if (!folder->fileNodes().isEmpty() || folder->subFolderNodes().isEmpty()) {
//            location = path;
//        } else {
//            // Otherwise we figure out a commonPath from the subfolders
//            QStringList list;
//            foreach (FolderNode *f, folder->subFolderNodes())
//                list << f->path() + QLatin1Char('/');
//            location = Utils::commonPath(list);
//        }

//        QFileInfo fi(location);
//        while ((!fi.exists() || !fi.isDir())
//               && !fi.isRoot())
//            fi.setFile(fi.absolutePath());
//        location = fi.absoluteFilePath();
//    } else {
//        QFileInfo fi(path);
//        // remove any /suffixes, which e.g. ResourceNode uses
//        // Note this should be removed again by making node->path() a true path again
//        // That requires changes in both the VirtualFolderNode and ResourceNode
//        while (!fi.exists() && !fi.isRoot())
//            fi.setFile(fi.absolutePath());

//        if (dir)
//            location = fi.isDir() ? fi.absoluteFilePath() : fi.absolutePath();
//        else
//            location = fi.absoluteFilePath();
//    }
//    return location;
//}//ROOPAK - END

//QString ProjectExplorerPlugin::pathFor(Node *node)//ROOPAK - START
//{
//    return pathOrDirectoryFor(node, false);
//}

//QString ProjectExplorerPlugin::directoryFor(Node *node)
//{
//    return pathOrDirectoryFor(node, true);
//}//ROOPAK - END

void ProjectExplorerPlugin::addNewFile()
{
//    QTC_ASSERT(d->m_currentNode, return);//ROOPAK - START
//    QString location = directoryFor(d->m_currentNode);

//    QVariantMap map;
//    map.insert(QLatin1String(Constants::PREFERED_PROJECT_NODE), QVariant::fromValue(d->m_currentNode));
//    if (d->m_currentProject) {
//        QList<Id> profileIds;
//        foreach (Target *target, d->m_currentProject->targets())
//            profileIds << target->id();
//        map.insert(QLatin1String(Constants::PROJECT_KIT_IDS), QVariant::fromValue(profileIds));
//    }
//    ICore::showNewItemDialog(tr("New File", "Title of dialog"),
//                               IWizard::wizardsOfKind(IWizard::FileWizard)
//                               + IWizard::wizardsOfKind(IWizard::ClassWizard),
//                               location, map);//ROOPAK - END
}

void ProjectExplorerPlugin::addNewSubproject()
{
//    QTC_ASSERT(d->m_currentNode, return);//ROOPAK - START
//    QString location = directoryFor(d->m_currentNode);

//    if (d->m_currentNode->nodeType() == ProjectNodeType
//            && d->m_currentNode->supportedActions(
//                d->m_currentNode).contains(ProjectExplorer::AddSubProject)) {
//        QVariantMap map;
//        map.insert(QLatin1String(Constants::PREFERED_PROJECT_NODE), QVariant::fromValue(d->m_currentNode));
//        if (d->m_currentProject) {
//            QList<Id> profileIds;
//            foreach (Target *target, d->m_currentProject->targets())
//                profileIds << target->id();
//            map.insert(QLatin1String(Constants::PROJECT_KIT_IDS), QVariant::fromValue(profileIds));
//        }

//        ICore::showNewItemDialog(tr("New Subproject", "Title of dialog"),         //ROOPAK - START
//                              IWizard::wizardsOfKind(IWizard::ProjectWizard),
//                              location, map);
//    }//ROOPAK - END
}

void ProjectExplorerPlugin::addExistingFiles()
{
//    QTC_ASSERT(d->m_currentNode, return);//ROOPAK

    QStringList fileNames = QFileDialog::getOpenFileNames(ICore::mainWindow(),
        tr("Add Existing Files"), /*directoryFor(d->m_currentNode)*/QString());//ROOPAK
    if (fileNames.isEmpty())
        return;
    addExistingFiles(fileNames);
}

void ProjectExplorerPlugin::addExistingDirectory()
{
//    QTC_ASSERT(d->m_currentNode, return);//ROOPAK - START

//    SelectableFilesDialogAddDirectory dialog(directoryFor(d->m_currentNode), QStringList(), Core::ICore::mainWindow());

//    if (dialog.exec() == QDialog::Accepted)
//        addExistingFiles(dialog.selectedFiles());//ROOPAK - END
}

void ProjectExplorerPlugin::addExistingFiles(const QStringList &filePaths)
{
//    FolderNode *folderNode = qobject_cast<FolderNode *>(d->m_currentNode);//ROOPAK
//    addExistingFiles(folderNode, filePaths);//ROOPAK
}

//void ProjectExplorerPlugin::addExistingFiles(FolderNode *folderNode, const QStringList &filePaths)//ROOPAK -END
//{
//    if (!folderNode) // can happen when project is not yet parsed
//        return;

//    const QString dir = directoryFor(folderNode);
//    QStringList fileNames = filePaths;
//    QStringList notAdded;
//    folderNode->addFiles(fileNames, &notAdded);

//    if (!notAdded.isEmpty()) {
//        QString message = tr("Could not add following files to project %1:").arg(folderNode->projectNode()->displayName());
//        message += QLatin1Char('\n');
//        QString files = notAdded.join(QString(QLatin1Char('\n')));
//        QMessageBox::warning(ICore::mainWindow(), tr("Adding Files to Project Failed"),
//                             message + files);
//        foreach (const QString &file, notAdded)
//            fileNames.removeOne(file);
//    }

//    VcsManager::promptToAdd(dir, fileNames);
//}//ROOPAK - END

void ProjectExplorerPlugin::removeProject()
{
//    ProjectNode *subProjectNode = qobject_cast<ProjectNode*>(d->m_currentNode->projectNode());//ROOPAK - START
//    ProjectNode *projectNode = qobject_cast<ProjectNode *>(subProjectNode->parentFolderNode());
//    if (projectNode) {
//        RemoveFileDialog removeFileDialog(subProjectNode->path(), ICore::mainWindow());
//        removeFileDialog.setDeleteFileVisible(false);
//        if (removeFileDialog.exec() == QDialog::Accepted)
//            projectNode->removeSubProjects(QStringList() << subProjectNode->path());
//    }//ROOPAK - END
}

void ProjectExplorerPlugin::openFile()
{
//    QTC_ASSERT(d->m_currentNode, return);//ROOPAK
//    EditorManager::openEditor(d->m_currentNode->path());//ROOPAK
}

void ProjectExplorerPlugin::searchOnFileSystem()
{
//    QTC_ASSERT(d->m_currentNode, return);//ROOPAK
//    TextEditor::FindInFiles::findOnFileSystem(pathFor(d->m_currentNode));//ROOPAK
}

void ProjectExplorerPlugin::showInGraphicalShell()
{
//    QTC_ASSERT(d->m_currentNode, return);//ROOPAK
//    Core::FileUtils::showInGraphicalShell(Core::ICore::mainWindow(),
//                                                    pathFor(d->m_currentNode));//ROOPAK
}

void ProjectExplorerPlugin::openTerminalHere()
{
//    QTC_ASSERT(d->m_currentNode, return);//ROOPAK
//    Core::FileUtils::openTerminal(directoryFor(d->m_currentNode));//ROOPAK
}

void ProjectExplorerPlugin::removeFile()
{
//    QTC_ASSERT(d->m_currentNode && d->m_currentNode->nodeType() == FileNodeType, return);//ROOPAK - START

//    FileNode *fileNode = qobject_cast<FileNode*>(d->m_currentNode);

//    QString filePath = d->m_currentNode->path();
//    RemoveFileDialog removeFileDialog(filePath, ICore::mainWindow());

//    if (removeFileDialog.exec() == QDialog::Accepted) {
//        const bool deleteFile = removeFileDialog.isDeleteFileChecked();

//        // remove from project
//        FolderNode *folderNode = fileNode->parentFolderNode();
//        Q_ASSERT(folderNode);

//        if (!folderNode->removeFiles(QStringList(filePath))) {
//            QMessageBox::warning(ICore::mainWindow(), tr("Removing File Failed"),
//                                 tr("Could not remove file %1 from project %2.").arg(filePath).arg(folderNode->projectNode()->displayName()));
//            return;
//        }

//        DocumentManager::expectFileChange(filePath);
//        Core::FileUtils::removeFile(filePath, deleteFile);
//        DocumentManager::unexpectFileChange(filePath);
//    }//ROOPAK - END
}

void ProjectExplorerPlugin::deleteFile()
{
//    QTC_ASSERT(d->m_currentNode && d->m_currentNode->nodeType() == FileNodeType, return);//ROOPAK - START

//    FileNode *fileNode = qobject_cast<FileNode*>(d->m_currentNode);

//    QString filePath = d->m_currentNode->path();
//    QMessageBox::StandardButton button =
//            QMessageBox::question(ICore::mainWindow(),
//                                  tr("Delete File"),
//                                  tr("Delete %1 from file system?").arg(filePath),
//                                  QMessageBox::Yes | QMessageBox::No);
//    if (button != QMessageBox::Yes)
//        return;

//    FolderNode *folderNode = fileNode->parentFolderNode();
//    QTC_ASSERT(folderNode, return);

//    folderNode->deleteFiles(QStringList(filePath));

//    DocumentManager::expectFileChange(filePath);
//    if (IVersionControl *vc =
//            VcsManager::findVersionControlForDirectory(QFileInfo(filePath).absolutePath())) {
//        vc->vcsDelete(filePath);
//    }
//    QFile file(filePath);
//    if (file.exists()) {
//        if (!file.remove())
//            QMessageBox::warning(ICore::mainWindow(), tr("Deleting File Failed"),
//                                 tr("Could not delete file %1.").arg(filePath));
//    }
//    DocumentManager::unexpectFileChange(filePath);//ROOPAK - END
}

void ProjectExplorerPlugin::renameFile()
{
//    QWidget *focusWidget = QApplication::focusWidget();//ROOPAK - START
//    while (focusWidget) {
//        ProjectTreeWidget *treeWidget = qobject_cast<ProjectTreeWidget*>(focusWidget);
//        if (treeWidget) {
//            treeWidget->editCurrentItem();
//            return;
//        }
//        focusWidget = focusWidget->parentWidget();
//    }//ROOPAK - END
}

//void ProjectExplorerPlugin::renameFile(Node *node, const QString &to)//ROOPAK - START
//{
//    QString orgFilePath = QFileInfo(node->path()).absoluteFilePath();
//    QString dir = QFileInfo(orgFilePath).absolutePath();
//    QString newFilePath = dir + QLatin1Char('/') + to;

//    if (Core::FileUtils::renameFile(orgFilePath, newFilePath)) {
//        // Tell the project plugin about rename
//        FolderNode *folderNode = node->parentFolderNode();
//        if (!folderNode->renameFile(orgFilePath, newFilePath)) {
//            QMessageBox::warning(ICore::mainWindow(), tr("Project Editing Failed"),
//                                 tr("The file %1 was renamed to %2, but the project file %3 could not be automatically changed.")
//                                 .arg(orgFilePath)
//                                 .arg(newFilePath)
//                                 .arg(folderNode->projectNode()->displayName()));
//        } else {
//            setCurrent(SessionManager::projectForFile(newFilePath), newFilePath, 0);
//        }
//    }
//}//ROOPAK - END

void ProjectExplorerPlugin::setStartupProject()
{
//    setStartupProject(d->m_currentProject);//#720 ROOPAK - START
}

//void ProjectExplorerPlugin::populateOpenWithMenu()//#720 ROOPAK - START
//{
////    DocumentManager::populateOpenWithMenu(d->m_openWithMenu, currentNode()->path());//ROOPAK
//}//#720 ROOPAK - END

//void ProjectExplorerPlugin::updateSessionMenu()//#720 ROOPAK - START
//{
//    d->m_sessionMenu->clear();
//    QActionGroup *ag = new QActionGroup(d->m_sessionMenu);
//    connect(ag, SIGNAL(triggered(QAction*)), this, SLOT(setSession(QAction*)));
////    const QString activeSession = SessionManager::activeSession();//#720 ROOPAK - START
////    foreach (const QString &session, SessionManager::sessions()) {
////        QAction *act = ag->addAction(session);
////        act->setCheckable(true);
////        if (session == activeSession)
////            act->setChecked(true);
////    }//#720 ROOPAK - END
//    d->m_sessionMenu->addActions(ag->actions());
//    d->m_sessionMenu->setEnabled(true);
//}

//void ProjectExplorerPlugin::setSession(QAction *action)
//{
//    QString session = action->text();
////    if (session != SessionManager::activeSession())//#720 ROOPAK - START
////        SessionManager::loadSession(session);//#720 ROOPAK - END
//}//#720 ROOPAK - END

//void ProjectExplorerPlugin::setProjectExplorerSettings(const ProjectExplorerSettings &pes)//ROOPAK - START
//{
//    QTC_ASSERT(m_instance->d->m_projectExplorerSettings.environmentId == pes.environmentId, return);

//    if (m_instance->d->m_projectExplorerSettings == pes)
//        return;
//    m_instance->d->m_projectExplorerSettings = pes;
//    emit m_instance->settingsChanged();
//}

//ProjectExplorerSettings ProjectExplorerPlugin::projectExplorerSettings()
//{
//    return m_instance->d->m_projectExplorerSettings;
//}//ROOPAK - END

QStringList ProjectExplorerPlugin::projectFilePatterns()
{
    QStringList patterns;
//    foreach (const IProjectManager *pm, allProjectManagers())//#720 ROOPAK - START
//        if (const MimeType mt = MimeDatabase::findByType(pm->mimeType()))
//            foreach (const MimeGlobPattern &gp, mt.globPatterns())
//                patterns.append(gp.pattern());//#720 ROOPAK - END
    return patterns;
}

void ProjectExplorerPlugin::openOpenProjectDialog()
{
    const QString path = DocumentManager::useProjectsDirectory() ? DocumentManager::projectsDirectory() : QString();
    const QStringList files = DocumentManager::getOpenFileNames(d->m_projectFilterString, path);
    if (!files.isEmpty())
        ICore::openFiles(files, ICore::SwitchMode);
}

QList<QPair<QString, QString> > ProjectExplorerPlugin::recentProjects()
{
    return d->m_recentProjects;
}

Q_EXPORT_PLUGIN(ProjectExplorerPlugin)

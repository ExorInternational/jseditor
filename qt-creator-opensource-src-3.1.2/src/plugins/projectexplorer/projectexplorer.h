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

#ifndef PROJECTEXPLORER_H
#define PROJECTEXPLORER_H

#include "projectexplorer_export.h"
//#include "projectexplorerconstants.h"//#720 ROOPAK//#720 ROOPAK

#include <extensionsystem/iplugin.h>

#include <QPair>

QT_BEGIN_NAMESPACE
class QPoint;
class QMenu;
class QAction;
QT_END_NAMESPACE

namespace Core {
class IMode;
class Id;
}

namespace ProjectExplorer {
//class RunControl;
//class RunConfiguration;//#720 ROOPAK
//class IRunControlFactory;
//class Project;//#720 ROOPAK
//class Node;//ROOPAK
//class BuildConfiguration;
//class FolderNode;//ROOPAK
//class TaskHub;//#720 ROOPAK

namespace Internal { /*class ProjectExplorerSettings;*/ }//ROOPAK

struct ProjectExplorerPluginPrivate;

class PROJECTEXPLORER_EXPORT ProjectExplorerPlugin
    : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "ProjectExplorer.json")

public:
    ProjectExplorerPlugin();
    ~ProjectExplorerPlugin();

    static ProjectExplorerPlugin *instance();

//    Project *openProject(const QString &fileName, QString *error);//#720 ROOPAK - START
//    QList<Project *> openProjects(const QStringList &fileNames, QString *error);//#720 ROOPAK - END
    Q_SLOT void openProjectWelcomePage(const QString &fileName);
//    void unloadProject(Project *project);//#720 ROOPAK

//    static Project *currentProject();//#720 ROOPAK
//    Node *currentNode() const;//ROOPAK

//    void setCurrentFile(Project *project, const QString &file);//#720 ROOPAK
//    void setCurrentNode(Node *node);//ROOPAK

    bool saveModifiedFiles();

//    void showContextMenu(QWidget *view, const QPoint &globalPos, Node *node);//ROOPAK

    //PluginInterface
    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

//    static void setProjectExplorerSettings(const Internal::ProjectExplorerSettings &pes);//ROOPAK
//    static Internal::ProjectExplorerSettings projectExplorerSettings();//ROOPAK

//    void startRunControl(RunControl *runControl, RunMode runMode);//#720 ROOPAK
    static void showRunErrorMessage(const QString &errorMessage);

    // internal public for FlatModel
//    void renameFile(Node *node, const QString &to);//ROOPAK
    static QStringList projectFilePatterns();
    bool coreAboutToClose();
    QList<QPair<QString, QString> > recentProjects();

//    bool canRun(Project *pro, RunMode runMode);//#720 ROOPAK - START
//    QString cannotRunReason(Project *project, RunMode runMode);
//    void runProject(Project *pro, RunMode, const bool forceSkipDeploy = false);//#720 ROOPAK - START
//    void runRunConfiguration(ProjectExplorer::RunConfiguration *rc, RunMode runMode,//#720 ROOPAK
//                             const bool forceSkipDeploy = false);//#720 ROOPAK

//    void addExistingFiles(ProjectExplorer::FolderNode *projectNode, const QStringList &filePaths);//ROOPAK
    void addExistingFiles(const QStringList &filePaths);

//    void buildProject(ProjectExplorer::Project *p);//#720 ROOPAK - START
    /// Normally there's no need to call this function.
    /// This function needs to be called, only if the pages that support a project changed.
//    void requestProjectModeUpdate(ProjectExplorer::Project *p);//#720 ROOPAK - START

//    QList<RunControl *> runControls() const;//#720 ROOPAK

    void initiateInlineRenaming();

    static QString displayNameForStepId(Core::Id stepId);

//    static QString directoryFor(Node *node);//ROOPAK
//    static QString pathFor(Node *node);//ROOPAK - END

signals:
//    void runControlStarted(ProjectExplorer::RunControl *rc);//#720 ROOPAK
//    void runControlFinished(ProjectExplorer::RunControl *rc);//#720 ROOPAK
//    void aboutToShowContextMenu(ProjectExplorer::Project *project,
//                                ProjectExplorer::Node *node);//ROOPAK

    // Is emitted when a project has been added/removed,
    // or the file list of a specific project has changed.
    void fileListChanged();

//    void currentProjectChanged(ProjectExplorer::Project *project);//#720 ROOPAK - START
//    void currentNodeChanged(ProjectExplorer::Node *node, ProjectExplorer::Project *project);//ROOPAK
//    void aboutToExecuteProject(ProjectExplorer::Project *project, RunMode runMode);//#720 ROOPAK - START
    void recentProjectsChanged();

    void settingsChanged();

    void updateRunActions();

public slots:
    void openOpenProjectDialog();

private slots:
//    void buildStateChanged(ProjectExplorer::Project * pro);//#720 ROOPAK
    void buildQueueFinished(bool success);
    void buildProjectOnly();
    void buildProject();
    void buildProjectContextMenu();
//    void buildSession();//#720 ROOPAK
    void rebuildProjectOnly();
    void rebuildProject();
    void rebuildProjectContextMenu();
//    void rebuildSession();//#720 ROOPAK
    void deployProjectOnly();
    void deployProject();
    void deployProjectContextMenu();
//    void deploySession();//#720 ROOPAK
    void cleanProjectOnly();
    void cleanProject();
    void cleanProjectContextMenu();
//    void cleanSession();//#720 ROOPAK
    void cancelBuild();
    void loadAction();
//    void unloadProject();//#720 ROOPAK
//    void closeAllProjects();//#720 ROOPAK
//    void newProject();//ROOPAK
//    void showSessionManager();//#720 ROOPAK
//    void populateOpenWithMenu();//#720 ROOPAK
//    void updateSessionMenu();//#720 ROOPAK - START
//    void setSession(QAction *action);//#720 ROOPAK - END

    void determineSessionToRestoreAtStartup();
    void restoreSession();
    void restoreSession2();
    void loadSession(const QString &session);
    void runProject();
    void runProjectWithoutDeploy();
    void runProjectContextMenu();
    void savePersistentSettings();

    void addNewFile();
    void addExistingFiles();
    void addExistingDirectory();
    void addNewSubproject();
    void removeProject();
    void openFile();
    void searchOnFileSystem();
    void showInGraphicalShell();
    void removeFile();
    void deleteFile();
    void renameFile();
    void setStartupProject();
//    void setStartupProject(ProjectExplorer::Project *project);//#720 ROOPAK

//    void updateRecentProjectMenu();//#720 ROOPAK
//    void clearRecentProjects();//#720 ROOPAK
    void openRecentProject();
    void openTerminalHere();

//    void invalidateProject(ProjectExplorer::Project *project);//#720 ROOPAK

    void setCurrentFile(const QString &filePath);

    void runControlFinished();

//    void projectAdded(ProjectExplorer::Project *pro);//#720 ROOPAK - START
//    void projectRemoved(ProjectExplorer::Project *pro);
//    void projectDisplayNameChanged(ProjectExplorer::Project *pro);//#720 ROOPAK - END
    void startupProjectChanged(); // Calls updateRunAction
    void activeTargetChanged();
//    void activeRunConfigurationChanged();//#720 ROOPAK

    void updateDeployActions();
    void slotUpdateRunActions();

    void currentModeChanged(Core::IMode *mode, Core::IMode *oldMode);
    void updateActions();
    void loadCustomWizards();
    void updateVariable(const QByteArray &variable);
    void updateRunWithoutDeployMenu();

    void updateWelcomePage();
    void updateExternalFileWarning();

    void updateContext();

#ifdef WITH_TESTS
    void testAnsiFilterOutputParser_data();
    void testAnsiFilterOutputParser();

    void testGccOutputParsers_data();
    void testGccOutputParsers();

    void testCustomOutputParsers_data();
    void testCustomOutputParsers();

    void testClangOutputParser_data();
    void testClangOutputParser();

    void testLinuxIccOutputParsers_data();
    void testLinuxIccOutputParsers();

    void testGnuMakeParserParsing_data();
    void testGnuMakeParserParsing();
    void testGnuMakeParserTaskMangling_data();
    void testGnuMakeParserTaskMangling();

    void testXcodebuildParserParsing_data();
    void testXcodebuildParserParsing();

    void testMsvcOutputParsers_data();
    void testMsvcOutputParsers();

    void testGccAbiGuessing_data();
    void testGccAbiGuessing();

    void testAbiOfBinary_data();
    void testAbiOfBinary();
    void testFlavorForOs();
    void testAbiFromTargetTriplet_data();
    void testAbiFromTargetTriplet();

    void testDeviceManager();

    void testCustomWizardPreprocessor_data();
    void testCustomWizardPreprocessor();
#endif

private:
//    void deploy(QList<Project *>);//#720 ROOPAK - START
//    int queue(QList<Project *>, QList<Core::Id> stepIds);//#720 ROOPAK - END
    void updateContextMenuActions();
    bool parseArguments(const QStringList &arguments, QString *error);
//    void executeRunConfiguration(RunConfiguration *, RunMode mode);//#720 ROOPAK
//    bool hasBuildSettings(Project *pro);//#720 ROOPAK
    QPair<bool, QString> buildSettingsEnabledForSession();
//    QPair<bool, QString> buildSettingsEnabled(Project *pro);//#720 ROOPAK
//    bool hasDeploySettings(Project *pro);//#720 ROOPAK - START

//    void setCurrent(Project *project, QString filePath, Node *node);//ROOPAK

//    QStringList allFilesWithDependencies(Project *pro);//#720 ROOPAK
//    IRunControlFactory *findRunControlFactory(RunConfiguration *config, RunMode mode);//#720 ROOPAK

    void addToRecentProjects(const QString &fileName, const QString &displayName);

    static ProjectExplorerPlugin *m_instance;
    ProjectExplorerPluginPrivate *d;
};

} // namespace ProjectExplorer

#endif // PROJECTEXPLORER_H

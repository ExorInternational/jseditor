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

#include "qmljsmodelmanager.h"
#include "qmljstoolsconstants.h"
#include "qmljssemanticinfo.h"
//#include "qmljsbundleprovider.h"//#720 ROOPAK

#include <coreplugin/icore.h>
#include <coreplugin/messagemanager.h>
#include <coreplugin/progressmanager/progressmanager.h>
//#include <cpptools/cppmodelmanagerinterface.h>//#720 ROOPAK
#include <extensionsystem/pluginmanager.h>
//#include <projectexplorer/buildconfiguration.h>//ROOPAK
//#include <projectexplorer/project.h>//#720 ROOPAK
//#include <projectexplorer/projectexplorer.h>//#720 ROOPAK
//#include <projectexplorer/session.h>//#720 ROOPAK
//#include <projectexplorer/target.h>//#720 ROOPAK
#include <qmljs/qmljsbind.h>
#include <qmljs/qmljsfindexportedcpptypes.h>
#include <qmljs/qmljsplugindumper.h>
//#include <qtsupport/qmldumptool.h>//#720 ROOPAK
//#include <qtsupport/qtkitinformation.h>//#720 ROOPAK
//#include <qtsupport/qtsupportconstants.h>//#720 ROOPAK
#include <texteditor/basetextdocument.h>
#include <utils/function.h>
#include <utils/hostosinfo.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <utils/runextensions.h>
#include <QTextDocument>
#include <QTextStream>
#include <QTimer>
#include <QRegExp>
#include <QtAlgorithms>

#include <QDebug>

//#720 ADDED BY ROOPAK - START
#include <coreplugin/mimedatabase.h>
//#720 ROOPAK - END

using namespace Core;
using namespace QmlJS;
using namespace QmlJSTools;
using namespace QmlJSTools::Internal;


//ModelManagerInterface::ProjectInfo QmlJSTools::defaultProjectInfoForProject(//#720 ROOPAK - START
//        ProjectExplorer::Project *project)
//{
//    ModelManagerInterface::ProjectInfo projectInfo(project);
////    ProjectExplorer::Target *activeTarget = 0;//#720 ROOPAK
//    if (project) {
//        QList<MimeGlobPattern> globs;
//        foreach (const MimeType &mimeType, MimeDatabase::mimeTypes())
//            if (mimeType.type() == QLatin1String(Constants::QML_MIMETYPE)
//                    || mimeType.subClassesOf().contains(QLatin1String(Constants::QML_MIMETYPE)))
//                globs << mimeType.globPatterns();
//        if (globs.isEmpty()) {
//            globs.append(MimeGlobPattern(QLatin1String("*.qbs")));
//            globs.append(MimeGlobPattern(QLatin1String("*.qml")));
//            globs.append(MimeGlobPattern(QLatin1String("*.qmltypes")));
//            globs.append(MimeGlobPattern(QLatin1String("*.qmlproject")));
//        }
////        foreach (const QString &filePath//#720 ROOPAK - START
////                 , project->files(ProjectExplorer::Project::ExcludeGeneratedFiles))
////            foreach (const MimeGlobPattern &glob, globs)
////                if (glob.matches(filePath))
////                    projectInfo.sourceFiles << filePath;//#720 ROOPAK - END
////        activeTarget = project->activeTarget();//#720 ROOPAK
//    }
////    ProjectExplorer::Kit *activeKit = /*activeTarget ? activeTarget->kit() :*///#720 ROOPAK
////                                           ProjectExplorer::KitManager::defaultKit();
////    QtSupport::BaseQtVersion *qtVersion = QtSupport::QtKitInformation::qtVersion(activeKit);//#720 ROOPAK

//    bool preferDebugDump = false;
//    bool setPreferDump = false;
//    projectInfo.tryQmlDump = false;

////    if (activeTarget) {//ROOPAK - START
////        if (ProjectExplorer::BuildConfiguration *bc = activeTarget->activeBuildConfiguration()) {
////            preferDebugDump = bc->buildType() == ProjectExplorer::BuildConfiguration::Debug;
////            setPreferDump = true;
////        }
////    }//ROOPAk - END
////    if (!setPreferDump && qtVersion)//#720 ROOPAK
////        preferDebugDump = (qtVersion->defaultBuildConfig() & QtSupport::BaseQtVersion::DebugBuild);
////    if (qtVersion && qtVersion->isValid()) {
////        projectInfo.tryQmlDump = project && (
////                    qtVersion->type() == QLatin1String(QtSupport::Constants::DESKTOPQT)
////                    || qtVersion->type() == QLatin1String(QtSupport::Constants::SIMULATORQT));
////        projectInfo.qtQmlPath = qtVersion->qmakeProperty("QT_INSTALL_QML");
////        projectInfo.qtImportsPath = qtVersion->qmakeProperty("QT_INSTALL_IMPORTS");
////        projectInfo.qtVersionString = qtVersion->qtVersionString();
////    }//#720 ROOPAK - END

//    if (projectInfo.tryQmlDump) {
////        ProjectExplorer::ToolChain *toolChain =                                       //#720 ROOPAK - START
////                ProjectExplorer::ToolChainKitInformation::toolChain(activeKit);
////        QtSupport::QmlDumpTool::pathAndEnvironment(project, qtVersion,
////                                                   toolChain,
////                                                   preferDebugDump, &projectInfo.qmlDumpPath,
////                                                   &projectInfo.qmlDumpEnvironment);
////        projectInfo.qmlDumpHasRelocatableFlag = qtVersion->hasQmlDumpWithRelocatableFlag();//#720 ROOPAK - END
//    } else {
//        projectInfo.qmlDumpPath.clear();
//        projectInfo.qmlDumpEnvironment.clear();
//        projectInfo.qmlDumpHasRelocatableFlag = true;
//    }
//    setupProjectInfoQmlBundles(projectInfo);
//    return projectInfo;
//}//#720 ROOPAK - END

void QmlJSTools::setupProjectInfoQmlBundles(ModelManagerInterface::ProjectInfo &projectInfo)
{
//    ProjectExplorer::Target *activeTarget = 0;//#720 ROOPAK - START
//    if (projectInfo.project)
//        activeTarget = projectInfo.project->activeTarget();
//    ProjectExplorer::Kit *activeKit = activeTarget
//            ? activeTarget->kit() : ProjectExplorer::KitManager::defaultKit();//#720 ROOPAK - END
    QHash<QString, QString> replacements;
    replacements.insert(QLatin1String("$(QT_INSTALL_IMPORTS)"), projectInfo.qtImportsPath);
    replacements.insert(QLatin1String("$(QT_INSTALL_QML)"), projectInfo.qtQmlPath);

//    QList<IBundleProvider *> bundleProviders =//#720 ROOPAK - START
//            ExtensionSystem::PluginManager::getObjects<IBundleProvider>();//#720 ROOPAK - END

//    foreach (IBundleProvider *bp, bundleProviders) {//#720 ROOPAK - START
//        if (bp)
//            bp->mergeBundlesForKit(activeKit, projectInfo.activeBundle, replacements);
//    }//#720 ROOPAK - END
    projectInfo.extendedBundle = projectInfo.activeBundle;

//    if (projectInfo.project) {//#720 ROOPAK - START
//        QSet<ProjectExplorer::Kit *> currentKits;//#720 ROOPAK - START
////        foreach (const ProjectExplorer::Target *t, projectInfo.project->targets())//#720 ROOPAK - START
////            if (t->kit())
////                currentKits.insert(t->kit())
////        currentKits.remove(activeKit);;//#720 ROOPAK - END
//        foreach (ProjectExplorer::Kit *kit, currentKits) {
//            foreach (IBundleProvider *bp, bundleProviders)
//                if (bp)
//                    bp->mergeBundlesForKit(kit, projectInfo.extendedBundle, replacements);
//        }//#720 ROOPAK - END
//    }//#720 ROOPAK - END
}

QHash<QString,QmlJS::Language::Enum> ModelManager::languageForSuffix() const
{
    QHash<QString,QmlJS::Language::Enum> res = ModelManagerInterface::languageForSuffix();

    if (ICore::instance()) {
        MimeType jsSourceTy = MimeDatabase::findByType(QLatin1String(Constants::JS_MIMETYPE));
        foreach (const QString &suffix, jsSourceTy.suffixes())
            res[suffix] = Language::JavaScript;
        MimeType qmlSourceTy = MimeDatabase::findByType(QLatin1String(Constants::QML_MIMETYPE));
        foreach (const QString &suffix, qmlSourceTy.suffixes())
            res[suffix] = Language::Qml;
        MimeType qbsSourceTy = MimeDatabase::findByType(QLatin1String(Constants::QBS_MIMETYPE));
        foreach (const QString &suffix, qbsSourceTy.suffixes())
            res[suffix] = Language::QmlQbs;
        MimeType qmlProjectSourceTy = MimeDatabase::findByType(QLatin1String(Constants::QMLPROJECT_MIMETYPE));
        foreach (const QString &suffix, qmlProjectSourceTy.suffixes())
            res[suffix] = Language::QmlProject;
        MimeType jsonSourceTy = MimeDatabase::findByType(QLatin1String(Constants::JSON_MIMETYPE));
        foreach (const QString &suffix, jsonSourceTy.suffixes())
            res[suffix] = Language::Json;
    }
    return res;
}

ModelManager::ModelManager(QObject *parent):
        ModelManagerInterface(parent)
{
    qRegisterMetaType<QmlJSTools::SemanticInfo>("QmlJSTools::SemanticInfo");
    loadDefaultQmlTypeDescriptions();
}

ModelManager::~ModelManager()
{
}

void ModelManager::delayedInitialization()
{
//    CppTools::CppModelManagerInterface *cppModelManager =//#720 ROOPAK - START
//            CppTools::CppModelManagerInterface::instance();
//    if (cppModelManager) {
//        // It's important to have a direct connection here so we can prevent
//        // the source and AST of the cpp document being cleaned away.
//        connect(cppModelManager, SIGNAL(documentUpdated(CPlusPlus::Document::Ptr)),
//                this, SLOT(maybeQueueCppQmlTypeUpdate(CPlusPlus::Document::Ptr)), Qt::DirectConnection);
//    }//#720 ROOPAK - END

//    connect(ProjectExplorer::SessionManager::instance(), SIGNAL(projectRemoved(ProjectExplorer::Project*)),//#720 ROOPAK - START
//            this, SLOT(removeProjectInfo(ProjectExplorer::Project*)));//#720 ROOPAK - END
}

void ModelManager::loadDefaultQmlTypeDescriptions()
{
    if (ICore::instance()) {
        loadQmlTypeDescriptionsInternal(ICore::resourcePath());
        loadQmlTypeDescriptionsInternal(ICore::userResourcePath());
    }
}

void ModelManager::writeMessageInternal(const QString &msg) const
{
    MessageManager::write(msg, MessageManager::Flash);
}

ModelManagerInterface::WorkingCopy ModelManager::workingCopyInternal() const
{
    WorkingCopy workingCopy;
    DocumentModel *documentModel = EditorManager::documentModel();
    foreach (IDocument *document, documentModel->openedDocuments()) {
        const QString key = document->filePath();
        if (TextEditor::BaseTextDocument *textDocument = qobject_cast<TextEditor::BaseTextDocument *>(document)) {
            // TODO the language should be a property on the document, not the editor
            if (documentModel->editorsForDocument(document).first()->context().contains(/*ProjectExplorer::Constants::LANG_QMLJS*/"QMLJS"))//#720 ROOPAK
                workingCopy.insert(key, textDocument->plainText(), textDocument->document()->revision());
        }
    }

    return workingCopy;
}

ModelManagerInterface::ProjectInfo ModelManager::defaultProjectInfo() const
{
//    ProjectExplorer::Project *activeProject = ProjectExplorer::SessionManager::startupProject();//#720 ROOPAK - START
//    if (!activeProject)
        return ModelManagerInterface::ProjectInfo();

//    return projectInfo(activeProject);//#720 ROOPAK - END
}

// Check whether fileMimeType is the same or extends knownMimeType
bool ModelManager::matchesMimeType(const MimeType &fileMimeType, const MimeType &knownMimeType)
{
    const QStringList knownTypeNames = QStringList(knownMimeType.type()) + knownMimeType.aliases();

    foreach (const QString &knownTypeName, knownTypeNames)
        if (fileMimeType.matchesType(knownTypeName))
            return true;

    // recursion to parent types of fileMimeType
    foreach (const QString &parentMimeType, fileMimeType.subClassesOf())
        if (matchesMimeType(MimeDatabase::findByType(parentMimeType), knownMimeType))
            return true;

    return false;
}

void ModelManager::addTaskInternal(QFuture<void> result, const QString &msg, const char *taskId) const
{
    ProgressManager::addTask(result, msg, taskId);
}


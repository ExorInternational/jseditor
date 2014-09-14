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

#include "cpptoolsconstants.h"
#include "cpptoolsplugin.h"
//#include "cppfilesettingspage.h"//#720 ROOPAK
//#include "cppcodemodelsettingspage.h"//#720 ROOPAK
//#include "cppcodestylesettingspage.h"//#720 ROOPAK
//#include "cppclassesfilter.h"//#720 ROOPAK
//#include "cppfunctionsfilter.h"//#720 ROOPAK
//#include "cppcurrentdocumentfilter.h"//#720 ROOPAK
//#include "cppmodelmanager.h"//#720 ROOPAK
//#include "cpplocatorfilter.h"//#720 ROOPAK
//#include "symbolsfindfilter.h"//#720 ROOPAK
//#include "cpptoolssettings.h"//#720 ROOPAK
//#include "cpptoolsreuse.h"//#720 ROOPAK
//#include "cppprojectfile.h"//#720 ROOPAK
//#include "cpplocatordata.h"//#720 ROOPAK

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/documentmanager.h>
#include <coreplugin/icore.h>
#include <coreplugin/vcsmanager.h>
#include <cppeditor/cppeditorconstants.h>

#include <utils/fileutils.h>
#include <utils/hostosinfo.h>
#include <utils/qtcassert.h>

#include <QtPlugin>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QMenu>
#include <QAction>

//#720 ADDED BY ROOPAK - START
#include <coreplugin/editormanager/editormanager.h>
#include <projectexplorer/project.h>
//#include "cppcodemodelsettings.h"//#720 ROOPAK
//#720 ROOPAK - END

using namespace Core;
//using namespace CPlusPlus;//#720 ROOPAK

namespace CppTools {
namespace Internal {

enum { debug = 0 };

static CppToolsPlugin *m_instance = 0;
static QHash<QString, QString> m_headerSourceMapping;

CppToolsPlugin::CppToolsPlugin()
//    : m_fileSettings(new CppFileSettings)//#720 ROOPAK
//    , m_codeModelSettings(new CppCodeModelSettings)//#720 ROOPAK
{
    m_instance = this;
}

CppToolsPlugin::~CppToolsPlugin()
{
    m_instance = 0;
//    delete CppModelManager::instance();//#720 ROOPAK
}

CppToolsPlugin *CppToolsPlugin::instance()
{
    return m_instance;
}

void CppToolsPlugin::clearHeaderSourceCache()
{
    m_headerSourceMapping.clear();
}

const QStringList &CppToolsPlugin::headerSearchPaths()
{
    return QStringList();//m_instance->m_fileSettings->headerSearchPaths;//#720 ROOPAK
}

const QStringList &CppToolsPlugin::sourceSearchPaths()
{
    QStringList ret;//#720 ROOPAK
    return ret;//m_instance->m_fileSettings->sourceSearchPaths;//#720 ROOPAK
}

const QStringList &CppToolsPlugin::headerPrefixes()
{
    QStringList ret;//#720 ROOPAK
    return ret;//m_instance->m_fileSettings->headerPrefixes;//#720 ROOPAK
}

const QStringList &CppToolsPlugin::sourcePrefixes()
{
    QStringList ret;//#720 ROOPAK
    return ret;//m_instance->m_fileSettings->sourcePrefixes;//#720 ROOPAK
}


bool CppToolsPlugin::initialize(const QStringList &arguments, QString *error)
{
    Q_UNUSED(arguments)
    Q_UNUSED(error)

//    m_settings = new CppToolsSettings(this); // force registration of cpp tools settings//#720 ROOPAK

    // Objects
//    CppModelManager *modelManager = CppModelManager::instance();//#720 ROOPAK - START
//    connect(VcsManager::instance(), SIGNAL(repositoryChanged(QString)),
//            modelManager, SLOT(updateModifiedSourceFiles()));
//    connect(DocumentManager::instance(), SIGNAL(filesChangedInternally(QStringList)),
//            modelManager, SLOT(updateSourceFiles(QStringList)));//#720 ROOPAK - END

//    CppLocatorData *locatorData = new CppLocatorData(modelManager);//#720 ROOPAK
//    addAutoReleasedObject(locatorData);//#720 ROOPAK
//    addAutoReleasedObject(new CppLocatorFilter(locatorData));//#720 ROOPAK
//    addAutoReleasedObject(new CppClassesFilter(locatorData));//#720 ROOPAK
//    addAutoReleasedObject(new CppFunctionsFilter(locatorData));//#720 ROOPAK
//    addAutoReleasedObject(new CppCurrentDocumentFilter(modelManager));//#720 ROOPAK
//    addAutoReleasedObject(new CppFileSettingsPage(m_fileSettings));//#720 ROOPAK
//    addAutoReleasedObject(new CppCodeModelSettingsPage(m_codeModelSettings));//#720 ROOPAK
//    addAutoReleasedObject(new SymbolsFindFilter(modelManager));//#720 ROOPAK
//    addAutoReleasedObject(new CppCodeStyleSettingsPage);//#720 ROOPAK

    // Menus
    ActionContainer *mtools = ActionManager::actionContainer(Core::Constants::M_TOOLS);
    ActionContainer *mcpptools = ActionManager::createMenu(CppTools::Constants::M_TOOLS_CPP);
    QMenu *menu = mcpptools->menu();
    menu->setTitle(tr("&C++"));
    menu->setEnabled(true);
    mtools->addMenu(mcpptools);

    // Actions
    Context context(CppEditor::Constants::C_CPPEDITOR);

    QAction *switchAction = new QAction(tr("Switch Header/Source"), this);
    Command *command = ActionManager::registerAction(switchAction, Constants::SWITCH_HEADER_SOURCE, context, true);
    command->setDefaultKeySequence(QKeySequence(Qt::Key_F4));
    mcpptools->addAction(command);
    connect(switchAction, SIGNAL(triggered()), this, SLOT(switchHeaderSource()));

    QAction *openInNextSplitAction = new QAction(tr("Open Corresponding Header/Source in Next Split"), this);
    command = ActionManager::registerAction(openInNextSplitAction, Constants::OPEN_HEADER_SOURCE_IN_NEXT_SPLIT, context, true);
    command->setDefaultKeySequence(QKeySequence(Utils::HostOsInfo::isMacHost()
                                                ? tr("Meta+E, F4")
                                                : tr("Ctrl+E, F4")));
    mcpptools->addAction(command);
    connect(openInNextSplitAction, SIGNAL(triggered()), this, SLOT(switchHeaderSourceInNextSplit()));

    return true;
}

void CppToolsPlugin::extensionsInitialized()
{
    // The Cpp editor plugin, which is loaded later on, registers the Cpp mime types,
    // so, apply settings here
//    m_fileSettings->fromSettings(ICore::settings());//#720 ROOPAK - START
//    if (!m_fileSettings->applySuffixesToMimeDB())
//        qWarning("Unable to apply cpp suffixes to mime database (cpp mime types not found).\n");//#720 ROOPAK - END
//    m_codeModelSettings->fromSettings(ICore::settings());//#720 ROOPAK
}

ExtensionSystem::IPlugin::ShutdownFlag CppToolsPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

//QSharedPointer<CppCodeModelSettings> CppToolsPlugin::codeModelSettings() const//#720 ROOPAK - START
//{
//    return m_codeModelSettings;
//}//#720 ROOPAK - END

void CppToolsPlugin::switchHeaderSource()
{
//    QString otherFile = correspondingHeaderOrSource(//#720 ROOPAK - START
//                EditorManager::currentDocument()->filePath());
//    if (!otherFile.isEmpty())
//        EditorManager::openEditor(otherFile);//#720 ROOPAK - END
}

void CppToolsPlugin::switchHeaderSourceInNextSplit()
{
//    QString otherFile = correspondingHeaderOrSource(//#720 ROOPAK - START
//                EditorManager::currentDocument()->filePath());
//    if (!otherFile.isEmpty())
//        EditorManager::openEditor(otherFile, Id(), EditorManager::OpenInOtherSplit);//#720 ROOPAK - END
}

static QStringList findFilesInProject(const QString &name,
                                   const ProjectExplorer::Project *project)
{
    if (debug)
        qDebug() << Q_FUNC_INFO << name << project;

    if (!project)
        return QStringList();

    QString pattern = QString(1, QLatin1Char('/'));
    pattern += name;
    const QStringList projectFiles = project->files(ProjectExplorer::Project::AllFiles);
    const QStringList::const_iterator pcend = projectFiles.constEnd();
    QStringList candidateList;
    for (QStringList::const_iterator it = projectFiles.constBegin(); it != pcend; ++it) {
        if (it->endsWith(pattern))
            candidateList.append(*it);
    }
    return candidateList;
}

// Return the suffixes that should be checked when trying to find a
// source belonging to a header and vice versa
//static QStringList matchingCandidateSuffixes(ProjectFile::Kind kind)//#720 ROOPAK - START
//{
//    switch (kind) {
//     // Note that C/C++ headers are undistinguishable
//    case ProjectFile::CHeader:
//    case ProjectFile::CXXHeader:
//    case ProjectFile::ObjCHeader:
//    case ProjectFile::ObjCXXHeader:
//        return MimeDatabase::findByType(QLatin1String(Constants::C_SOURCE_MIMETYPE)).suffixes()
//                + MimeDatabase::findByType(QLatin1String(Constants::CPP_SOURCE_MIMETYPE)).suffixes()
//                + MimeDatabase::findByType(QLatin1String(Constants::OBJECTIVE_C_SOURCE_MIMETYPE)).suffixes()
//                + MimeDatabase::findByType(QLatin1String(Constants::OBJECTIVE_CPP_SOURCE_MIMETYPE)).suffixes();
//    case ProjectFile::CSource:
//    case ProjectFile::ObjCSource:
//        return MimeDatabase::findByType(QLatin1String(Constants::C_HEADER_MIMETYPE)).suffixes();
//    case ProjectFile::CXXSource:
//    case ProjectFile::ObjCXXSource:
//    case ProjectFile::CudaSource:
//    case ProjectFile::OpenCLSource:
//        return MimeDatabase::findByType(QLatin1String(Constants::CPP_HEADER_MIMETYPE)).suffixes();
//    default:
//        return QStringList();
//    }
//}//#720 ROOPAK - END

static QStringList baseNameWithAllSuffixes(const QString &baseName, const QStringList &suffixes)
{
    QStringList result;
    const QChar dot = QLatin1Char('.');
    foreach (const QString &suffix, suffixes) {
        QString fileName = baseName;
        fileName += dot;
        fileName += suffix;
        result += fileName;
    }
    return result;
}

static QStringList baseNamesWithAllPrefixes(const QStringList &baseNames, bool isHeader)
{
    QStringList result;
    const QStringList &sourcePrefixes = m_instance->sourcePrefixes();
    const QStringList &headerPrefixes = m_instance->headerPrefixes();

    foreach (const QString &name, baseNames) {
        foreach (const QString &prefix, isHeader ? headerPrefixes : sourcePrefixes) {
            if (name.startsWith(prefix)) {
                QString nameWithoutPrefix = name.mid(prefix.size());
                result += nameWithoutPrefix;
                foreach (const QString &prefix, isHeader ? sourcePrefixes : headerPrefixes)
                    result += prefix + nameWithoutPrefix;
            }
        }
        foreach (const QString &prefix, isHeader ? sourcePrefixes : headerPrefixes)
            result += prefix + name;

    }
    return result;
}

static QStringList baseDirWithAllDirectories(const QDir &baseDir, const QStringList &directories)
{
    QStringList result;
    foreach (const QString &dir, directories)
        result << QDir::cleanPath(baseDir.absoluteFilePath(dir));
    return result;
}

static int commonStringLength(const QString &s1, const QString &s2)
{
    int length = qMin(s1.length(), s2.length());
    for (int i = 0; i < length; ++i)
        if (s1[i] != s2[i])
            return i;
    return length;
}

static QString correspondingHeaderOrSourceInProject(const QFileInfo &fileInfo,
                                                    const QStringList &candidateFileNames,
                                                    const ProjectExplorer::Project *project)
{
    QString bestFileName;
    int compareValue = 0;
    const QString filePath = fileInfo.filePath();
    foreach (const QString &candidateFileName, candidateFileNames) {
        const QStringList projectFiles = findFilesInProject(candidateFileName, project);
        // Find the file having the most common path with fileName
        foreach (const QString &projectFile, projectFiles) {
            int value = commonStringLength(filePath, projectFile);
            if (value > compareValue) {
                compareValue = value;
                bestFileName = projectFile;
            }
        }
    }
    if (!bestFileName.isEmpty()) {
        const QFileInfo candidateFi(bestFileName);
        QTC_ASSERT(candidateFi.isFile(), return QString());
        m_headerSourceMapping[fileInfo.absoluteFilePath()] = candidateFi.absoluteFilePath();
        m_headerSourceMapping[candidateFi.absoluteFilePath()] = fileInfo.absoluteFilePath();
        return candidateFi.absoluteFilePath();
    }

    return QString();
}

} // namespace Internal

QString correspondingHeaderOrSource(const QString &fileName, bool *wasHeader)
{
    using namespace Internal;

    const QFileInfo fi(fileName);
//    ProjectFile::Kind kind = ProjectFile::classify(fileName);//#720 ROOPAK - START
//    const bool isHeader = ProjectFile::isHeader(kind);
//    if (wasHeader)
//        *wasHeader = isHeader;
//    if (m_headerSourceMapping.contains(fi.absoluteFilePath()))
//        return m_headerSourceMapping.value(fi.absoluteFilePath());

//    if (debug)
//        qDebug() << Q_FUNC_INFO << fileName <<  kind;

//    if (kind == ProjectFile::Unclassified)
//        return QString();

//    const QString baseName = fi.completeBaseName();
//    const QString privateHeaderSuffix = QLatin1String("_p");
//    const QStringList suffixes = matchingCandidateSuffixes(kind);

//    QStringList candidateFileNames = baseNameWithAllSuffixes(baseName, suffixes);
//    if (isHeader) {
//        if (baseName.endsWith(privateHeaderSuffix)) {
//            QString sourceBaseName = baseName;
//            sourceBaseName.truncate(sourceBaseName.size() - privateHeaderSuffix.size());
//            candidateFileNames += baseNameWithAllSuffixes(sourceBaseName, suffixes);
//        }
//    } else {
//        QString privateHeaderBaseName = baseName;
//        privateHeaderBaseName.append(privateHeaderSuffix);
//        candidateFileNames += baseNameWithAllSuffixes(privateHeaderBaseName, suffixes);
//    }

//    const QDir absoluteDir = fi.absoluteDir();
//    QStringList candidateDirs(absoluteDir.absolutePath());
//    // If directory is not root, try matching against its siblings
//    const QStringList searchPaths = isHeader ? m_instance->sourceSearchPaths()
//                                             : m_instance->headerSearchPaths();
//    candidateDirs += baseDirWithAllDirectories(absoluteDir, searchPaths);

//    candidateFileNames += baseNamesWithAllPrefixes(candidateFileNames, isHeader);//#720 ROOPAK

    // Try to find a file in the same or sibling directories first
//    foreach (const QString &candidateDir, candidateDirs) {
//        foreach (const QString &candidateFileName, candidateFileNames) {
//            const QString candidateFilePath = candidateDir + QLatin1Char('/') + candidateFileName;
//            const QString normalized = Utils::FileUtils::normalizePathName(candidateFilePath);
//            const QFileInfo candidateFi(normalized);
//            if (candidateFi.isFile()) {
//                m_headerSourceMapping[fi.absoluteFilePath()] = candidateFi.absoluteFilePath();
//                if (!isHeader || !baseName.endsWith(privateHeaderSuffix))
//                    m_headerSourceMapping[candidateFi.absoluteFilePath()] = fi.absoluteFilePath();
//                return candidateFi.absoluteFilePath();
//            }
//        }
//    }//#720 ROOPAK - END

    // Find files in the current project
    ProjectExplorer::Project *currentProject = ProjectExplorer::ProjectExplorerPlugin::currentProject();
    if (currentProject) {
//        const QString path = correspondingHeaderOrSourceInProject(fi, candidateFileNames,//#720 ROOPAK - START
//                                                                  currentProject);
//        if (!path.isEmpty())
//            return path;//#720 ROOPAK - END
    }

    // Find files in other projects
//    CppModelManager *modelManager = CppModelManager::instance();//#720 ROOPAK - START
//    QList<CppModelManagerInterface::ProjectInfo> projectInfos = modelManager->projectInfos();
//    foreach (const CppModelManagerInterface::ProjectInfo &projectInfo, projectInfos) {
//        const ProjectExplorer::Project *project = projectInfo.project().data();
//        if (project == currentProject)
//            continue; // We have already checked the current project.

//        const QString path = correspondingHeaderOrSourceInProject(fi, candidateFileNames, project);
//        if (!path.isEmpty())
//            return path;
//    }//#720 ROOPAK - END

    return QString();
}

} // namespace CppTools

Q_EXPORT_PLUGIN(CppTools::Internal::CppToolsPlugin)

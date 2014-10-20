#include "jseditormenuitems.h"

//#720 ROOPAK - START
#include <jseditortools/coreplugin/idocument.h>
#include <jseditortools/coreplugin/idocumentfactory.h>
#include <jseditortools/coreplugin/editormanager/ieditorfactory.h>
#include <jseditortools/coreplugin/mimedatabase.h>
#include <jseditortools/coreplugin/modemanager.h>
#include <jseditortools/coreplugin/coreconstants.h>
#include <jseditortools/coreplugin/editormanager/editormanager.h>
#include <jseditortools/coreplugin/editormanager/ieditor.h>
#include <jseditortools/extensionsystem/pluginmanager.h>
#include <jseditortools/coreplugin/actionmanager/command.h>
#include <jseditortools/coreplugin/actionmanager/actionmanager.h>
#include <jseditortools/coreplugin/actionmanager/actioncontainer_p.h>

#include <QFileDialog>

using namespace JsEditorTools;
using namespace Core;
using namespace ExtensionSystem;

JSEditorMenuItems::JSEditorMenuItems(QObject *parent) :
    QObject(parent)
{
    m_pFileMenuActions = NULL;
    createActionGroups();
}

void JSEditorMenuItems::newFileInEditor()
{
    QString fileName = QFileDialog::getSaveFileName(NULL, QString(QLatin1String("New File")),
                                QString(QLatin1String("%1/Untitled.js")).arg(QDir::homePath()),
                                QString(QLatin1String("Javascript Files(*.js)")) );

    if(!fileName.isEmpty()) {
        QFile fileNew(QDir::toNativeSeparators(fileName));
        fileNew.open(QIODevice::WriteOnly);

        QStringList filesList;
        filesList.append(fileNew.fileName());
        openFiles(filesList, ICore::SwitchMode);
    }//#720 ROOPAK - END
}
void JSEditorMenuItems::openFileInEditor()
{
     openFiles(EditorManager::getOpenFileNames(), ICore::SwitchMode);
}

static QList<IDocumentFactory*> getNonEditorDocumentFactories()
{
    const QList<IDocumentFactory*> allFileFactories =
        ExtensionSystem::PluginManager::getObjects<IDocumentFactory>();
    QList<IDocumentFactory*> nonEditorFileFactories;
    foreach (IDocumentFactory *factory, allFileFactories) {
        if (!qobject_cast<IEditorFactory *>(factory))
            nonEditorFileFactories.append(factory);
    }
    return nonEditorFileFactories;
}
static IDocumentFactory *findDocumentFactory(const QList<IDocumentFactory*> &fileFactories,
                                     const QFileInfo &fi)
{
    if (const MimeType mt = MimeDatabase::findByFile(fi)) {
        const QString type = mt.type();
        foreach (IDocumentFactory *factory, fileFactories) {
            if (factory->mimeTypes().contains(type))
                return factory;
        }
    }
    return 0;
}

IDocument *JSEditorMenuItems::openFiles(const QStringList &fileNames, ICore::OpenFilesFlags flags)
{
    QList<IDocumentFactory*> nonEditorFileFactories = getNonEditorDocumentFactories();
    IDocument *res = 0;

    foreach (const QString &fileName, fileNames) {
        const QFileInfo fi(fileName);
        const QString absoluteFilePath = fi.absoluteFilePath();
        if (IDocumentFactory *documentFactory = findDocumentFactory(nonEditorFileFactories, fi)) {
            IDocument *document = documentFactory->open(absoluteFilePath);
            if (!document) {
                if (flags & ICore::StopOnLoadFail)
                    return res;
            } else {
                if (!res)
                    res = document;
                if (flags & ICore::SwitchMode)
                    ModeManager::activateMode(Id(Core::Constants::MODE_EDIT));
            }
        } else {
            QFlags<EditorManager::OpenEditorFlag> emFlags;
            if (flags & ICore::CanContainLineNumbers)
                emFlags |=  EditorManager::CanContainLineNumber;
            IEditor *editor = EditorManager::openEditor(absoluteFilePath, Id(), emFlags);
            if (!editor) {
                if (flags & ICore::StopOnLoadFail)
                    return res;
            } else if (!res) {
                res = editor->document();
            }
        }
    }
    return res;
}

void JSEditorMenuItems::createActionGroups()
{
    if(m_pFileMenuActions == NULL) {
        m_pFileMenuActions = new QActionGroup(this);

        Context globalContext(Constants::C_GLOBAL);

        ActionContainer *filemenu = ActionManager::createMenu(Constants::M_FILE);
        filemenu->appendGroup(Constants::G_FILE_NEW);
        filemenu->appendGroup(Constants::G_FILE_OPEN);

        ActionContainer *mfile = ActionManager::actionContainer(Constants::M_FILE);

        //New Action
        QIcon icon = QIcon::fromTheme(QLatin1String("document-new"), QIcon(QLatin1String(Constants::ICON_NEWFILE)));
        QAction *newAction = new QAction(icon, tr("&New File"), this);//#720 ROOPAK - START
        Command *cmd = ActionManager::registerAction(newAction, Constants::NEW, globalContext);
        cmd->setDefaultKeySequence(QKeySequence::New);
//        mfile->addAction(cmd, Constants::G_FILE_NEW);
        connect(newAction, SIGNAL(triggered()), this, SLOT(newFileInEditor()));
        m_pFileMenuActions->addAction(newAction);

        // Open Action
        icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(QLatin1String(Constants::ICON_OPENFILE)));
        QAction *openAction = new QAction(icon, tr("&Open File or Project..."), this);
        cmd = ActionManager::registerAction(openAction, Constants::OPEN, globalContext);
        cmd->setDefaultKeySequence(QKeySequence::Open);
//        mfile->addAction(cmd, Constants::G_FILE_OPEN);
        connect(openAction, SIGNAL(triggered()), this, SLOT(openFileInEditor()));
        m_pFileMenuActions->addAction(openAction);

        // Save Action
        icon = QIcon::fromTheme(QLatin1String("document-save"), QIcon(QLatin1String(Constants::ICON_SAVEFILE)));
        QAction *tmpaction = new QAction(icon, tr("&Save"), this);
        tmpaction->setEnabled(false);
        cmd = ActionManager::registerAction(tmpaction, Constants::SAVE, globalContext);
        cmd->setDefaultKeySequence(QKeySequence::Save);
        cmd->setAttribute(Command::CA_UpdateText);
        cmd->setDescription(tr("Save"));
//        mfile->addAction(cmd, Constants::G_FILE_SAVE);
//        m_pFileMenuActions->addAction(tmpaction);
        QAction *pSaveAction = ActionManager::command(Constants::SAVE)->action();
        pSaveAction->setText(QLatin1String("&Save"));//Otherwise initially the action loads with empty string
         m_pFileMenuActions->addAction(pSaveAction);
    }
}

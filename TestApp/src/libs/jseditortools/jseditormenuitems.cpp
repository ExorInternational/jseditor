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
#include <jseditortools/coreplugin/documentmanager.h>

#include <QFileDialog>

using namespace JsEditorTools;
using namespace Core;
using namespace ExtensionSystem;

JSEditorMenuItems::JSEditorMenuItems(QObject *parent) :
    QObject(parent)
{
    m_pFileMenuActions = NULL;
    m_pEditMenu = NULL;
    createActionGroups();
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
void JSEditorMenuItems::saveAll()
{
    DocumentManager::saveAllModifiedDocumentsSilently();
}
void JSEditorMenuItems::createActionGroups()
{
    createFileMenuItems();
    createEditMenuItems();
}

void JSEditorMenuItems::createFileMenuItems()
{
    if(m_pFileMenuActions == NULL)
    {
        m_pFileMenuActions = new QActionGroup(this);

        Context globalContext(Constants::C_GLOBAL);

//        ActionContainer *filemenu = ActionManager::createMenu(Constants::M_FILE);
    //        filemenu->appendGroup(Constants::G_FILE_NEW);
    //        filemenu->appendGroup(Constants::G_FILE_OPEN);

    //        ActionContainer *mfile = ActionManager::actionContainer(Constants::M_FILE);

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
        QAction *openAction = new QAction(icon, tr("&Open File"), this);
        cmd = ActionManager::registerAction(openAction, Constants::OPEN, globalContext);
        cmd->setDefaultKeySequence(QKeySequence::Open);
    //        mfile->addAction(cmd, Constants::G_FILE_OPEN);
        connect(openAction, SIGNAL(triggered()), this, SLOT(openFileInEditor()));
        m_pFileMenuActions->addAction(openAction);

        QAction *separator1 = new QAction(this);
        separator1->setSeparator(true);
        m_pFileMenuActions->addAction(separator1);

        // Save Action
        icon = QIcon::fromTheme(QLatin1String("document-save"), QIcon(QLatin1String(Constants::ICON_SAVEFILE)));
        QAction *tmpaction = new QAction(icon, tr("&Save"), this);
        tmpaction->setEnabled(false);
        cmd = ActionManager::registerAction(tmpaction, Constants::SAVE, globalContext);
        cmd->setDefaultKeySequence(QKeySequence::Save);
        cmd->setAttribute(Command::CA_UpdateText);
        cmd->setDescription(tr("Save"));
    //        mfile->addAction(cmd, Constants::G_FILE_SAVE);
        QAction *pSaveAction = ActionManager::command(Constants::SAVE)->action();
        pSaveAction->setText(QLatin1String("&Save"));//Otherwise initially the action loads with empty string
         m_pFileMenuActions->addAction(pSaveAction);

         // Save As Action
         icon = QIcon::fromTheme(QLatin1String("document-save-as"));
         tmpaction = new QAction(icon, tr("Save &As..."), this);
         tmpaction->setEnabled(false);
         cmd = ActionManager::registerAction(tmpaction, Constants::SAVEAS, globalContext);
         cmd->setDefaultKeySequence(QKeySequence(UseMacShortcuts ? tr("Ctrl+Shift+S") : QString()));
         cmd->setAttribute(Command::CA_UpdateText);
         cmd->setDescription(tr("Save As..."));
    //         mfile->addAction(cmd, Constants::G_FILE_SAVE);
         QAction *pSaveAsAction = ActionManager::command(Constants::SAVEAS)->action();
         pSaveAsAction->setText(QLatin1String("Save &As..."));//Otherwise initially the action loads with empty string
          m_pFileMenuActions->addAction(pSaveAsAction);

          QAction *saveAllAction = new QAction(tr("Save A&ll"), this);
          cmd = ActionManager::registerAction(saveAllAction, Constants::SAVEALL, globalContext);
          cmd->setDefaultKeySequence(QKeySequence(UseMacShortcuts ? QString() : tr("Ctrl+Shift+S")));
    //          mfile->addAction(cmd, Constants::G_FILE_SAVE);
          connect(saveAllAction, SIGNAL(triggered()), this, SLOT(saveAll()));
          m_pFileMenuActions->addAction(saveAllAction);

          QAction *pRevertToSavedAction = ActionManager::command(Constants::REVERTTOSAVED)->action();
          m_pFileMenuActions->addAction(pRevertToSavedAction);

          QAction *separator2 = new QAction(this);
          separator2->setSeparator(true);
          m_pFileMenuActions->addAction(separator2);

          QAction *pCloseAction = ActionManager::command(Constants::CLOSE)->action();
          m_pFileMenuActions->addAction(pCloseAction);

          QAction *pCloseAllAction = ActionManager::command(Constants::CLOSEALL)->action();
          m_pFileMenuActions->addAction(pCloseAllAction);

          QAction *pCloseOthers = ActionManager::command(Constants::CLOSEOTHERS)->action();
          m_pFileMenuActions->addAction(pCloseOthers);

          //CLOSEALLEXCEPTVISIBLE is not added since its for other editors used in Qt Creator.
          //For this library we only have one editor(text editor).

          QAction *separator3 = new QAction(this);
          separator3->setSeparator(true);
          m_pFileMenuActions->addAction(separator3);

          // Print Action
    //          icon = QIcon::fromTheme(QLatin1String("document-print"));
    //          tmpaction = new QAction(icon, tr("&Print..."), this);
    //          tmpaction->setEnabled(false);
    //          cmd = ActionManager::registerAction(tmpaction, Constants::PRINT, globalContext);
    //          cmd->setDefaultKeySequence(QKeySequence::Print);
    //          mfile->addAction(cmd, Constants::G_FILE_PRINT);

          //we dont need tht above comment for the print action. But for the 'Save', 'Save as'
          //actions, the above type of code is required otherwise the filename will not be
          //shown along with them.
          QAction *pPrintAction = ActionManager::command(Constants::PRINT)->action();
          pPrintAction->setText(QLatin1String("&Print..."));//Otherwise initially the action loads with empty string
          m_pFileMenuActions->addAction(pPrintAction);
    }
}

void JSEditorMenuItems::createEditMenuItems()
{
    if(m_pEditMenu == NULL)
    {
        m_pEditMenu = new QMenu(QLatin1String("Edit"), NULL);
        
//        m_pEditMenuActions->addAction(QLatin1String("1"));
//        m_pEditMenuActions->addAction(QLatin1String("2"));

//        QMenu *pMenu = new QMenu(QLatin1String("Ad"), NULL);
//        pMenu->addAction(QLatin1String("3"));
//        pMenu->addAction(QLatin1String("4"));
//        m_pEditMenuActions->addMenu(pMenu);

        Context globalContext(Constants::C_GLOBAL);

        QIcon icon = QIcon::fromTheme(QLatin1String("edit-undo"), QIcon(QLatin1String(Constants::ICON_UNDO)));
        QAction *tmpaction = new QAction(icon, tr("&Undo"), this);
        Command *cmd = ActionManager::registerAction(tmpaction, Constants::UNDO, globalContext);
        cmd->setDefaultKeySequence(QKeySequence::Undo);
        cmd->setAttribute(Command::CA_UpdateText);
        cmd->setDescription(tr("Undo"));
//        medit->addAction(cmd, Constants::G_EDIT_UNDOREDO);
        tmpaction->setEnabled(false);
        QAction *pUndoAction = ActionManager::command(Constants::UNDO)->action();
        pUndoAction->setText(QLatin1String("&Undo"));//Otherwise initially the action loads with empty string
         m_pEditMenu->addAction(pUndoAction);

         // Redo Action
         icon = QIcon::fromTheme(QLatin1String("edit-redo"), QIcon(QLatin1String(Constants::ICON_REDO)));
         tmpaction = new QAction(icon, tr("&Redo"), this);
         cmd = ActionManager::registerAction(tmpaction, Constants::REDO, globalContext);
         cmd->setDefaultKeySequence(QKeySequence::Redo);
         cmd->setAttribute(Command::CA_UpdateText);
         cmd->setDescription(tr("Redo"));
//         medit->addAction(cmd, Constants::G_EDIT_UNDOREDO);
         tmpaction->setEnabled(false);
         QAction *pRedoAction = ActionManager::command(Constants::REDO)->action();
         pRedoAction->setText(QLatin1String("&Redo"));//Otherwise initially the action loads with empty string
         m_pEditMenu->addAction(pRedoAction);

         m_pEditMenu->addSeparator();
    }
}

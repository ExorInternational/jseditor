#include "jseditormenuitems.h"

//#720 ROOPAK - START
#include <coreplugin/idocument.h>
#include <coreplugin/idocumentfactory.h>
#include <coreplugin/editormanager/ieditorfactory.h>
#include <coreplugin/mimedatabase.h>
#include <coreplugin/modemanager.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <extensionsystem/pluginmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer_p.h>
#include <coreplugin/documentmanager.h>
#include <texteditor/texteditorconstants.h>
#include <coreplugin/find/textfindconstants.h>
#include <coreplugin/find/ifindfilter.h>
#include <qmljstools/qmljstoolsconstants.h>
#include <qmljseditor/qmljseditorconstants.h>

#include <QFileDialog>

using namespace JsEditorTools;
using namespace Core;
using namespace ExtensionSystem;

JSEditorMenuItems::JSEditorMenuItems(QObject *parent) :
    QObject(parent)
{
    m_pFileMenu = NULL;

    m_pEditMenu = NULL;
    m_pEditAdvancedMenu = NULL;
    m_pEditFindReplaceMenu = NULL;
    m_pEditFindReplaceAdvancedFindMenu = NULL;

    m_pToolsMenu = NULL;
    m_pToolsQMLJSMenu = NULL;

    m_pWindowMenu = NULL;
    m_pWindowOutputPanesMenu = NULL;
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
    createToolsMenuItems();
    createWindowMenu();
}

void JSEditorMenuItems::createFileMenuItems()
{
    if(m_pFileMenu == NULL)
    {
        m_pFileMenu = new QMenu(QLatin1String("File"), NULL);

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
        m_pFileMenu->addAction(newAction);

        // Open Action
        icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(QLatin1String(Constants::ICON_OPENFILE)));
        QAction *openAction = new QAction(icon, tr("&Open File"), this);
        cmd = ActionManager::registerAction(openAction, Constants::OPEN, globalContext);
        cmd->setDefaultKeySequence(QKeySequence::Open);
    //        mfile->addAction(cmd, Constants::G_FILE_OPEN);
        connect(openAction, SIGNAL(triggered()), this, SLOT(openFileInEditor()));
        m_pFileMenu->addAction(openAction);

        m_pFileMenu->addSeparator();

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
         m_pFileMenu->addAction(pSaveAction);

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
          m_pFileMenu->addAction(pSaveAsAction);

          QAction *saveAllAction = new QAction(tr("Save A&ll"), this);
          cmd = ActionManager::registerAction(saveAllAction, Constants::SAVEALL, globalContext);
          cmd->setDefaultKeySequence(QKeySequence(UseMacShortcuts ? QString() : tr("Ctrl+Shift+S")));
    //          mfile->addAction(cmd, Constants::G_FILE_SAVE);
          connect(saveAllAction, SIGNAL(triggered()), this, SLOT(saveAll()));
          m_pFileMenu->addAction(saveAllAction);

          QAction *pRevertToSavedAction = ActionManager::command(Constants::REVERTTOSAVED)->action();
          m_pFileMenu->addAction(pRevertToSavedAction);

          m_pFileMenu->addSeparator();

          QAction *pCloseAction = ActionManager::command(Constants::CLOSE)->action();
          m_pFileMenu->addAction(pCloseAction);

          QAction *pCloseAllAction = ActionManager::command(Constants::CLOSEALL)->action();
          m_pFileMenu->addAction(pCloseAllAction);

          QAction *pCloseOthers = ActionManager::command(Constants::CLOSEOTHERS)->action();
          m_pFileMenu->addAction(pCloseOthers);

          //CLOSEALLEXCEPTVISIBLE is not added since its for other editors used in Qt Creator.
          //For this library we only have one editor(text editor).

          m_pFileMenu->addSeparator();

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
          m_pFileMenu->addAction(pPrintAction);
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

         // Cut Action
         icon = QIcon::fromTheme(QLatin1String("edit-cut"), QIcon(QLatin1String(Constants::ICON_CUT)));
         tmpaction = new QAction(icon, tr("Cu&t"), this);
         cmd = ActionManager::registerAction(tmpaction, Constants::CUT, globalContext);
         cmd->setDefaultKeySequence(QKeySequence::Cut);
//         medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
         tmpaction->setEnabled(false);
         QAction *pCutAction = ActionManager::command(Constants::CUT)->action();
         pCutAction->setText(QLatin1String("Cu&t"));//Otherwise initially the action loads with empty string
         m_pEditMenu->addAction(pCutAction);

         // Copy Action
         icon = QIcon::fromTheme(QLatin1String("edit-copy"), QIcon(QLatin1String(Constants::ICON_COPY)));
         tmpaction = new QAction(icon, tr("&Copy"), this);
         cmd = ActionManager::registerAction(tmpaction, Constants::COPY, globalContext);
         cmd->setDefaultKeySequence(QKeySequence::Copy);
//         medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
         tmpaction->setEnabled(false);
         QAction *pCopyAction = ActionManager::command(Constants::COPY)->action();
         pCopyAction->setText(QLatin1String("&Copy"));//Otherwise initially the action loads with empty string
         m_pEditMenu->addAction(pCopyAction);

         // Paste Action
         icon = QIcon::fromTheme(QLatin1String("edit-paste"), QIcon(QLatin1String(Constants::ICON_PASTE)));
         tmpaction = new QAction(icon, tr("&Paste"), this);
         cmd = ActionManager::registerAction(tmpaction, Constants::PASTE, globalContext);
         cmd->setDefaultKeySequence(QKeySequence::Paste);
//         medit->addAction(cmd, Constants::G_EDIT_COPYPASTE);
         tmpaction->setEnabled(false);
         QAction *pPasteAction = ActionManager::command(Constants::PASTE)->action();
         pPasteAction->setText(QLatin1String("&Paste"));//Otherwise initially the action loads with empty string
         m_pEditMenu->addAction(pPasteAction);

         QAction *pCircularPasteAction = ActionManager::command(TextEditor::Constants::CIRCULAR_PASTE)->action();
         m_pEditMenu->addAction(pCircularPasteAction);

         m_pEditMenu->addSeparator();

         // Select All
         icon = QIcon::fromTheme(QLatin1String("edit-select-all"));
         tmpaction = new QAction(icon, tr("Select &All"), this);
         cmd = ActionManager::registerAction(tmpaction, Constants::SELECTALL, globalContext);
         cmd->setDefaultKeySequence(QKeySequence::SelectAll);
//         medit->addAction(cmd, Constants::G_EDIT_SELECTALL);
         tmpaction->setEnabled(false);
         QAction *pSelectAllAction = ActionManager::command(Constants::SELECTALL)->action();
         pSelectAllAction->setText(QLatin1String("Select &All"));//Otherwise initially the action loads with empty string
         m_pEditMenu->addAction(pSelectAllAction);

         m_pEditMenu->addSeparator();

         createEditAdvancedMenu();
         m_pEditMenu->addMenu(m_pEditAdvancedMenu);

         m_pEditMenu->addSeparator();

         createEditFindReplaceMenu();
         m_pEditMenu->addMenu(m_pEditFindReplaceMenu);

         QAction *pGotoLineAction = ActionManager::command(Constants::GOTO)->action();
         pGotoLineAction->setText(QLatin1String("&Go to Line..."));//Otherwise initially the action loads with empty string
         m_pEditMenu->addAction(pGotoLineAction);

         QAction *pSelectEncodingAction = ActionManager::command(TextEditor::Constants::SELECT_ENCODING)->action();
         m_pEditMenu->addAction(pSelectEncodingAction);
    }
}
void JSEditorMenuItems::createEditAdvancedMenu()
{
    if(m_pEditAdvancedMenu == NULL)
    {
        m_pEditAdvancedMenu = new QMenu(QLatin1String("Ad&vanced"), NULL);

        QAction *pAutoIndentSelectionAction = ActionManager::command(TextEditor::Constants::AUTO_INDENT_SELECTION)->action();
        m_pEditAdvancedMenu->addAction(pAutoIndentSelectionAction);

        QAction *pRewrapParagraphAction = ActionManager::command(TextEditor::Constants::REWRAP_PARAGRAPH)->action();
        m_pEditAdvancedMenu->addAction(pRewrapParagraphAction);

        QAction *pVisualizeWhiteSpaceAction = ActionManager::command(TextEditor::Constants::VISUALIZE_WHITESPACE)->action();
        m_pEditAdvancedMenu->addAction(pVisualizeWhiteSpaceAction);

        QAction *pCleanWhiteSpaceAction = ActionManager::command(TextEditor::Constants::CLEAN_WHITESPACE)->action();
        m_pEditAdvancedMenu->addAction(pCleanWhiteSpaceAction);

        QAction *pTextWrappingAction = ActionManager::command(TextEditor::Constants::TEXT_WRAPPING)->action();
        m_pEditAdvancedMenu->addAction(pTextWrappingAction);

        QAction *pToggleCommentAction = ActionManager::command(TextEditor::Constants::UN_COMMENT_SELECTION)->action();
        m_pEditAdvancedMenu->addAction(pToggleCommentAction);

        m_pEditAdvancedMenu->addSeparator();

        QAction *pFoldAction = ActionManager::command(TextEditor::Constants::FOLD)->action();
        m_pEditAdvancedMenu->addAction(pFoldAction);

        QAction *pUnfoldAction = ActionManager::command(TextEditor::Constants::UNFOLD)->action();
        m_pEditAdvancedMenu->addAction(pUnfoldAction);

        QAction *pUnfoldAllAction = ActionManager::command(TextEditor::Constants::UNFOLD_ALL)->action();
        m_pEditAdvancedMenu->addAction(pUnfoldAllAction);

        m_pEditAdvancedMenu->addSeparator();

        QAction *pGotoBlockAction = ActionManager::command(TextEditor::Constants::GOTO_BLOCK_START)->action();
        m_pEditAdvancedMenu->addAction(pGotoBlockAction);

        QAction *pGotoBlockEndAction = ActionManager::command(TextEditor::Constants::GOTO_BLOCK_END)->action();
        m_pEditAdvancedMenu->addAction(pGotoBlockEndAction);

        QAction *pSelectBlockUpAction = ActionManager::command(TextEditor::Constants::SELECT_BLOCK_UP)->action();
        m_pEditAdvancedMenu->addAction(pSelectBlockUpAction);

        QAction *pSelectBlockDownAction = ActionManager::command(TextEditor::Constants::SELECT_BLOCK_DOWN)->action();
        m_pEditAdvancedMenu->addAction(pSelectBlockDownAction);

        m_pEditAdvancedMenu->addSeparator();

        QAction *pIncreaseFontSizeAction = ActionManager::command(TextEditor::Constants::INCREASE_FONT_SIZE)->action();
        m_pEditAdvancedMenu->addAction(pIncreaseFontSizeAction);

        QAction *pDecreaseFontSizeAction = ActionManager::command(TextEditor::Constants::DECREASE_FONT_SIZE)->action();
        m_pEditAdvancedMenu->addAction(pDecreaseFontSizeAction);

        QAction *pResetFontSizeAction = ActionManager::command(TextEditor::Constants::RESET_FONT_SIZE)->action();
        m_pEditAdvancedMenu->addAction(pResetFontSizeAction);

        m_pEditAdvancedMenu->addSeparator();
    }
}

void JSEditorMenuItems::createEditFindReplaceMenu()
{
    if(m_pEditFindReplaceMenu == NULL)
    {
        m_pEditFindReplaceMenu = new QMenu(QLatin1String("&Find/Replace"), NULL);

        QAction *pFindInDocAction = ActionManager::command(Constants::FIND_IN_DOCUMENT)->action();
        pFindInDocAction->setEnabled(false);
        m_pEditFindReplaceMenu->addAction(pFindInDocAction);

        createEditFindReplaceAdvancedFindMenu();
        m_pEditFindReplaceMenu->addMenu(m_pEditFindReplaceAdvancedFindMenu);

        m_pEditFindReplaceMenu->addSeparator();

        QAction *pCaseSensitiveAction = ActionManager::command(Constants::CASE_SENSITIVE)->action();
        m_pEditFindReplaceMenu->addAction(pCaseSensitiveAction);

        QAction *pWholeWorldAction = ActionManager::command(Constants::WHOLE_WORDS)->action();
        m_pEditFindReplaceMenu->addAction(pWholeWorldAction);

        QAction *pRegularExpressionAction = ActionManager::command(Constants::REGULAR_EXPRESSIONS)->action();
        m_pEditFindReplaceMenu->addAction(pRegularExpressionAction);

        QAction *pPreserveCaseAction = ActionManager::command(Constants::PRESERVE_CASE)->action();
        m_pEditFindReplaceMenu->addAction(pPreserveCaseAction);

        m_pEditFindReplaceMenu->addSeparator();

        QAction *pFindNextAction = ActionManager::command(Constants::FIND_NEXT)->action();
        m_pEditFindReplaceMenu->addAction(pFindNextAction);

        QAction *pFindPreviosuAction = ActionManager::command(Constants::FIND_PREVIOUS)->action();
        m_pEditFindReplaceMenu->addAction(pFindPreviosuAction);

        QAction *pFindNextSelectedAction = ActionManager::command(Constants::FIND_NEXT_SELECTED)->action();
        m_pEditFindReplaceMenu->addAction(pFindNextSelectedAction);

        QAction *pFindPrevSelectedAction = ActionManager::command(Constants::FIND_PREV_SELECTED)->action();
        m_pEditFindReplaceMenu->addAction(pFindPrevSelectedAction);

        QAction *pReplaceAction = ActionManager::command(Constants::REPLACE)->action();
        m_pEditFindReplaceMenu->addAction(pReplaceAction);

        QAction *pReplaceNextAction = ActionManager::command(Constants::REPLACE_NEXT)->action();
        m_pEditFindReplaceMenu->addAction(pReplaceNextAction);

        QAction *pReplacePrevAction = ActionManager::command(Constants::REPLACE_PREVIOUS)->action();
        m_pEditFindReplaceMenu->addAction(pReplacePrevAction);

        QAction *pReplaceAllAction = ActionManager::command(Constants::REPLACE_ALL)->action();
        m_pEditFindReplaceMenu->addAction(pReplaceAllAction);
    }
}

void JSEditorMenuItems::createEditFindReplaceAdvancedFindMenu()
{
    if(m_pEditFindReplaceAdvancedFindMenu == NULL)
    {
        m_pEditFindReplaceAdvancedFindMenu = new QMenu(QLatin1String("Advanced Find"), NULL);

        QAction *pAdvancedFindAction = ActionManager::command(Constants::ADVANCED_FIND)->action();
        m_pEditFindReplaceAdvancedFindMenu->addAction(pAdvancedFindAction);


        QList<IFindFilter*> findInterfaces =
            ExtensionSystem::PluginManager::getObjects<IFindFilter>();
        foreach (IFindFilter *filter, findInterfaces) {
            const Core::Id base("FindFilter.");
            QAction *pFindFilterAction = ActionManager::command(base.withSuffix(filter->id()))->action();
            m_pEditFindReplaceAdvancedFindMenu->addAction(pFindFilterAction);
        }
    }
}

void JSEditorMenuItems::createToolsMenuItems()
{
    if(m_pToolsMenu == NULL)
    {
        m_pToolsMenu = new QMenu(QLatin1String("&Tools"), NULL);

        createToolsQMLJSMenu();
        m_pToolsMenu->addMenu(m_pToolsQMLJSMenu);

        QAction *pOptionsAction = ActionManager::command(Constants::OPTIONS)->action();
        m_pToolsMenu->addAction(pOptionsAction);
    }
}
void JSEditorMenuItems::createToolsQMLJSMenu()
{
    if(m_pToolsQMLJSMenu == NULL)
    {
        m_pToolsQMLJSMenu = new QMenu(QLatin1String("&QML/JS"), NULL);

        QAction *pResetCodeModelAction = ActionManager::command(QmlJSTools::Constants::RESET_CODEMODEL)->action();
        m_pToolsQMLJSMenu->addAction(pResetCodeModelAction);

        m_pToolsQMLJSMenu->addSeparator();

        QAction *pSollowSymbolUnderCursorAction = ActionManager::command(TextEditor::Constants::FOLLOW_SYMBOL_UNDER_CURSOR)->action();
        m_pToolsQMLJSMenu->addAction(pSollowSymbolUnderCursorAction);

        QAction *pFindUsagesAction = ActionManager::command(QmlJSEditor::Constants::FIND_USAGES)->action();
        m_pToolsQMLJSMenu->addAction(pFindUsagesAction);

        QAction *pRenameUsagesAction = ActionManager::command(QmlJSEditor::Constants::RENAME_USAGES)->action();
        m_pToolsQMLJSMenu->addAction(pRenameUsagesAction);

        QAction *pRunSemanticAction = ActionManager::command(QmlJSEditor::Constants::RUN_SEMANTIC_SCAN)->action();
        m_pToolsQMLJSMenu->addAction(pRunSemanticAction);

        QAction *pReformatFileAction = ActionManager::command(QmlJSEditor::Constants::REFORMAT_FILE)->action();
        m_pToolsQMLJSMenu->addAction(pReformatFileAction);
    }
}

void JSEditorMenuItems::createWindowMenu()
{
    if(m_pWindowMenu == NULL)
    {
        m_pWindowMenu = new QMenu(QLatin1String("&Window"), NULL);

        QAction *pToggleModeSelectorAction = ActionManager::command(Constants::TOGGLE_MODE_SELECTOR)->action();
        m_pWindowMenu->addAction(pToggleModeSelectorAction);

        createWindowOutputPanesMenu();
        m_pWindowMenu->addMenu(m_pWindowOutputPanesMenu);

        m_pWindowMenu->addSeparator();

        QAction *pWidowSplit = ActionManager::command(Constants::SPLIT)->action();
        m_pWindowMenu->addAction(pWidowSplit);

        QAction *pWidowSplitSideBySide = ActionManager::command(Constants::SPLIT_SIDE_BY_SIDE)->action();
        m_pWindowMenu->addAction(pWidowSplitSideBySide);

        QAction *pWidowSplitNewWindow = ActionManager::command(Constants::SPLIT_NEW_WINDOW)->action();
        m_pWindowMenu->addAction(pWidowSplitNewWindow);

        QAction *pWidowRemoveCurrentSplit = ActionManager::command(Constants::REMOVE_CURRENT_SPLIT)->action();
        m_pWindowMenu->addAction(pWidowRemoveCurrentSplit);

        QAction *pWidowRemoveAllSplits = ActionManager::command(Constants::REMOVE_ALL_SPLITS)->action();
        m_pWindowMenu->addAction(pWidowRemoveAllSplits);

        QAction *pWidowGotoNextSplit = ActionManager::command(Constants::GOTO_NEXT_SPLIT)->action();
        m_pWindowMenu->addAction(pWidowGotoNextSplit);

        m_pWindowMenu->addSeparator();

        QAction *pWidowGoBack = ActionManager::command(Constants::GO_BACK)->action();
        m_pWindowMenu->addAction(pWidowGoBack);

        QAction *pWidowGoForward = ActionManager::command(Constants::GO_FORWARD)->action();
        m_pWindowMenu->addAction(pWidowGoForward);

        QAction *pWidowGoToPrevInHistory = ActionManager::command(Constants::GOTOPREVINHISTORY)->action();
        m_pWindowMenu->addAction(pWidowGoToPrevInHistory);

        QAction *pWidowGoToNextInHistory = ActionManager::command(Constants::GOTONEXTINHISTORY)->action();
        m_pWindowMenu->addAction(pWidowGoToNextInHistory);
    }
}
void JSEditorMenuItems::createWindowOutputPanesMenu()
{
    if(m_pWindowOutputPanesMenu == NULL)
    {
        m_pWindowOutputPanesMenu  = new QMenu(QLatin1String("Output &Panes"), NULL);

        QAction *pOutputPaneClear = ActionManager::command("Coreplugin.OutputPane.clear")->action();
        m_pWindowOutputPanesMenu->addAction(pOutputPaneClear);

        QAction *pOutputPanePrevItem = ActionManager::command("Coreplugin.OutputPane.previtem")->action();
        m_pWindowOutputPanesMenu->addAction(pOutputPanePrevItem);

        QAction *pOutputPaneNextItem = ActionManager::command("Coreplugin.OutputPane.nextitem")->action();
        m_pWindowOutputPanesMenu->addAction(pOutputPaneNextItem);

        QAction *pOutputPaneMaximize = ActionManager::command("Coreplugin.OutputPane.minmax")->action();
        m_pWindowOutputPanesMenu->addAction(pOutputPaneMaximize);

        m_pWindowOutputPanesMenu->addSeparator();

        QAction *pOutputPaneSearchResults = ActionManager::command("QtCreator.Pane.SearchResults")->action();
        m_pWindowOutputPanesMenu->addAction(pOutputPaneSearchResults);
    }
}

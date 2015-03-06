#include "jseditortools.h"
#include <coreplugin/coreplugin.h>
#include <coreplugin/documentmanager.h>
#include <texteditor/texteditorplugin.h>
#include <qmljstools/qmljstoolsplugin.h>
#include <qmljseditor/qmljseditorplugin.h>
#include <extensionsystem/pluginmanager.h>
//#include <app/app_version.h>//#720 - ROOPAK
#include <jseditormenuitems.h>
#include <coreplugin/icore.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <texteditor/itexteditor.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/fancytabwidget.h>
#include <qmljseditor/qmljseditorconstants.h>
#include <coreplugin/editormanager/editorview.h>
#include <qmljseditor/qmljseditor.h>
#include <coreplugin/outputpanemanager.h>
#include <coreplugin/find/searchresultwindow.h>
#include <texteditor/findincurrentfile.h>
#include <coreplugin/find/findtoolwindow.h>
#include <qmljseditor/qmljseditordocument.h>
#include <qmljstools/qmljstoolsconstants.h>
#include <coreplugin/dialogs/settingsdialog.h>
#include <coreplugin/icontext.h>

#include <QStringList>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QInputDialog>
#include <QTextBlock>
#include <QTranslator>
#include <QLibraryInfo>

using namespace JsEditorTools;
using namespace ExtensionSystem;

static bool copyRecursively(const QString &srcFilePath,
                            const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        if (!targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            return false;
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &fileName, fileNames) {
            const QString newSrcFilePath
                    = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath
                    = tgtFilePath + QLatin1Char('/') + fileName;
            if (!copyRecursively(newSrcFilePath, newTgtFilePath))
                return false;
        }
    } else {
        if (!QFile::copy(srcFilePath, tgtFilePath))
            return false;
    }
    return true;
}

static QSettings *createUserSettings()
{
    return new QSettings(QSettings::IniFormat, QSettings::UserScope,
                         QLatin1String(Core::Constants::IDE_SETTINGSVARIANT_STR),
                         QLatin1String(Core::Constants::IDE_APPNAME_STR));
}

static inline QSettings *userSettings()
{
    QSettings *settings = createUserSettings();
    const QString fromVariant = QLatin1String(Core::Constants::IDE_COPY_SETTINGS_FROM_VARIANT_STR);
    if (fromVariant.isEmpty())
        return settings;

    // Copy old settings to new ones:
    QFileInfo pathFi = QFileInfo(settings->fileName());
    if (pathFi.exists()) // already copied.
        return settings;

    QDir destDir = pathFi.absolutePath();
    if (!destDir.exists())
        destDir.mkpath(pathFi.absolutePath());

    QDir srcDir = destDir;
    srcDir.cdUp();
    if (!srcDir.cd(fromVariant))
        return settings;

    if (srcDir == destDir) // Nothing to copy and no settings yet
        return settings;

    QStringList entries = srcDir.entryList();
    foreach (const QString &file, entries) {
        const QString lowerFile = file.toLower();
        if (lowerFile.startsWith(QLatin1String("profiles.xml"))
                || lowerFile.startsWith(QLatin1String("toolchains.xml"))
                || lowerFile.startsWith(QLatin1String("qtversion.xml"))
                || lowerFile.startsWith(QLatin1String("devices.xml"))
                || lowerFile.startsWith(QLatin1String("debuggers.xml"))
                || lowerFile.startsWith(QLatin1String("qtcreator.")))
            QFile::copy(srcDir.absoluteFilePath(file), destDir.absoluteFilePath(file));
        if (file == QLatin1String("qtcreator"))
            copyRecursively(srcDir.absoluteFilePath(file), destDir.absoluteFilePath(file));
    }

    // Make sure to use the copied settings:
    delete settings;
    return createUserSettings();
}

JsEditorToolsLib::JsEditorToolsLib(QWidget *mainWindow, QString strLocale)
{
    m_pDetachedFindWindow = NULL;
    m_MainWindow = NULL;
    m_pDummyMainWidget = new QWidget(mainWindow);
    m_MainWindow = m_pDummyMainWidget;
    setParentWidget(m_MainWindow, strLocale);
}
void copyDefaultFontSettingsFilesFromResource(QSettings *settings)
{
    QString strFileName = settings->fileName();
    if(!strFileName.isEmpty())
    {
        QFileInfo file1(strFileName);
        QString strFilePath = file1.path();
        QString userStylePath = strFilePath + QLatin1String("/JsEditor/styles/default/");
        if(!QDir(userStylePath).exists())
            QDir().mkpath(userStylePath);

        QStringList strStylesList = QStringList() <<    QLatin1String(":/Resources/styles/default.xml")
                                                  <<    QLatin1String(":/Resources/styles/grayscale.xml")
                                                  <<    QLatin1String(":/Resources/styles/darkvim.xml")
                                                  <<    QLatin1String(":/Resources/styles/inkpot.xml")
                                                  <<    QLatin1String(":/Resources/styles/intellij.xml");

        foreach(QString strStyleFileName, strStylesList){
            QFile file2(strStyleFileName);
            if(!file2.open(QFile::ReadOnly | QFile::Text)){
                    qDebug() << "could not open file for read";
            }
            else
            {
                QFileInfo info(file2);
                QString ss = userStylePath + info.fileName();
                bool copied = QFile::copy(strStyleFileName, ss);
                if(!copied)
                    qDebug() << "could not copy file";
            }
        }
    }
}
void copyDefaultTranslationFilesFromResource(QSettings *settings)
{
    QString strFileName = settings->fileName();
    if(!strFileName.isEmpty())
    {
        QFileInfo file1(strFileName);
        QString strFilePath = file1.path();
        QString userTranslationsPath = strFilePath + QLatin1String("/JsEditor/translations/");
        if(!QDir(userTranslationsPath).exists())
            QDir().mkpath(userTranslationsPath);

        QStringList strTranslationsList = QStringList() <<    QLatin1String(":/Resources/translations/jseditortools_de.qm")
                                                  <<    QLatin1String(":/Resources/translations/jseditortools_fr.qm")
                                                  <<    QLatin1String(":/Resources/translations/jseditortools_es.qm")
                                                  <<    QLatin1String(":/Resources/translations/jseditortools_it.qm");

        foreach(QString strTranslationsFileName, strTranslationsList){
            QFile file2(strTranslationsFileName);
            if(!file2.open(QFile::ReadOnly | QFile::Text)){
                    qDebug() << "could not open file for read";
            }
            else
            {
                QFileInfo info(file2);
                QString ss = userTranslationsPath + info.fileName();
                bool copied = QFile::copy(strTranslationsFileName, ss);
                if(!copied)
                    qDebug() << "could not copy file";
            }
        }
    }
}

void setLanguage(const QString &locale, QSettings* settings)
{
    if (settings->value(QLatin1String("General/OverrideLanguage")).toString() != locale)
    {
//        QMessageBox::information(Core::ICore::mainWindow(), tr("Restart required"),
//                                 tr("The language change will take effect after a restart of Qt Creator."));
    }
    if (locale.isEmpty())
        settings->remove(QLatin1String("General/OverrideLanguage"));
    else
        settings->setValue(QLatin1String("General/OverrideLanguage"), locale);
}

void JsEditorToolsLib::loadTranslator(QSettings *settings)
{
//    copyDefaultTranslationFilesFromResource(settings);

    QString strFileName = settings->fileName();
    if(!strFileName.isEmpty())
    {
        QFileInfo file1(strFileName);
        QString strFilePath = file1.path();
        //QString userTranslationsPath = strFilePath + QLatin1String("/JsEditor/translations/");
        const QString &creatorTrPath = QLatin1String(":/Resources/translations/");//userTranslationsPath;

//        QTranslator translator;
        QTranslator qtTranslator;
        QStringList uiLanguages;
    // uiLanguages crashes on Windows with 4.8.0 release builds
    #if (QT_VERSION >= 0x040801) || (QT_VERSION >= 0x040800 && !defined(Q_OS_WIN))
        uiLanguages = QLocale::system().uiLanguages();
    #else
        uiLanguages << QLocale::system().name();
    #endif
        QString overrideLanguage = settings->value(QLatin1String("General/OverrideLanguage")).toString();
        if (!overrideLanguage.isEmpty())
            uiLanguages.prepend(overrideLanguage);

        foreach (QString locale, uiLanguages) {
    #if (QT_VERSION >= 0x050000)
            locale = QLocale(locale).name();
    #else
            locale.replace(QLatin1Char('-'), QLatin1Char('_')); // work around QTBUG-25973
    #endif
            if (m_oTranslator.load(QLatin1String("jseditortools_") + locale, creatorTrPath)) {
//                const QString &qtTrPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
//                const QString &qtTrFile = QLatin1String("qt_") + locale;
                // Binary installer puts Qt tr files into creatorTrPath
                //if (qtTranslator.load(qtTrFile, qtTrPath) || qtTranslator.load(qtTrFile, creatorTrPath)) {
                    qApp->installTranslator(&m_oTranslator);
                //    qApp->installTranslator(&qtTranslator);
                    qApp->setProperty("qtc_locale", locale);
                    break;
                //}
//                m_oTranslator.load(QString()); // unload()
            } else if (locale == QLatin1String("C") /* overrideLanguage == "English" */) {
                // use built-in
                break;
            } else if (locale.startsWith(QLatin1String("en")) /* "English" is built-in */) {
                // use built-in
                break;
            }
        }

    }


}
void JsEditorToolsLib::setParentWidget(QWidget *mainWindow, QString strLocale)
{
    if(mainWindow != NULL)
    {
        if(m_pDummyMainWidget && m_pDummyMainWidget!= m_MainWindow)//no need for this variable if parent widget is set separately
        {
            delete m_pDummyMainWidget;
            m_pDummyMainWidget = 0;
        }
//        else if(m_pDummyMainWidget)
//        {
//            m_pDummyMainWidget->hide();
//        }

        m_MainWindow = mainWindow;

        QString err;
        QStringList arguments;
    
        QSettings *settings = userSettings();
        QSettings *globalSettings = new QSettings(QSettings::IniFormat, QSettings::SystemScope,
                                                  QLatin1String(Core::Constants::IDE_SETTINGSVARIANT_STR),
                                                  QLatin1String(Core::Constants::IDE_APPNAME_STR));
        copyDefaultFontSettingsFilesFromResource(settings);

        setLanguage(strLocale, settings);//testing
        loadTranslator(settings);

        m_pPluginManager = new ExtensionSystem::PluginManager();
        PluginManager::setFileExtension(QLatin1String("pluginspec"));
        PluginManager::setGlobalSettings(globalSettings);
        PluginManager::setSettings(settings);
    
        m_pCorePlugin = new Core::Internal::CorePlugin(m_MainWindow);
        m_pCorePlugin->initialize(arguments, &err);
    
        m_pTextEditorPlugin = new TextEditor::Internal::TextEditorPlugin();
        m_pTextEditorPlugin->initialize(arguments, &err);
        m_pTextEditorPlugin->extensionsInitialized();
    
        m_pQmlJSToolsPlugin = new QmlJSTools::Internal::QmlJSToolsPlugin();
        m_pQmlJSToolsPlugin->initialize(arguments, &err);
        m_pQmlJSToolsPlugin->extensionsInitialized();
    
        m_pQmlJSEditorPlugin = new QmlJSEditor::Internal::QmlJSEditorPlugin();
        m_pQmlJSEditorPlugin->initialize(arguments, &err);
        m_pQmlJSEditorPlugin->extensionsInitialized();
    
        m_pCorePlugin->setEnableRestoreMainwindowState(false);
        m_pCorePlugin->extensionsInitialized();//this should be called only in the final step(after the other plugins are loaded).
    
        m_pJSEditorMenuItems = NULL;
//        m_pJSEditorMenuItems = new JSEditorMenuItems(this);

        //find dialog
        if(m_pDetachedFindWindow == NULL)
        {
            m_pDetachedFindWindow = Core::Internal::OutputPaneManager::instance();
            m_pDetachedFindWindow->setParent(NULL);
            m_pDetachedFindWindow->setWindowModality(Qt::WindowModal);
            Core::SearchResultWindow::instance()->setDisconnectSearchResultItems(true);
            connect(Core::SearchResultWindow::instance(), SIGNAL(searchItemSelected(QString, int)), this, SIGNAL(searchResultItemSelected(QString, int)));
            connect(Core::SearchResultWindow::instance(), SIGNAL(showPage(int)), m_pDetachedFindWindow, SLOT(show()));
            connect(Core::SearchResultWindow::instance(), SIGNAL(showPage(int)), this, SIGNAL(showFindDialog()));
            m_pDetachedFindWindow->setWindowTitle(tr("Find"));
            m_pDetachedFindWindow->hide();
        }
    }
}
JSEditorMenuItems *JsEditorToolsLib::getJSEditorMenuItems()
{
    if(m_pJSEditorMenuItems == NULL)
        m_pJSEditorMenuItems = new JSEditorMenuItems(this);
    return m_pJSEditorMenuItems;
}
void JsEditorToolsLib::setLayout(QLayout *pLayout)
{
    if(m_pCorePlugin && m_pCorePlugin->getModeStack())
        pLayout->addWidget(m_pCorePlugin->getModeStack());
}

void JsEditorToolsLib::setCustomBuiltinTypes(QMap<JsEditorTools::JSCustomBuiltinKey, QMetaObject> oCustomClassTypesList)
{
    if(Core::DocumentManager::instance())
        Core::DocumentManager::m_oCustomClassTypesList = oCustomClassTypesList;
}

JsEditorToolsLib::~JsEditorToolsLib()
{
    if(m_MainWindow)
        m_MainWindow->close();//Sending close-event here is important for showing message box for unsaved changes in the editor and fixing a crash.

    m_pQmlJSEditorPlugin->aboutToShutdown();
    if(m_pQmlJSEditorPlugin)
        delete m_pQmlJSEditorPlugin;
    m_pQmlJSEditorPlugin = 0;

    m_pQmlJSToolsPlugin->aboutToShutdown();
    if(m_pQmlJSToolsPlugin)
        delete m_pQmlJSToolsPlugin;
    m_pQmlJSToolsPlugin = 0;

    m_pTextEditorPlugin->aboutToShutdown();
    if(m_pTextEditorPlugin)
        delete m_pTextEditorPlugin;
    m_pTextEditorPlugin = 0;

    m_pCorePlugin->aboutToShutdown();
    if(m_pCorePlugin)
        delete m_pCorePlugin;
    m_pCorePlugin = 0;

    if(m_pPluginManager)
        delete m_pPluginManager;
    m_pPluginManager = 0;

    if(m_pJSEditorMenuItems)
        delete m_pJSEditorMenuItems;
    m_pJSEditorMenuItems = 0;
}
QPlainTextEdit *JsEditorToolsLib::openFile(QString strFilePath)
{
    QPointer<QmlJSEditor::Internal::QmlJSTextEditorWidget>pTextEditor = NULL;

    Core::ICore::OpenFilesFlags flags = Core::ICore::SwitchMode;
    QFlags<Core::EditorManager::OpenEditorFlag> emFlags;
    if (flags & Core::ICore::CanContainLineNumbers)
        emFlags |=  Core::EditorManager::CanContainLineNumber;
    emFlags |= Core::EditorManager::DoNotChangeCurrentEditor;

    Core::IEditor *editor = Core::EditorManager::openEditor(strFilePath, Core::Id(), emFlags);
    if(editor) {
        QObject::connect(editor->document(), SIGNAL(changed()), this, SIGNAL(currentDocumentChanged()));
        pTextEditor = qobject_cast<QmlJSEditor::Internal::QmlJSTextEditorWidget *>(editor->widget());
        QPointer<Core::Internal::EditorView> pEditorView = qobject_cast<Core::Internal::EditorView *>(Core::EditorManager::viewForEditor(editor));
        if(pEditorView){
            pEditorView->removeEditor(editor);
            disconnect(Core::ICore::instance(), SIGNAL(contextAboutToChange(QList<Core::IContext*>)),
                    Core::EditorManager::instance(), SLOT(handleContextChange(QList<Core::IContext*>)));
            if(!m_pDetatchedEditors.contains(editor))
                m_pDetatchedEditors.append(editor);

            //set contect menu
            QMenu *pMenu = new QMenu(pTextEditor);
            pTextEditor->setAlternateMenu(pMenu);
            pTextEditor->setEnableAlternateContextMenu(true);
            populateAlternateContextMenu(pTextEditor, pMenu);
            connect(pTextEditor, SIGNAL(gotFocusIn()), this, SLOT(onTextEditorFocused()));
        }
    }

    return pTextEditor;
}
void JsEditorToolsLib::populateAlternateContextMenu(QPlainTextEdit *pTextEdit, QMenu *pMenu)
{
    QPointer<QmlJSEditor::Internal::QmlJSTextEditorWidget> pBaseTextEdit = qobject_cast<QmlJSEditor::Internal::QmlJSTextEditorWidget *>(pTextEdit);
    if(pBaseTextEdit && pMenu)
    {
        pMenu->addAction(Core::ActionManager::command(Core::Constants::CUT)->action());
        pMenu->addAction(Core::ActionManager::command(Core::Constants::COPY)->action());
        pMenu->addAction(Core::ActionManager::command(Core::Constants::PASTE)->action());
        pMenu->addAction(Core::ActionManager::command(Core::Constants::SELECTALL)->action());
        pMenu->addSeparator();

        QMenu *pAdvancedMenu = new QMenu(pMenu);//pMenu->addMenu(tr("Advanced"));
        QAction *pAdvancedAction = Core::ActionManager::command(Core::Constants::G_EDIT_ADVANCED)->action();
        pMenu->addAction(pAdvancedAction);
        pAdvancedAction->setMenu(pAdvancedMenu);

        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::AUTO_INDENT_SELECTION)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::REWRAP_PARAGRAPH)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::CLEAN_WHITESPACE)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::UN_COMMENT_SELECTION)->action());

        pAdvancedMenu->addSeparator();
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::CUT_LINE)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::COPY_LINE)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::UPPERCASE_SELECTION)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::LOWERCASE_SELECTION)->action());

        pAdvancedMenu->addSeparator();
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::FOLD)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::UNFOLD)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::UNFOLD_ALL)->action());

        pAdvancedMenu->addSeparator();
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::GOTO_BLOCK_START)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::GOTO_BLOCK_END)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::SELECT_BLOCK_UP)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::SELECT_BLOCK_DOWN)->action());

        pAdvancedMenu->addSeparator();
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::INCREASE_FONT_SIZE)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::DECREASE_FONT_SIZE)->action());
        pAdvancedMenu->addAction(Core::ActionManager::command(TextEditor::Constants::RESET_FONT_SIZE)->action());

        pTextEdit->addActions(pAdvancedMenu->actions());

        //pMenu->addAction(Core::ActionManager::command(Core::Constants::FIND_IN_DOCUMENT)->action(), this, SLOT(openDetatchedFindDialog()) );
        QAction *pFindAction = Core::ActionManager::command(Core::Constants::FIND_IN_DOCUMENT)->action();
        pMenu->addAction(pFindAction);
        connect(pFindAction, SIGNAL(triggered(bool)), this, SLOT(openDetatchedFindDialog()), Qt::UniqueConnection);

//        pMenu->addAction(tr("Go To Line..."), this, SLOT(showGoToLineDialog()) );
        QAction *pGoToAction = Core::ActionManager::command(Core::Constants::GOTO)->action();
        pMenu->addAction(pGoToAction);
        connect(pGoToAction, SIGNAL(triggered(bool)), this, SLOT(showGoToLineDialog()), Qt::UniqueConnection);

        QMenu *pToolsMenu = new QMenu(pMenu);//pMenu->addMenu(tr("&Tools"));
        QAction *pToolsAction = Core::ActionManager::command(Core::Constants::G_TOOLS)->action();
        pMenu->addAction(pToolsAction);
        pToolsAction->setMenu(pToolsMenu);

        QMenu *pJavascriptMenu = pToolsMenu->addMenu(tr("Javascript"));
        QAction *pResetCodeModelAction = Core::ActionManager::command(QmlJSTools::Constants::RESET_CODEMODEL)->action();
        pJavascriptMenu->addAction(pResetCodeModelAction);

        pJavascriptMenu->addSeparator();

        QAction *pSollowSymbolUnderCursorAction = Core::ActionManager::command(TextEditor::Constants::FOLLOW_SYMBOL_UNDER_CURSOR)->action();
        pJavascriptMenu->addAction(pSollowSymbolUnderCursorAction);
        pTextEdit->addAction(pSollowSymbolUnderCursorAction);

        QAction *pFindUsagesAction = Core::ActionManager::command(QmlJSEditor::Constants::FIND_USAGES)->action();
        pJavascriptMenu->addAction(pFindUsagesAction);
        pTextEdit->addAction(pFindUsagesAction);

        QAction *pRenameUsagesAction = Core::ActionManager::command(QmlJSEditor::Constants::RENAME_USAGES)->action();
        pJavascriptMenu->addAction(pRenameUsagesAction);
        pTextEdit->addAction(pRenameUsagesAction);

//        QAction *pRunSemanticAction = Core::ActionManager::command(QmlJSEditor::Constants::RUN_SEMANTIC_SCAN)->action();
//        pJavascriptMenu->addAction(pRunSemanticAction);

        QAction *pReformatFileAction = Core::ActionManager::command(QmlJSEditor::Constants::REFORMAT_FILE)->action();
        pJavascriptMenu->addAction(pReformatFileAction);

//        pTextEdit->addActions(pJavascriptMenu->actions());//THIS IS COMMENTED SINCE AUTO-COMPLETION STOPS WORKING IF 'pReformatFileAction' is added to the pTextEdit.

        QAction *pOptionsAction = Core::ActionManager::command(Core::Constants::OPTIONS)->action();
        pToolsMenu->addAction(pOptionsAction);
        connect(pOptionsAction, SIGNAL(triggered(bool)), this, SLOT(showOptionsDialog()), Qt::UniqueConnection);
//        pToolsMenu->addAction(tr("Options"), this, SLOT(showOptionsDialog()) );

        pTextEdit->addActions(pMenu->actions());
    }
}

void JsEditorToolsLib::openDetatchedFindDialog()
{
    if(getFindDialog())
    {
        if(m_pDetachedFindWindow->isHidden())
        {
            m_pDetachedFindWindow->show();
            emit showFindDialog();
        }
        else
        {
            m_pDetachedFindWindow->hide();
            emit hideFindDialog();
        }
    }
}

QPlainTextEdit *JsEditorToolsLib::openNewEditorWidget(QString strContentTitle)
{
    QPlainTextEdit *pTextEditor = NULL;

    Core::ICore::OpenFilesFlags flags = Core::ICore::SwitchMode;
    QFlags<Core::EditorManager::OpenEditorFlag> emFlags;
    if (flags & Core::ICore::CanContainLineNumbers)
        emFlags |=  Core::EditorManager::CanContainLineNumber;
    QByteArray contents("");
    //QString title = QLatin1String("Untitled.js");
    Core::IEditor *editor = Core::EditorManager::openEditorWithContents(Core::Id(QmlJSEditor::Constants::C_QMLJSEDITOR_ID), &strContentTitle,contents, emFlags);
    if(editor) {
        QObject::connect(editor->document(), SIGNAL(changed()), this, SIGNAL(currentDocumentChanged()));
        pTextEditor = qobject_cast<QPlainTextEdit *>(editor->widget());
    }

    return pTextEditor;
}

QString JsEditorToolsLib::getCurrentDocumentText()
{
    QString retStr;

    if(Core::EditorManager::currentDocument()) {
        Core::IDocument *document = Core::EditorManager::currentDocument();
        if(document){
            TextEditor::ITextEditorDocument *textEditorDocument = qobject_cast<TextEditor::ITextEditorDocument *>(document);
            if (textEditorDocument){
                retStr = textEditorDocument->plainText();
            }
        }
    }

    return retStr;
}
void JsEditorToolsLib::setTextToCurrentDocument(QString strText)
{
    if(Core::EditorManager::currentDocument()) {
        Core::IDocument *document = Core::EditorManager::currentDocument();
        if(document){
            TextEditor::ITextEditorDocument *textEditorDocument = qobject_cast<TextEditor::ITextEditorDocument *>(document);
            if (textEditorDocument){
                textEditorDocument->setContents(strText.toAscii());
            }
        }
        else
        {
            qDebug() << QLatin1String("Cannot set text to current document.");
        }
    }
}

void JsEditorToolsLib::undo()
{
    QAction *pUndoAction = Core::ActionManager::command(Core::Constants::UNDO)->action();
    if(pUndoAction)
        pUndoAction->trigger();
}
bool JsEditorToolsLib::isUndoEnabled()
{
    bool bRet = false;

    bRet = Core::ActionManager::command(Core::Constants::UNDO)->isActive();

    return bRet;
}
void JsEditorToolsLib::redo()
{
    QAction *pRedoAction = Core::ActionManager::command(Core::Constants::REDO)->action();
    if(pRedoAction)
        pRedoAction->trigger();
}
bool JsEditorToolsLib::isRedoEnabled()
{
    bool bRet = false;

    bRet = Core::ActionManager::command(Core::Constants::REDO)->isActive();

    return bRet;
}
void JsEditorToolsLib::doCopy()
{
    QAction *pCopyAction = Core::ActionManager::command(Core::Constants::COPY)->action();
    if(pCopyAction)
        pCopyAction->trigger();
}

void JsEditorToolsLib::doCut()
{
    QAction *pCutAction = Core::ActionManager::command(Core::Constants::CUT)->action();
    if(pCutAction)
        pCutAction->trigger();
}

bool JsEditorToolsLib::isPasteEnabled()
{
    bool bRet = false;

    bRet = Core::ActionManager::command(Core::Constants::PASTE)->isActive();

    return bRet;
}

void JsEditorToolsLib::doPaste()
{
    QAction *pPasteAction = Core::ActionManager::command(Core::Constants::PASTE)->action();
    if(pPasteAction)
        pPasteAction->trigger();
}
void JsEditorToolsLib::doSelectAll()
{
    QAction *pSelectAllAction = Core::ActionManager::command(Core::Constants::SELECTALL)->action();
    if(pSelectAllAction)
        pSelectAllAction->trigger();
}
void JsEditorToolsLib::goToLine(QPlainTextEdit *pTextEdit, int lineNumber)
{
    QmlJSEditor::Internal::QmlJSTextEditorWidget *pQMLJSTextEdit = qobject_cast<QmlJSEditor::Internal::QmlJSTextEditorWidget *>(pTextEdit);
    if(pQMLJSTextEdit)
    {
        pQMLJSTextEdit->gotoLine(lineNumber);
    }
}
QWidget *JsEditorToolsLib::getFindDialog()
{
    return m_pDetachedFindWindow;
}
void JsEditorToolsLib::onTextEditorFocused()
{
    QmlJSEditor::Internal::QmlJSTextEditorWidget *pQMLJSTextEdit = qobject_cast<QmlJSEditor::Internal::QmlJSTextEditorWidget *>(sender());
    if(pQMLJSTextEdit)
    {
        foreach (Core::IEditor *pEditor, m_pDetatchedEditors) {
            if(pEditor->document() == pQMLJSTextEdit->qmlJsEditorDocument())
            {
                Core::EditorManager::setCurrentEditorWithEditorViewIgnored(pEditor);
                break;
            }
        }
    }
}
void JsEditorToolsLib::removeEditor(QPlainTextEdit *pTextEdit)
{
    QmlJSEditor::Internal::QmlJSTextEditorWidget *pQMLJSTextEdit = qobject_cast<QmlJSEditor::Internal::QmlJSTextEditorWidget *>(pTextEdit);
    if(pQMLJSTextEdit)
    {
        foreach (Core::IEditor *pEditor, m_pDetatchedEditors) {
            if(pEditor->document() == pQMLJSTextEdit->qmlJsEditorDocument())
            {
                m_pDetatchedEditors.removeAll(pEditor);
                Core::EditorManager::closeEditor(pEditor, false);
                break;
            }
        }
    }

    if(m_pDetatchedEditors.count() == 0)
    {
        m_pDetachedFindWindow->hide();
        emit hideFindDialog();
    }
}
QString JsEditorToolsLib::getTextWithNewLine(QPlainTextEdit *pTextEdit)
{
    QString ret;
    QmlJSEditor::Internal::QmlJSTextEditorWidget *pQMLJSTextEdit = qobject_cast<QmlJSEditor::Internal::QmlJSTextEditorWidget *>(pTextEdit);
    if(pQMLJSTextEdit)
    {
        QString txt = pQMLJSTextEdit->toPlainText();
        ret = txt;
        QChar *uc = ret.data();
        QChar *e = uc + ret.size();

        for (; uc != e; ++uc) {
            switch (uc->unicode()) {
            case 0xfdd0: // QTextBeginningOfFrame
            case 0xfdd1: // QTextEndOfFrame
            case QChar::ParagraphSeparator:
            case QChar::LineSeparator:
                *uc = QLatin1Char('\n');
                break;
            case QChar::Nbsp:
                *uc = QLatin1Char(' ');
                break;
            default:
                ;
            }
        }
    }
    return ret;
}
void JsEditorToolsLib::showGoToLineDialog()
{
    bool ok;
    QmlJSEditor::Internal::QmlJSTextEditorWidget *pQMLJSTextEdit = qobject_cast<QmlJSEditor::Internal::QmlJSTextEditorWidget *>(Core::EditorManager::currentEditor()->widget());
    if(pQMLJSTextEdit)
    {
        QTextBlock block = pQMLJSTextEdit->textCursor().block();
        QWidget *pParent = qobject_cast<QWidget *>(m_pDummyMainWidget->parent());
        int nLineNumber = QInputDialog::getInt(pParent, QLatin1String("Go To Line:"),
                                      QLatin1String("Line Number:"), block.fragmentIndex(), 0, pQMLJSTextEdit->blockCount(), 1, &ok);
        if (ok)
        {
            foreach (Core::IEditor *pEditor, m_pDetatchedEditors) {
                if(pEditor->document() == pQMLJSTextEdit->qmlJsEditorDocument())
                {
                    emit searchResultItemSelected(pEditor->document()->filePath(), nLineNumber);
                    break;
                }
            }
        }
    }
}
bool JsEditorToolsLib::showOptionsDialog()
{
    QWidget *pParent = qobject_cast<QWidget *>(m_pDummyMainWidget->parent());
    Core::Internal::SettingsDialog *dialog = Core::Internal::SettingsDialog::getSettingsDialog(pParent, Core::Id(), Core::Id());
    return dialog->execDialog();
}
////////////////////////////////////////ADDITIONAL SLOTS ADDED BY ROOPAK/////////#720 ROOPAK

//static JsEditorTools::JsEditorToolsLib *globalObject = NULL;

////non-class function to return pointer to class
//extern "C" Q_DECL_EXPORT JsEditorTools::JsEditorToolsLib* create(QWidget *pWidget)
//{
//    if(globalObject == NULL) {
//        globalObject = new JsEditorTools::JsEditorToolsLib(pWidget);
//    }
//   return globalObject;
//}

//extern "C" Q_DECL_EXPORT QMenu* getMenu(QString strMenuName)
//{
//    if(strMenuName.compare(QLatin1String("File")) == 0)
//        return globalObject->getJSEditorMenuItems()->getFileMenu();
//    else if(strMenuName.compare(QLatin1String("Edit")) == 0)
//        return globalObject->getJSEditorMenuItems()->getEditMenu();
//    else if(strMenuName.compare(QLatin1String("Tools")) == 0)
//        return globalObject->getJSEditorMenuItems()->getToolsMenu();
//    else if(strMenuName.compare(QLatin1String("Window")) == 0)
//        return globalObject->getJSEditorMenuItems()->getWindowMenu();
//    else
//        return NULL;
//}

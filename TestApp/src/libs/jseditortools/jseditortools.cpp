#include "jseditortools.h"
#include <jseditortools/coreplugin/coreplugin.h>
#include <jseditortools/coreplugin/documentmanager.h>
#include <jseditortools/texteditor/texteditorplugin.h>
#include <jseditortools/qmljstools/qmljstoolsplugin.h>
#include <jseditortools/qmljseditor/qmljseditorplugin.h>
#include <extensionsystem/pluginmanager.h>
//#include <app/app_version.h>//#720 - ROOPAK
#include <jseditortools/jseditormenuitems.h>

#include <QStringList>
#include <QSettings>
#include <QFileInfo>
#include <QDir>

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

JsEditorToolsLib::JsEditorToolsLib(QWidget *mainWindow)
{
    m_MainWindow = NULL;
    setParentWidget(mainWindow);
}
void JsEditorToolsLib::setParentWidget(QWidget *mainWindow)
{
    if(m_MainWindow== NULL && mainWindow)
    {
        m_MainWindow = mainWindow;
        
        QString err;
        QStringList arguments;
    
        QSettings *settings = userSettings();
        QSettings *globalSettings = new QSettings(QSettings::IniFormat, QSettings::SystemScope,
                                                  QLatin1String(Core::Constants::IDE_SETTINGSVARIANT_STR),
                                                  QLatin1String(Core::Constants::IDE_APPNAME_STR));
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
    
        m_pCorePlugin->extensionsInitialized();//this should be called only in the final step(after the other plugins are loaded).
    
        m_pJSEditorMenuItems = new JSEditorMenuItems(this);
    }
}

void JsEditorToolsLib::setCustomBuiltinTypes(QMap<JsEditorTools::JSCustomBuiltinKey, QObject *> oCustomClassTypesList)
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

////////////////////////////////////////ADDITIONAL SLOTS ADDED BY ROOPAK/////////#720 ROOPAK

static JsEditorTools::JsEditorToolsLib *globalObject = NULL;

//non-class function to return pointer to class
extern "C" Q_DECL_EXPORT JsEditorTools::JsEditorToolsLib* create(QWidget *pWidget)
{
    if(globalObject == NULL) {
        globalObject = new JsEditorTools::JsEditorToolsLib(pWidget);
    }
   return globalObject;
}

extern "C" Q_DECL_EXPORT QMenu* getMenu(QString strMenuName)
{
    if(strMenuName.compare(QLatin1String("File")) == 0)
        return globalObject->getJSEditorMenuItems()->getFileMenu();
    else if(strMenuName.compare(QLatin1String("Edit")) == 0)
        return globalObject->getJSEditorMenuItems()->getEditMenu();
    else if(strMenuName.compare(QLatin1String("Tools")) == 0)
        return globalObject->getJSEditorMenuItems()->getToolsMenu();
    else if(strMenuName.compare(QLatin1String("Window")) == 0)
        return globalObject->getJSEditorMenuItems()->getWindowMenu();
    else
        return NULL;
}

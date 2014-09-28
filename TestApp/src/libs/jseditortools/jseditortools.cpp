#include "jseditortools.h"
#include <jseditortools/coreplugin/coreplugin.h>
#include <jseditortools/texteditor/texteditorplugin.h>

#include <QStringList>

using namespace JsEditorTools;

JsEditorToolsLib::JsEditorToolsLib(QMainWindow *mainWindow)
{
    m_MainWindow = mainWindow;

    QString err;
    QStringList arguments;

    m_pCorePlugin = new Core::Internal::CorePlugin(m_MainWindow);
    m_pCorePlugin->initialize(arguments, &err);
    m_pCorePlugin->extensionsInitialized();

    m_pTextEditorPlugin = new TextEditor::Internal::TextEditorPlugin();
    m_pTextEditorPlugin->initialize(arguments, &err);
    m_pTextEditorPlugin->extensionsInitialized();
}
JsEditorToolsLib::~JsEditorToolsLib()
{
    if(m_pCorePlugin)
        delete m_pCorePlugin;
    m_pCorePlugin = 0;

    if(m_pTextEditorPlugin)
        delete m_pTextEditorPlugin;
    m_pTextEditorPlugin = 0;
}

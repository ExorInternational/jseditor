#include "jseditortools.h"
#include <jseditortools/coreplugin/coreplugin.h>
#include <jseditortools/texteditor/texteditorplugin.h>

using namespace JsEditorTools;

JsEditorToolsLib::JsEditorToolsLib(QMainWindow *mainWindow)
{
    m_MainWindow = mainWindow;
    m_pCorePlugin = new Core::Internal::CorePlugin(m_MainWindow);
    m_pTextEditorPlugin = new TextEditor::Internal::TextEditorPlugin();
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

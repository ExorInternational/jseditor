#include "jseditortools.h"
#include <jseditortools/coreplugin/coreplugin.h>

using namespace JsEditorTools;

JsEditorToolsLib::JsEditorToolsLib(QMainWindow *mainWindow)
{
    m_MainWindow = mainWindow;
    m_pCorePlugin = new Core::Internal::CorePlugin(m_MainWindow);
}
JsEditorToolsLib::~JsEditorToolsLib()
{
    if(m_pCorePlugin)
        delete m_pCorePlugin;
    m_pCorePlugin = 0;
}

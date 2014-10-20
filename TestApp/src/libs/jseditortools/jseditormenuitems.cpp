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

#include <QFileDialog>

using namespace JsEditorTools;
using namespace Core;
using namespace ExtensionSystem;

JSEditorMenuItems::JSEditorMenuItems(QObject *parent) :
    QObject(parent)
{
    createActionGroups();
}

void JSEditorMenuItems::createActionGroups()
{

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

#ifndef JSEDITORMENUITEMS_H
#define JSEDITORMENUITEMS_H

#include <coreplugin/icore.h>

#include <QObject>
#include <QActionGroup>

namespace Core {
class IDocument;
}

namespace JsEditorTools {

class JSEditorMenuItems : public QObject
{
    Q_OBJECT
public:
    explicit JSEditorMenuItems(QObject *parent = 0);

    QActionGroup *getFileMenuItems(){ return m_pFileMenuActions; }
signals:

public slots:
    void newFileInEditor();
    void openFileInEditor();
    void saveAll();

private:
    void createFileMenuItems();
    Core::IDocument *openFiles(const QStringList &fileNames, Core::ICore::OpenFilesFlags flags);

    //Menu groups
    void createActionGroups();
    QActionGroup *m_pFileMenuActions;

};

}// namespace JsEditorTools

#endif // JSEDITORMENUITEMS_H

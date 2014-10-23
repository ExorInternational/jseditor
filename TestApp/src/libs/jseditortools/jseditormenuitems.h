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

    QMenu *getFileMenu(){ return m_pFileMenu; }
    QMenu *getEditMenu(){ return m_pEditMenu; }
signals:

public slots:
    void newFileInEditor();
    void openFileInEditor();
    void saveAll();

private:
    Core::IDocument *openFiles(const QStringList &fileNames, Core::ICore::OpenFilesFlags flags);

    //Menu groups
    void createActionGroups();

    void createFileMenuItems();
    QMenu *m_pFileMenu;

    void createEditMenuItems();
    QMenu *m_pEditMenu;
    void createEditAdvancedMenu();
    QMenu *m_pEditAdvancedMenu;
};

}// namespace JsEditorTools

#endif // JSEDITORMENUITEMS_H

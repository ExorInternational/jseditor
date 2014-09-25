/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "icontext.h"
#include "icore.h"

#include <utils/appmainwindow.h>

#include <QMap>
#include <QColor>

QT_BEGIN_NAMESPACE
class QSettings;
class QShortcut;
class QPrinter;
class QToolButton;
QT_END_NAMESPACE

namespace Core {

class ActionManager;
//class StatusBarWidget;//#720 ROOPAK
class EditorManager;
//class ExternalToolManager;//ROOPAK
class DocumentManager;
//class HelpManager;//#720 ROOPAK
class IDocument;
//class IWizard;//#720 ROOPAK
class MessageManager;
class MimeDatabase;
class ModeManager;
class ProgressManager;
//class NavigationWidget;//#720 ROOPAK
class RightPaneWidget;
class SettingsDatabase;
class VariableManager;
//class VcsManager;//#720 ROOPAK

namespace Internal {

class ActionManagerPrivate;
class FancyTabWidget;
//class GeneralSettings;//ROOPAK
class ProgressManagerPrivate;
//class ShortcutSettings;//ROOPAK
//class ToolSettings;//ROOPAK
//class MimeTypeSettings;//ROOPAK
//class StatusBarManager;//#720 ROOPAK
//class VersionDialog;//#720 ROOPAK
//class SystemEditor;//ROOPAK

class MainWindow : public Utils::AppMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *mainWindow);
    ~MainWindow();

    bool init(QString *errorMessage);
    void extensionsInitialized();
    void aboutToShutdown();

    IContext *contextObject(QWidget *widget);
    void addContextObject(IContext *contex);
    void removeContextObject(IContext *contex);

    Core::IDocument *openFiles(const QStringList &fileNames, ICore::OpenFilesFlags flags);

    inline SettingsDatabase *settingsDatabase() const { return m_settingsDatabase; }
    virtual QPrinter *printer() const;
    IContext * currentContextObject() const;
//    QStatusBar *statusBar() const;//#720 ROOPAK

    void updateAdditionalContexts(const Context &remove, const Context &add);

    void setSuppressNavigationWidget(bool suppress);

    void setOverrideColor(const QColor &color);

    void setIsFullScreen(bool fullScreen);
signals:
    void windowActivated();

public slots:
//    void newFile();//ROOPAK
//    void openFileWith();//#720 ROOPAK
    void exit();
    void setFullScreen(bool on);

//    void showNewItemDialog(const QString &title,//#720 ROOPAK - START
//                           const QList<IWizard *> &wizards,
//                           const QString &defaultLocation = QString(),
//                           const QVariantMap &extraVariables = QVariantMap());//#720 ROOPAK - END

    bool showOptionsDialog(Id category = Id(), Id page = Id(), QWidget *parent = 0);

    bool showWarningWithOptions(const QString &title, const QString &text,
                                const QString &details = QString(),
                                Id settingsCategory = Id(),
                                Id settingsId = Id(),
                                QWidget *parent = 0);

protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);

private slots:
    void openFile();
//    void aboutToShowRecentFiles();//#720 ROOPAK
//    void openRecentFile();//#720 ROOPAK
    void setFocusToEditor();
    void saveAll();
//    void aboutQtCreator();//#720 ROOPAK
    void aboutPlugins();
    void updateFocusWidget(QWidget *old, QWidget *now);
    void setSidebarVisible(bool visible);
//    void destroyVersionDialog();//#720 ROOPAK
    void openDelayedFiles();
    void restoreWindowState();

private:
    void updateContextObject(const QList<IContext *> &context);
    void updateContext();

    void registerDefaultContainers();
    void registerDefaultActions();

    void readSettings();
    void writeSettings();

    ICore *m_coreImpl;
    Context m_additionalContexts;
    SettingsDatabase *m_settingsDatabase;
    mutable QPrinter *m_printer;
    ActionManager *m_actionManager;
    EditorManager *m_editorManager;
//    ExternalToolManager *m_externalToolManager;//ROOPAK
    MessageManager *m_messageManager;
    ProgressManagerPrivate *m_progressManager;
    VariableManager *m_variableManager;
//    VcsManager *m_vcsManager;//#720 ROOPAK
//    StatusBarManager *m_statusBarManager;//#720 ROOPAK
    ModeManager *m_modeManager;
    MimeDatabase *m_mimeDatabase;
//    HelpManager *m_helpManager;//#720 ROOPAK
    FancyTabWidget *m_modeStack;
//    NavigationWidget *m_navigationWidget;//#720 ROOPAK
    RightPaneWidget *m_rightPaneWidget;
//    Core::StatusBarWidget *m_outputView;//#720 ROOPAK
//    VersionDialog *m_versionDialog;//#720 ROOPAK

    QList<IContext *> m_activeContext;

    QMap<QWidget *, IContext *> m_contextWidgets;

//    GeneralSettings *m_generalSettings;//ROOPAK
//    ShortcutSettings *m_shortcutSettings;//ROOPAK
//    ToolSettings *m_toolSettings;//ROOPAK
//    MimeTypeSettings *m_mimeTypeSettings;//ROOPAK
//    SystemEditor *m_systemEditor;//ROOPAK

    // actions
    QShortcut *m_focusToEditor;
//    QAction *m_newAction;//ROOPAK
    QAction *m_openAction;
//    QAction *m_openWithAction;//#720 ROOPAK
    QAction *m_saveAllAction;
    QAction *m_exitAction;
    QAction *m_optionsAction;
    QAction *m_toggleSideBarAction;
    QAction *m_toggleModeSelectorAction;
    QAction *m_toggleFullScreenAction;
    QAction *m_minimizeAction;
    QAction *m_zoomAction;

    QToolButton *m_toggleSideBarButton;
    QColor m_overrideColor;

    QStringList m_filesToOpenDelayed;
};

} // namespace Internal
} // namespace Core

#endif // MAINWINDOW_H

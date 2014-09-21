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

#ifndef QMLJSTOOLS_H
#define QMLJSTOOLS_H

#include <coreplugin/id.h>
#include <extensionsystem/iplugin.h>

QT_BEGIN_NAMESPACE
class QFileInfo;
class QDir;
class QAction;
QT_END_NAMESPACE

namespace QmlJSTools {

class QmlJSToolsSettings;
//class QmlConsoleManager;//#720 ROOPAK

namespace Internal {

class ModelManager;

class QmlJSToolsPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QmlJSTools.json")

public:
    static QmlJSToolsPlugin *instance() { return m_instance; }

    QmlJSToolsPlugin();
    ~QmlJSToolsPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();
    ModelManager *modelManager() { return m_modelManager; }

private slots:
    void onTaskStarted(Core::Id type);
    void onAllTasksFinished(Core::Id type);

#ifdef WITH_TESTS
    void test_basic();
#endif

private:
    ModelManager *m_modelManager;
//    QmlConsoleManager *m_consoleManager;//#720 ROOPAK
    QmlJSToolsSettings *m_settings;
    QAction *m_resetCodeModelAction;

    static QmlJSToolsPlugin *m_instance;
};

} // namespace Internal
} // namespace CppTools

#endif // QMLJSTOOLS_H

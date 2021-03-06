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

#ifndef DEBUGGER_COREGDBADAPTER_H
#define DEBUGGER_COREGDBADAPTER_H

#include "gdbengine.h"

#include <QFile>

namespace Debugger {
namespace Internal {

///////////////////////////////////////////////////////////////////////
//
// CoreGdbAdapter
//
///////////////////////////////////////////////////////////////////////

QString readExecutableNameFromCore(const QString &cmd, const QString &coreFile, bool *isCore);

class GdbCoreEngine : public GdbEngine
{
    Q_OBJECT

public:
    explicit GdbCoreEngine(const DebuggerStartParameters &startParameters);
    ~GdbCoreEngine();

private:
    void setupEngine();
    void setupInferior();
    void runEngine();
    void interruptInferior();
    void shutdownEngine();

    void handleFileExecAndSymbols(const GdbResponse &response);
    void handleTargetCore(const GdbResponse &response);
    void handleRoundTrip(const GdbResponse &response);
    void unpackCoreIfNeeded();
    QString coreFileName() const;
    QString coreName() const;

private slots:
    void continueSetupEngine();
    void writeCoreChunk();

private:
    QString m_executable;
    QString m_coreName;
    QString m_tempCoreName;
    QProcess *m_coreUnpackProcess;
    QFile m_tempCoreFile;
};

} // namespace Internal
} // namespace Debugger

#endif // DEBUGGER_COREDBADAPTER_H

/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Build Suite.
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
#ifndef QBS_FUZZYTESTER_H
#define QBS_FUZZYTESTER_H

#include <QString>

#include <exception>

QT_BEGIN_NAMESPACE
class QStringList;
QT_END_NAMESPACE

class TestError {
public:
    TestError(const QString &errorMessage) : errorMessage(errorMessage) {}
    ~TestError() throw() {}

    QString errorMessage;

private:
    const char *what() const throw() { return qPrintable(errorMessage); }
};


class FuzzyTester
{
public:
    FuzzyTester();

    void runTest(const QString &profile, const QString &startCommit);

private:
    void checkoutCommit(const QString &commit);
    QStringList findAllCommits(const QString &startCommit);
    QString findWorkingStartCommit(const QString &startCommit);
    void runGit(const QStringList &arguments, QString *output = 0);
    bool runQbs(const QString &buildDir, const QString &command, QString *errorOutput = 0);
    void removeDir(const QString &dir);
    bool doCleanBuild(QString *errorMessage = 0);
    void throwIncrementalBuildError(const QString &message, const QStringList &commitSequence);

    static QString defaultBuildDir();

    QString m_profile;
    QString m_headCommit;
};

#endif // Include guard.

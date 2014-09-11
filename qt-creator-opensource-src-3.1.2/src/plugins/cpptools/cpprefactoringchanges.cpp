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

#include "cpprefactoringchanges.h"

#include "cppqtstyleindenter.h"
#include "cppcodeformatter.h"
//#include "cppmodelmanager.h"//#720 ROOPAK
//#include <projectexplorer/editorconfiguration.h>//#720 ROOPAK

//#720 ADDED BY ROOPAK - START
#include <texteditor/tabsettings.h>
#include <QTextDocument>
#include <QTextCursor>
//#720 ROOPAK - END

#include <utils/qtcassert.h>

using namespace CPlusPlus;
using namespace CppTools;
using namespace Utils;

class CppTools::CppRefactoringChangesData : public TextEditor::RefactoringChangesData
{
public:
    CppRefactoringChangesData(const Snapshot &snapshot)
        : m_snapshot(snapshot)
        , m_modelManager(/*Internal::CppModelManager*/CppModelManagerInterface::instance())//#720 ROOPAK
        , m_workingCopy(m_modelManager->workingCopy())
    {}

    virtual void indentSelection(const QTextCursor &selection,
                                 const QString &fileName,
                                 const TextEditor::BaseTextDocument *textDocument) const
    {
//        const TextEditor::TabSettings &tabSettings =                          //#720 ROOPAK - START
//            ProjectExplorer::actualTabSettings(fileName, textDocument);

//        CppQtStyleIndenter indenter;
//        indenter.indent(selection.document(), selection, QChar::Null, tabSettings);//#720 ROOPAK - END
    }

    virtual void reindentSelection(const QTextCursor &selection,
                                   const QString &fileName,
                                   const TextEditor::BaseTextDocument *textDocument) const
    {
//        const TextEditor::TabSettings &tabSettings =                  //#720 ROOPAK - START
//            ProjectExplorer::actualTabSettings(fileName, textDocument);

//        CppQtStyleIndenter indenter;
//        indenter.reindent(selection.document(), selection, tabSettings);//#720 ROOPAK - END
    }

    virtual void fileChanged(const QString &fileName)
    {
        m_modelManager->updateSourceFiles(QStringList(fileName));
    }

    Snapshot m_snapshot;
    CppModelManagerInterface *m_modelManager;
    CppModelManagerInterface::WorkingCopy m_workingCopy;

};

CppRefactoringChanges::CppRefactoringChanges(const Snapshot &snapshot)
    : RefactoringChanges(new CppRefactoringChangesData(snapshot))
{
}

CppRefactoringChangesData *CppRefactoringChanges::data() const
{
    return static_cast<CppRefactoringChangesData *>(m_data.data());
}

CppRefactoringFilePtr CppRefactoringChanges::file(TextEditor::BaseTextEditorWidget *editor, const Document::Ptr &document)
{
    CppRefactoringFilePtr result(new CppRefactoringFile(editor));
    result->setCppDocument(document);
    return result;
}

CppRefactoringFilePtr CppRefactoringChanges::file(const QString &fileName) const
{
    CppRefactoringFilePtr result(new CppRefactoringFile(fileName, m_data));
    return result;
}

CppRefactoringFileConstPtr CppRefactoringChanges::fileNoEditor(const QString &fileName) const
{
    QTextDocument *document = 0;
    if (data()->m_workingCopy.contains(fileName))
        document = new QTextDocument(QString::fromUtf8(data()->m_workingCopy.source(fileName)));
    CppRefactoringFilePtr result(new CppRefactoringFile(document, fileName));
    result->m_data = m_data;

    Document::Ptr cppDocument = data()->m_snapshot.document(fileName);
    if (cppDocument)
        result->setCppDocument(cppDocument);

    return result;
}

const Snapshot &CppRefactoringChanges::snapshot() const
{
    return data()->m_snapshot;
}

CppRefactoringFile::CppRefactoringFile(const QString &fileName, const QSharedPointer<TextEditor::RefactoringChangesData> &data)
    : RefactoringFile(fileName, data)
{
    const Snapshot &snapshot = this->data()->m_snapshot;
    m_cppDocument = snapshot.document(fileName);
}

CppRefactoringFile::CppRefactoringFile(QTextDocument *document, const QString &fileName)
    : RefactoringFile(document, fileName)
{ }

CppRefactoringFile::CppRefactoringFile(TextEditor::BaseTextEditorWidget *editor)
    : RefactoringFile(editor)
{ }

Document::Ptr CppRefactoringFile::cppDocument() const
{
    if (!m_cppDocument || !m_cppDocument->translationUnit() ||
            !m_cppDocument->translationUnit()->ast()) {
        const QByteArray source = document()->toPlainText().toUtf8();
        const QString name = fileName();
        const Snapshot &snapshot = data()->m_snapshot;

        m_cppDocument = snapshot.preprocessedDocument(source, name);
        m_cppDocument->check();
    }

    return m_cppDocument;
}

void CppRefactoringFile::setCppDocument(Document::Ptr document)
{
    m_cppDocument = document;
}

Scope *CppRefactoringFile::scopeAt(unsigned index) const
{
    unsigned line, column;
    cppDocument()->translationUnit()->getTokenStartPosition(index, &line, &column);
    return cppDocument()->scopeAt(line, column);
}

bool CppRefactoringFile::isCursorOn(unsigned tokenIndex) const
{
    QTextCursor tc = cursor();
    int cursorBegin = tc.selectionStart();

    int start = startOf(tokenIndex);
    int end = endOf(tokenIndex);

    if (cursorBegin >= start && cursorBegin <= end)
        return true;

    return false;
}

bool CppRefactoringFile::isCursorOn(const AST *ast) const
{
    QTextCursor tc = cursor();
    int cursorBegin = tc.selectionStart();

    int start = startOf(ast);
    int end = endOf(ast);

    if (cursorBegin >= start && cursorBegin <= end)
        return true;

    return false;
}

ChangeSet::Range CppRefactoringFile::range(unsigned tokenIndex) const
{
    const Token &token = tokenAt(tokenIndex);
    unsigned line, column;
    cppDocument()->translationUnit()->getPosition(token.begin(), &line, &column);
    const int start = document()->findBlockByNumber(line - 1).position() + column - 1;
    return ChangeSet::Range(start, start + token.length());
}

ChangeSet::Range CppRefactoringFile::range(AST *ast) const
{
    return ChangeSet::Range(startOf(ast), endOf(ast));
}

int CppRefactoringFile::startOf(unsigned index) const
{
    unsigned line, column;
    cppDocument()->translationUnit()->getPosition(tokenAt(index).begin(), &line, &column);
    return document()->findBlockByNumber(line - 1).position() + column - 1;
}

int CppRefactoringFile::startOf(const AST *ast) const
{
    return startOf(ast->firstToken());
}

int CppRefactoringFile::endOf(unsigned index) const
{
    unsigned line, column;
    cppDocument()->translationUnit()->getPosition(tokenAt(index).end(), &line, &column);
    return document()->findBlockByNumber(line - 1).position() + column - 1;
}

int CppRefactoringFile::endOf(const AST *ast) const
{
    unsigned end = ast->lastToken();
    QTC_ASSERT(end > 0, return -1);
    return endOf(end - 1);
}

void CppRefactoringFile::startAndEndOf(unsigned index, int *start, int *end) const
{
    unsigned line, column;
    Token token(tokenAt(index));
    cppDocument()->translationUnit()->getPosition(token.begin(), &line, &column);
    *start = document()->findBlockByNumber(line - 1).position() + column - 1;
    *end = *start + token.length();
}

QString CppRefactoringFile::textOf(const AST *ast) const
{
    return textOf(startOf(ast), endOf(ast));
}

const Token &CppRefactoringFile::tokenAt(unsigned index) const
{
    return cppDocument()->translationUnit()->tokenAt(index);
}

CppRefactoringChangesData *CppRefactoringFile::data() const
{
    return static_cast<CppRefactoringChangesData *>(m_data.data());
}

void CppRefactoringFile::fileChanged()
{
    m_cppDocument.clear();
    RefactoringFile::fileChanged();
}

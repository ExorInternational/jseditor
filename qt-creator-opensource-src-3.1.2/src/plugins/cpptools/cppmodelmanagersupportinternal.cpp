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

//#include "cppcompletionassist.h"//#720 ROOPAK
//#include "cpphighlightingsupportinternal.h"//#720 ROOPAK
#include "cppmodelmanagersupportinternal.h"

#include <QCoreApplication>

using namespace CppTools;
using namespace CppTools::Internal;

ModelManagerSupportInternal::ModelManagerSupportInternal()
//    : m_completionAssistProvider(new InternalCompletionAssistProvider)//#720 ROOPAK
{
}

ModelManagerSupportInternal::~ModelManagerSupportInternal()
{
}

QString ModelManagerSupportInternal::id() const
{
    return QLatin1String("CppTools.BuiltinCodeModel");
}

QString ModelManagerSupportInternal::displayName() const
{
    return QCoreApplication::translate("ModelManagerSupportInternal::displayName",
                                       "Qt Creator Built-in");
}

//CppCompletionAssistProvider *ModelManagerSupportInternal::completionAssistProvider()//#720 ROOPAK - START
//{
//    return NULL;//m_completionAssistProvider.data();//#720 ROOPAK
//}//#720 ROOPAK - END

//CppHighlightingSupport *ModelManagerSupportInternal::highlightingSupport(TextEditor::ITextEditor *editor)//#720 ROOPAK - START
//{
//    return new CppHighlightingSupportInternal(editor);
//}//#720 ROOPAK - END

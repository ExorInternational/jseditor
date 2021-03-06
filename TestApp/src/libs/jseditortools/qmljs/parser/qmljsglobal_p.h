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
#ifndef QMLJSGLOBAL_P_H
#define QMLJSGLOBAL_P_H

//#include <QtCore/qglobal.h>//#720 - ROOPAK START

//#ifdef QT_CREATOR
//#  define QT_QML_BEGIN_NAMESPACE
//#  define QT_QML_END_NAMESPACE

//#  ifdef QMLJS_BUILD_DIR
//#    define QML_PARSER_EXPORT Q_DECL_EXPORT
//#  elif QML_BUILD_STATIC_LIB
//#    define QML_PARSER_EXPORT
//#  else
//#    define QML_PARSER_EXPORT Q_DECL_IMPORT
//#  endif // QMLJS_BUILD_DIR

//#else // !QT_CREATOR//#720 - ROOPAK END
#  define QT_QML_BEGIN_NAMESPACE QT_BEGIN_NAMESPACE
#  define QT_QML_END_NAMESPACE QT_END_NAMESPACE
//#  if defined(QT_BUILD_QMLDEVTOOLS_LIB) || defined(QT_QMLDEVTOOLS_LIB)//#720 - ROOPAK START
//     // QmlDevTools is a static library
//#    define QML_PARSER_EXPORT
//#  elif defined(QT_BUILD_QML_LIB)
//#    define QML_PARSER_EXPORT Q_AUTOTEST_EXPORT
//#  else
//#    define QML_PARSER_EXPORT
//#  endif
//#endif // QT_CREATOR

#include <qmljs/../jseditortools_global.h>

#define QML_PARSER_EXPORT JSEDITORTOOLS_EXPORT//#720 - ROOPAK END

#endif // QMLJSGLOBAL_P_H

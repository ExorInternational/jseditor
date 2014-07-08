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

#ifndef QTC_FUNCTION_H
#define QTC_FUNCTION_H

#include <functional>
#if !(__cplusplus > 199711L || __GXX_EXPERIMENTAL_CXX0X__ || _MSC_VER >= 1600 || defined( _LIBCPP_VERSION )) || \
    (defined(__GNUC_LIBSTD__) && ((__GNUC_LIBSTD__-0) * 100 + __GNUC_LIBSTD_MINOR__-0 <= 402))
#define USE_TR1
#endif

#ifdef USE_TR1
#  ifdef __GNUC__
#    include <tr1/functional>
#  endif
namespace Utils { using std::tr1::function; }
#else
namespace Utils { using std::function; }
#endif

#endif // QTC_FUNCTION_H

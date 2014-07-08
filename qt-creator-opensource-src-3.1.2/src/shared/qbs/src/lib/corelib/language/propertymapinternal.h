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

#ifndef QBS_PROPERTYMAPINTERNAL_H
#define QBS_PROPERTYMAPINTERNAL_H

#include "forward_decls.h"
#include <tools/persistentobject.h>
#include <QVariantMap>

namespace qbs {
namespace Internal {

class PropertyMapInternal : public PersistentObject
{
public:
    static PropertyMapPtr create() { return PropertyMapPtr(new PropertyMapInternal); }
    PropertyMapPtr clone() const { return PropertyMapPtr(new PropertyMapInternal(*this)); }

    const QVariantMap &value() const { return m_value; }
    QVariant qbsPropertyValue(const QString &key) const; // Convenience function.
    void setValue(const QVariantMap &value);
    QString toJSLiteral() const;

private:
    PropertyMapInternal();
    PropertyMapInternal(const PropertyMapInternal &other);

    void load(PersistentPool &);
    void store(PersistentPool &) const;

    QVariantMap m_value;
};

} // namespace Internal
} // namespace qbs

#endif // QBS_PROPERTYMAPINTERNAL_H

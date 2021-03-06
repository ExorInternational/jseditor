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

#ifndef QBS_PROPERTYDECLARATION_H
#define QBS_PROPERTYDECLARATION_H

#include <QSharedDataPointer>
#include <QString>
#include <QStringList>
#include <QScriptValue>

namespace qbs {
namespace Internal {

class PropertyDeclarationData;

class PropertyDeclaration
{
public:
    enum Type
    {
        UnknownType,
        Boolean,
        Integer,
        Path,
        PathList,
        String,
        StringList,
        Variant,
        Verbatim
    };

    enum Flag
    {
        DefaultFlags = 0,
        ListProperty = 0x1,
        PropertyNotAvailableInConfig = 0x2     // Is this property part of a project, product or file configuration?
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    PropertyDeclaration();
    PropertyDeclaration(const QString &name, Type type, Flags flags = DefaultFlags);
    PropertyDeclaration(const PropertyDeclaration &other);
    ~PropertyDeclaration();

    PropertyDeclaration &operator=(const PropertyDeclaration &other);

    bool isValid() const;

    static Type propertyTypeFromString(const QString &typeName);

    const QString &name() const;
    void setName(const QString &name);

    Type type() const;
    void setType(Type t);

    Flags flags() const;
    void setFlags(Flags f);

    const QScriptValue &allowedValues() const;
    void setAllowedValues(const QScriptValue &v);

    const QString &description() const;
    void setDescripton(const QString &str);

    const QString &initialValueSource() const;
    void setInitialValueSource(const QString &str);

    const QStringList &functionArgumentNames() const;
    void setFunctionArgumentNames(const QStringList &lst);

private:
    QSharedDataPointer<PropertyDeclarationData> d;
};

} // namespace Internal
} // namespace qbs

#endif // QBS_PROPERTYDECLARATION_H

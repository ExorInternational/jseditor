/**************************************************************************
**
** Copyright (c) 2014 Lorenz Haas
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

#ifndef BEAUTIFIER_UNCRUSTIFY_H
#define BEAUTIFIER_UNCRUSTIFY_H

#include "../beautifierabstracttool.h"

#include <utils/qtcoverride.h>

QT_FORWARD_DECLARE_CLASS(QAction)

namespace Beautifier {
namespace Internal {
namespace Uncrustify {

class UncrustifySettings;

class Uncrustify : public BeautifierAbstractTool
{
    Q_OBJECT

public:
    explicit Uncrustify(QObject *parent = 0);
    virtual ~Uncrustify();
    bool initialize() QTC_OVERRIDE;
    void updateActions(Core::IEditor *editor) QTC_OVERRIDE;
    QList<QObject *> autoReleaseObjects() QTC_OVERRIDE;

private slots:
    void formatFile();

private:
    QAction *m_formatFile;
    UncrustifySettings *m_settings;
};

} // namespace Uncrustify
} // namespace Internal
} // namespace Beautifier

#endif // BEAUTIFIER_UNCRUSTIFY_H

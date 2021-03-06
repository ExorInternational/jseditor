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

#include "cpptoolssettings.h"

#include "cpptoolsconstants.h"
//#include "cppcodestylepreferences.h"//#720 ROOPAK
//#include "cppcodestylepreferencesfactory.h"//#720 ROOPAK
//#include "commentssettings.h"//#720 ROOPAK
//#include "completionsettingspage.h"//#720 ROOPAK

#include <coreplugin/icore.h>
#include <texteditor/codestylepool.h>
#include <texteditor/tabsettings.h>
#include <texteditor/texteditorsettings.h>

#include <extensionsystem/pluginmanager.h>
#include <utils/qtcassert.h>
#include <utils/settingsutils.h>

#include <QSettings>

static const char idKey[] = "CppGlobal";

using namespace CppTools;
using namespace CppTools::Internal;
using namespace TextEditor;

namespace CppTools {
namespace Internal {

class CppToolsSettingsPrivate
{
public:
    CppToolsSettingsPrivate()
//        : m_globalCodeStyle(0)//#720 ROOPAK
//        , m_completionSettingsPage(0)//#720 ROOPAK
    {}

//    CppCodeStylePreferences *m_globalCodeStyle;//#720 ROOPAK
//    CompletionSettingsPage *m_completionSettingsPage;//#720 ROOPAK
};

} // namespace Internal
} // namespace CppTools

CppToolsSettings *CppToolsSettings::m_instance = 0;

CppToolsSettings::CppToolsSettings(QObject *parent)
    : QObject(parent)
    , d(new Internal::CppToolsSettingsPrivate)
{
    QTC_ASSERT(!m_instance, return);
    m_instance = this;

//    qRegisterMetaType<CppTools::CppCodeStyleSettings>("CppTools::CppCodeStyleSettings");//#720 ROOPAK

//    d->m_completionSettingsPage = new CompletionSettingsPage(this);//#720 ROOPAK - START
//    ExtensionSystem::PluginManager::addObject(d->m_completionSettingsPage);

//    connect(d->m_completionSettingsPage,
//            SIGNAL(commentsSettingsChanged(CppTools::CommentsSettings)),
//            this,
//            SIGNAL(commentsSettingsChanged(CppTools::CommentsSettings)));//#720 ROOPAK - END

    // code style factory
//    ICodeStylePreferencesFactory *factory = new CppTools::CppCodeStylePreferencesFactory();//#720 ROOPAK - START
//    TextEditorSettings::registerCodeStyleFactory(factory);

    // code style pool
//    CodeStylePool *pool = new CodeStylePool(factory, this);
//    TextEditorSettings::registerCodeStylePool(Constants::CPP_SETTINGS_ID, pool);//#720 ROOPAK - END

    // global code style settings
//    d->m_globalCodeStyle = new CppCodeStylePreferences(this);//#720 ROOPAK
//    d->m_globalCodeStyle->setDelegatingPool(pool);//#720 ROOPAK
//    d->m_globalCodeStyle->setDisplayName(tr("Global", "Settings"));//#720 ROOPAK - START
//    d->m_globalCodeStyle->setId(idKey);//#720 ROOPAK - END
//    pool->addCodeStyle(d->m_globalCodeStyle);//#720 ROOPAK
//    TextEditorSettings::registerCodeStyle(CppTools::Constants::CPP_SETTINGS_ID, d->m_globalCodeStyle);//#720 ROOPAK

    /*
    For every language we have exactly 1 pool. The pool contains:
    1) All built-in code styles (Qt/GNU)
    2) All custom code styles (which will be added dynamically)
    3) A global code style

    If the code style gets a pool (setCodeStylePool()) it means it can behave
    like a proxy to one of the code styles from that pool
    (ICodeStylePreferences::setCurrentDelegate()).
    That's why the global code style gets a pool (it can point to any code style
    from the pool), while built-in and custom code styles don't get a pool
    (they can't point to any other code style).

    The instance of the language pool is shared. The same instance of the pool
    is used for all project code style settings and for global one.
    Project code style can point to one of built-in or custom code styles
    or to the global one as well. That's why the global code style is added
    to the pool. The proxy chain can look like:
    ProjectCodeStyle -> GlobalCodeStyle -> BuildInCodeStyle (e.g. Qt).

    With the global pool there is an exception - it gets a pool
    in which it exists itself. The case in which a code style point to itself
    is disallowed and is handled in ICodeStylePreferences::setCurrentDelegate().
    */

    // built-in settings
    // Qt style
//    CppCodeStylePreferences *qtCodeStyle = new CppCodeStylePreferences();//#720 ROOPAK - START
//    qtCodeStyle->setId("qt");
//    qtCodeStyle->setDisplayName(tr("Qt"));
//    qtCodeStyle->setReadOnly(true);
//    TabSettings qtTabSettings;
//    qtTabSettings.m_tabPolicy = TabSettings::SpacesOnlyTabPolicy;
//    qtTabSettings.m_tabSize = 4;
//    qtTabSettings.m_indentSize = 4;
//    qtTabSettings.m_continuationAlignBehavior = TabSettings::ContinuationAlignWithIndent;
//    qtCodeStyle->setTabSettings(qtTabSettings);//#720 ROOPAK - END
//    pool->addCodeStyle(qtCodeStyle);//#720 ROOPAK

    // GNU style
//    CppCodeStylePreferences *gnuCodeStyle = new CppCodeStylePreferences();//#720 ROOPAK - START
//    gnuCodeStyle->setId("gnu");
//    gnuCodeStyle->setDisplayName(tr("GNU"));
//    gnuCodeStyle->setReadOnly(true);
//    TabSettings gnuTabSettings;
//    gnuTabSettings.m_tabPolicy = TabSettings::MixedTabPolicy;
//    gnuTabSettings.m_tabSize = 8;
//    gnuTabSettings.m_indentSize = 2;
//    gnuTabSettings.m_continuationAlignBehavior = TabSettings::ContinuationAlignWithIndent;
//    gnuCodeStyle->setTabSettings(gnuTabSettings);
//    CppCodeStyleSettings gnuCodeStyleSettings;
//    gnuCodeStyleSettings.indentNamespaceBody = true;
//    gnuCodeStyleSettings.indentBlockBraces = true;
//    gnuCodeStyleSettings.indentSwitchLabels = true;
//    gnuCodeStyleSettings.indentBlocksRelativeToSwitchLabels = true;
//    gnuCodeStyle->setCodeStyleSettings(gnuCodeStyleSettings);//#720 ROOPAK - END
//    pool->addCodeStyle(gnuCodeStyle);//#720 ROOPAK

    // default delegate for global preferences
//    d->m_globalCodeStyle->setCurrentDelegate(qtCodeStyle);//#720 ROOPAK

//    pool->loadCustomCodeStyles();//#720 ROOPAK

    // load global settings (after built-in settings are added to the pool)
    QSettings *s = Core::ICore::settings();
//    d->m_globalCodeStyle->fromSettings(QLatin1String(CppTools::Constants::CPP_SETTINGS_ID), s);//#720 ROOPAK

    // legacy handling start (Qt Creator Version < 2.4)
    const bool legacyTransformed =
                s->value(QLatin1String("CppCodeStyleSettings/LegacyTransformed"), false).toBool();

    if (!legacyTransformed) {
        // creator 2.4 didn't mark yet the transformation (first run of creator 2.4)

        // we need to transform the settings only if at least one from
        // below settings was already written - otherwise we use
        // defaults like it would be the first run of creator 2.4 without stored settings
        const QStringList groups = s->childGroups();
        const bool needTransform = groups.contains(QLatin1String("textTabPreferences")) ||
                                   groups.contains(QLatin1String("CppTabPreferences")) ||
                                   groups.contains(QLatin1String("CppCodeStyleSettings"));
        if (needTransform) {
//            CppCodeStyleSettings legacyCodeStyleSettings;//#720 ROOPAK - START
//            if (groups.contains(QLatin1String("CppCodeStyleSettings"))) {
//                Utils::fromSettings(QLatin1String("CppCodeStyleSettings"),
//                                    QString(), s, &legacyCodeStyleSettings);
//            }//#720 ROOPAK - END

            const QString currentFallback = s->value(QLatin1String("CppTabPreferences/CurrentFallback")).toString();
            TabSettings legacyTabSettings;
            if (currentFallback == QLatin1String("CppGlobal")) {
                // no delegate, global overwritten
                Utils::fromSettings(QLatin1String("CppTabPreferences"),
                                    QString(), s, &legacyTabSettings);
            } else {
                // delegating to global
//                legacyTabSettings = TextEditorSettings::codeStyle()->currentTabSettings();//#720 ROOPAK
            }

            // create custom code style out of old settings
            QVariant v;
//            v.setValue(legacyCodeStyleSettings);//#720 ROOPAK
//            TextEditor::ICodeStylePreferences *oldCreator = pool->createCodeStyle(//#720 ROOPAK - START
//                     "legacy", legacyTabSettings, v, tr("Old Creator"));

            // change the current delegate and save
//            d->m_globalCodeStyle->setCurrentDelegate(oldCreator);//#720 ROOPAK - END
//            d->m_globalCodeStyle->toSettings(QLatin1String(CppTools::Constants::CPP_SETTINGS_ID), s);//#720 ROOPAK
        }
        // mark old settings as transformed
        s->setValue(QLatin1String("CppCodeStyleSettings/LegacyTransformed"), true);
        // legacy handling stop
    }


    // mimetypes to be handled
    TextEditorSettings::registerMimeTypeForLanguageId(Constants::C_SOURCE_MIMETYPE, Constants::CPP_SETTINGS_ID);
    TextEditorSettings::registerMimeTypeForLanguageId(Constants::C_HEADER_MIMETYPE, Constants::CPP_SETTINGS_ID);
    TextEditorSettings::registerMimeTypeForLanguageId(Constants::CPP_SOURCE_MIMETYPE, Constants::CPP_SETTINGS_ID);
    TextEditorSettings::registerMimeTypeForLanguageId(Constants::CPP_HEADER_MIMETYPE, Constants::CPP_SETTINGS_ID);
}

CppToolsSettings::~CppToolsSettings()
{
//    ExtensionSystem::PluginManager::removeObject(d->m_completionSettingsPage);//#720 ROOPAK

    TextEditorSettings::unregisterCodeStyle(Constants::CPP_SETTINGS_ID);
    TextEditorSettings::unregisterCodeStylePool(Constants::CPP_SETTINGS_ID);
    TextEditorSettings::unregisterCodeStyleFactory(Constants::CPP_SETTINGS_ID);

    delete d;

    m_instance = 0;
}

CppToolsSettings *CppToolsSettings::instance()
{
    return m_instance;
}

//CppCodeStylePreferences *CppToolsSettings::cppCodeStyle() const//#720 ROOPAK - START
//{
//    return d->m_globalCodeStyle;
//}//#720 ROOPAK - END

//const CommentsSettings &CppToolsSettings::commentsSettings() const//#720 ROOPAK - START
//{
//    return CppTools::CommentsSettings();//d->m_completionSettingsPage->commentsSettings();//#720 ROOPAK
//}//#720 ROOPAK - END

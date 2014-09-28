import qbs 1.0

import QtcPlugin

QtcPlugin {
    name: "QmlJSEditor"

    Depends { name: "Qt"; submodules: ["widgets", "script"] }
    Depends { name: "Aggregation" }
    Depends { name: "LanguageUtils" }
    Depends { name: "Utils" }
    Depends { name: "QmlEditorWidgets" }
    Depends { name: "QmlJS" }

    Depends { name: "Core" }
    Depends { name: "TextEditor" }
    Depends { name: "ProjectExplorer" }
    Depends { name: "QmlJSTools" }

    files: [
        "jsfilewizard.cpp",
        "jsfilewizard.h",
        "qmlexpressionundercursor.cpp",
        "qmlexpressionundercursor.h",
        "qmlfilewizard.cpp",
        "qmlfilewizard.h",
        "qmljsautocompleter.cpp",
        "qmljsautocompleter.h",
        "qmljscompletionassist.cpp",
        "qmljscompletionassist.h",
        "qmljscomponentfromobjectdef.cpp",
        "qmljscomponentfromobjectdef.h",
        "qmljscomponentnamedialog.cpp",
        "qmljscomponentnamedialog.h",
        "qmljscomponentnamedialog.ui",
        "qmljseditor.cpp",
        "qmljseditor.h",
        "qmljseditor.qrc",
        "qmljseditor_global.h",
        "qmljseditorconstants.h",
        "qmljseditordocument.cpp",
        "qmljseditordocument.h",
        "qmljseditordocument_p.h",
        "qmljseditoreditable.cpp",
        "qmljseditoreditable.h",
        "qmljseditorfactory.cpp",
        "qmljseditorfactory.h",
        "qmljseditorplugin.cpp",
        "qmljseditorplugin.h",
        "qmljsfindreferences.cpp",
        "qmljsfindreferences.h",
        "qmljshighlighter.cpp",
        "qmljshighlighter.h",
        "qmljshighlighterfactory.cpp",
        "qmljshighlighterfactory.h",
        "qmljshoverhandler.cpp",
        "qmljshoverhandler.h",
        "qmljsoutline.cpp",
        "qmljsoutline.h",
        "qmljsoutlinetreeview.cpp",
        "qmljsoutlinetreeview.h",
        "qmljspreviewrunner.cpp",
        "qmljspreviewrunner.h",
        "qmljsquickfix.cpp",
        "qmljsquickfix.h",
        "qmljsquickfixassist.cpp",
        "qmljsquickfixassist.h",
        "qmljsquickfixes.cpp",
        "qmljsreuse.cpp",
        "qmljsreuse.h",
        "qmljssemantichighlighter.cpp",
        "qmljssemantichighlighter.h",
        "qmljssemanticinfoupdater.cpp",
        "qmljssemanticinfoupdater.h",
        "qmljssnippetprovider.cpp",
        "qmljssnippetprovider.h",
        "qmljswrapinloader.cpp",
        "qmljswrapinloader.h",
        "qmloutlinemodel.cpp",
        "qmloutlinemodel.h",
        "qmltaskmanager.cpp",
        "qmltaskmanager.h",
        "quicktoolbar.cpp",
        "quicktoolbar.h",
        "quicktoolbarsettingspage.cpp",
        "quicktoolbarsettingspage.h",
        "quicktoolbarsettingspage.ui",
        "images/qmlfile.png",
    ]

    Export {
        Depends { name: "QmlJSTools" }
    }
}
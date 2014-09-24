include(../../qtcreatorplugin.pri)
QT += script

DEFINES += \
    QMLJSEDITOR_LIBRARY

HEADERS += \
    qmljseditor.h \
    qmljseditor_global.h \
    qmljseditorconstants.h \
    qmljseditorfactory.h \
    qmljseditorplugin.h \
    qmlexpressionundercursor.h \
#    qmlfilewizard.h \//#720 ROOPAK
    qmljshighlighter.h \
    qmljshighlighterfactory.h \
    qmljshoverhandler.h \
#    qmljspreviewrunner.h \//#720 ROOPAK
    qmljscomponentfromobjectdef.h \
    qmljsoutline.h \
    qmloutlinemodel.h \
#    qmltaskmanager.h \//#720 ROOPAK
    qmljsoutlinetreeview.h \
#    quicktoolbarsettingspage.h \//#720 ROOPAK
    quicktoolbar.h \
    qmljscomponentnamedialog.h \
    qmljsfindreferences.h \
    qmljseditoreditable.h \
    qmljsautocompleter.h \
#    jsfilewizard.h \//#720 ROOPAK
    qmljssnippetprovider.h \
    qmljsreuse.h \
    qmljsquickfixassist.h \
    qmljscompletionassist.h \
    qmljsquickfix.h \
    qmljssemanticinfoupdater.h \
    qmljssemantichighlighter.h \
    qmljswrapinloader.h \
    qmljseditordocument.h \
    qmljseditordocument_p.h

SOURCES += \
    qmljseditor.cpp \
    qmljseditorfactory.cpp \
    qmljseditorplugin.cpp \
    qmlexpressionundercursor.cpp \
#    qmlfilewizard.cpp \//#720 ROOPAK
    qmljshighlighter.cpp \
    qmljshighlighterfactory.cpp \
    qmljshoverhandler.cpp \
#    qmljspreviewrunner.cpp \//#720 ROOPAK
    qmljscomponentfromobjectdef.cpp \
    qmljsoutline.cpp \
    qmloutlinemodel.cpp \
#    qmltaskmanager.cpp \//#720 ROOPAK
    qmljsquickfixes.cpp \
    qmljsoutlinetreeview.cpp \
#    quicktoolbarsettingspage.cpp \//#720 ROOPAK
    quicktoolbar.cpp \
    qmljscomponentnamedialog.cpp \
    qmljsfindreferences.cpp \
    qmljseditoreditable.cpp \
    qmljsautocompleter.cpp \
#    jsfilewizard.cpp \//#720 ROOPAK
    qmljssnippetprovider.cpp \
    qmljsreuse.cpp \
    qmljsquickfixassist.cpp \
    qmljscompletionassist.cpp \
    qmljsquickfix.cpp \
    qmljssemanticinfoupdater.cpp \
    qmljssemantichighlighter.cpp \
    qmljswrapinloader.cpp \
    qmljseditordocument.cpp

RESOURCES += qmljseditor.qrc

FORMS += \
#    quicktoolbarsettingspage.ui \//#720 ROOPAK
    qmljscomponentnamedialog.ui

DEFINES += CORE_LIBRARY
QT += network \
    script \
    sql

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += help printsupport
} else {
    CONFIG += help
}

include(../../qtcreatorplugin.pri)
#include(../../shared/scriptwrapper/scriptwrapper.pri)//#720 ROOPAK
win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250
SOURCES += mainwindow.cpp \
    editmode.cpp \
#    tabpositionindicator.cpp \//#720 ROOPAK
#    fancyactionbar.cpp \ #ROOPAK
    fancytabwidget.cpp \
#    generalsettings.cpp \#ROOPAK
    id.cpp \
    icontext.cpp \
    messagemanager.cpp \
#    messageoutputwindow.cpp \#ROOPAK
    outputpane.cpp \
#    outputwindow.cpp \//#720 ROOPAK
#    vcsmanager.cpp \//#720 ROOPAK
#    statusbarmanager.cpp \//#720 ROOPAK
#    versiondialog.cpp \//#720 ROOPAK
    editormanager/editormanager.cpp \
    editormanager/editorview.cpp \
    editormanager/documentmodel.cpp \
#    editormanager/openeditorsview.cpp \//#720 ROOPAK
    editormanager/openeditorswindow.cpp \
    editormanager/ieditorfactory.cpp \
#    editormanager/iexternaleditor.cpp \//#720 ROOPAK
    actionmanager/actionmanager.cpp \
    actionmanager/command.cpp \
#    actionmanager/commandbutton.cpp \//#720 ROOPAK
    actionmanager/actioncontainer.cpp \
#    actionmanager/commandsfile.cpp \#ROOPAK
#    dialogs/saveitemsdialog.cpp \#ROOPAK
#    dialogs/newdialog.cpp \#ROOPAK
    dialogs/settingsdialog.cpp \
#    actionmanager/commandmappings.cpp \#ROOPAK
#    dialogs/shortcutsettings.cpp \ #ROOPAK
#    dialogs/readonlyfilesdialog.cpp \ #ROOPAK
#    dialogs/openwithdialog.cpp \ #ROOPAK
    progressmanager/progressmanager.cpp \
    progressmanager/progressview.cpp \
    progressmanager/progressbar.cpp \
    progressmanager/futureprogress.cpp \
#    statusbarwidget.cpp \//#720 ROOPAK
    coreplugin.cpp \
    variablemanager.cpp \
    modemanager.cpp \
#    basefilewizard.cpp \//#720 ROOPAK
#    generatedfile.cpp \//#720 ROOPAK
    plugindialog.cpp \
#    inavigationwidgetfactory.cpp \//#720 ROOPAK
#    navigationwidget.cpp \//#720 ROOPAK
#    manhattanstyle.cpp \//#720 ROOPAK
    minisplitter.cpp \
#    styleanimator.cpp \//#720 ROOPAK
    findplaceholder.cpp \
    rightpane.cpp \
#    sidebar.cpp \//#720 ROOPAK
#    fileiconprovider.cpp \//#720 ROOPAK
    mimedatabase.cpp \
    icore.cpp \
    infobar.cpp \
    editormanager/ieditor.cpp \
    dialogs/ioptionspage.cpp \
#    dialogs/iwizard.cpp \//#720 ROOPAK
    settingsdatabase.cpp \
    imode.cpp \
#    editormanager/systemeditor.cpp \ #ROOPAK
#    designmode.cpp \                        #ROOPAK
#    editortoolbar.cpp \//#720 ROOPAK
#    helpmanager.cpp \//#720 ROOPAK
    outputpanemanager.cpp \
#    navigationsubwidget.cpp \//#720 ROOPAK
#    sidebarwidget.cpp \//#720 ROOPAK
#    externaltool.cpp \#ROOPAK
#    dialogs/externaltoolconfig.cpp \ #ROOPAK
#    toolsettings.cpp \#ROOPAK
#    variablechooser.cpp \ #ROOPAK
#    mimetypemagicdialog.cpp \#ROOPAK
#    mimetypesettings.cpp \#ROOPAK
#    dialogs/promptoverwritedialog.cpp \ #ROOPAK
    fileutils.cpp \
#    featureprovider.cpp \//#720 ROOPAK
    idocument.cpp \
    textdocument.cpp \
    documentmanager.cpp \
#    removefiledialog.cpp \#ROOPAK
#    iversioncontrol.cpp \//#720 ROOPAK
#    dialogs/addtovcsdialog.cpp \    #ROOPAK
    icorelistener.cpp \
    ioutputpane.cpp

HEADERS += mainwindow.h \
    editmode.h \
#    tabpositionindicator.h \//#720 ROOPAK
#    fancyactionbar.h \ #ROOPAK
    fancytabwidget.h \
#    generalsettings.h \#ROOPAK
    id.h \
    messagemanager.h \
#    messageoutputwindow.h \#ROOPAK
    outputpane.h \
#    outputwindow.h \//#720 ROOPAK
#    vcsmanager.h \//#720 ROOPAK
#    statusbarmanager.h \//#720 ROOPAK
    editormanager/editormanager.h \
    editormanager/editorview.h \
    editormanager/documentmodel.h \
#    editormanager/openeditorsview.h \//#720 ROOPAK
    editormanager/openeditorswindow.h \
    editormanager/ieditor.h \
#    editormanager/iexternaleditor.h \//#720 ROOPAK
    editormanager/ieditorfactory.h \
    actionmanager/actioncontainer.h \
    actionmanager/actionmanager.h \
    actionmanager/command.h \
#    actionmanager/commandbutton.h \//#720 ROOPAK
    actionmanager/actionmanager_p.h \
    actionmanager/command_p.h \
    actionmanager/actioncontainer_p.h \
#    actionmanager/commandsfile.h \#ROOPAK
#    dialogs/saveitemsdialog.h \#ROOPAK
#    dialogs/newdialog.h \#ROOPAK
    dialogs/settingsdialog.h \
#    actionmanager/commandmappings.h \#ROOPAK
#    dialogs/readonlyfilesdialog.h \ #ROOPAK
#    dialogs/shortcutsettings.h \ //ROOPAK
#    dialogs/openwithdialog.h \#ROOPAK
#    dialogs/iwizard.h \//#720 ROOPAK
    dialogs/ioptionspage.h \
    progressmanager/progressmanager_p.h \
    progressmanager/progressview.h \
    progressmanager/progressbar.h \
    progressmanager/futureprogress.h \
    progressmanager/progressmanager.h \
    icontext.h \
    icore.h \
    infobar.h \
    imode.h \
    ioutputpane.h \
    coreconstants.h \
#    iversioncontrol.h \//#720 ROOPAK
#    ifilewizardextension.h \//#720 ROOPAK
    icorelistener.h \
#    versiondialog.h \//#720 ROOPAK
    core_global.h \
#    statusbarwidget.h \//#720 ROOPAK
    coreplugin.h \
    variablemanager.h \
    modemanager.h \
#    basefilewizard.h \//#720 ROOPAK
#    generatedfile.h \//#720 ROOPAK
    plugindialog.h \
#    inavigationwidgetfactory.h \//#720 ROOPAK
#    navigationwidget.h \//#720 ROOPAK
#    manhattanstyle.h \//#720 ROOPAK
    minisplitter.h \
#    styleanimator.h \//#720 ROOPAK
    findplaceholder.h \
    rightpane.h \
#    sidebar.h \//#720 ROOPAK
#    fileiconprovider.h \//#720 ROOPAK
    mimedatabase.h \
    settingsdatabase.h \
#    editormanager/systemeditor.h \ #ROOPAK
#    designmode.h \                 #ROOPAK
#    editortoolbar.h \//#720 ROOPAK
#    helpmanager.h \//#720 ROOPAK
    outputpanemanager.h \
#    navigationsubwidget.h \//#720 ROOPAK
#    sidebarwidget.h \//#720 ROOPAK
#    externaltool.h \#ROOPAK
#    dialogs/externaltoolconfig.h \ #ROOPAK
#    toolsettings.h \ #ROOPAK
#    variablechooser.h \#ROOPAK
#    mimetypemagicdialog.h \#ROOPAK
#    mimetypesettings.h \#ROOPAK
#    dialogs/promptoverwritedialog.h \ #ROOPAK
    fileutils.h \
#    externaltoolmanager.h \#ROOPAK
#    generatedfile.h \//#720 ROOPAK
#    featureprovider.h \//#720 ROOPAK
    idocument.h \
    idocumentfactory.h \
    textdocument.h \
    documentmanager.h \
#    removefiledialog.h \#ROOPAK
#    dialogs/addtovcsdialog.h  #ROOPAK

FORMS += \#dialogs/newdialog.ui \ #ROOPAK
#    dialogs/saveitemsdialog.ui \ #ROOPAK
#    dialogs/readonlyfilesdialog.ui \ #ROOPAK
#    dialogs/openwithdialog.ui \#ROOPAK
#    generalsettings.ui \#ROOPAK
#    dialogs/externaltoolconfig.ui \ #ROOPAK
#    variablechooser.ui \#ROOPAK
#    mimetypesettingspage.ui \#ROOPAK
#    mimetypemagicdialog.ui \#ROOPAK
#    removefiledialog.ui \ #ROOPAK
#   dialogs/addtovcsdialog.ui   #ROOPAK

RESOURCES += core.qrc \
#    fancyactionbar.qrc#ROOPAK

include(find/find.pri)
#include(locator/locator.pri)//#720 ROOPAK

win32 {
    SOURCES += progressmanager/progressmanager_win.cpp
    greaterThan(QT_MAJOR_VERSION, 4): QT += gui-private # Uses QPlatformNativeInterface.
    LIBS += -lole32 -luser32
}
else:macx {
    HEADERS += macfullscreen.h
    OBJECTIVE_SOURCES += \
        progressmanager/progressmanager_mac.mm \
        macfullscreen.mm
    LIBS += -framework AppKit
}
else:unix {
    SOURCES += progressmanager/progressmanager_x11.cpp

    IMAGE_SIZE_LIST = 16 24 32 48 64 128 256 512

    for(imagesize, IMAGE_SIZE_LIST) {
        eval(image$${imagesize}.files = images/logo/$${imagesize}/QtProject-qtcreator.png)
        eval(image$${imagesize}.path = $$QTC_PREFIX/share/icons/hicolor/$${imagesize}x$${imagesize}/apps)
        INSTALLS += image$${imagesize}
    }
}
OTHER_FILES += editormanager/BinFiles.mimetypes.xml

equals(TEST, 1) {
#    SOURCES += testdatadir.cpp
#    HEADERS += testdatadir.h
}

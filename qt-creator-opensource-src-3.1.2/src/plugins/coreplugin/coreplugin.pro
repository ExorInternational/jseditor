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
include(../../shared/scriptwrapper/scriptwrapper.pri)
win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250
SOURCES += mainwindow.cpp \
    editmode.cpp \
    tabpositionindicator.cpp \
#    fancyactionbar.cpp \ #ROOPAK
    fancytabwidget.cpp \
#    generalsettings.cpp \#ROOPAK
    id.cpp \
    icontext.cpp \
    messagemanager.cpp \
#    messageoutputwindow.cpp \#ROOPAK
    outputpane.cpp \
    outputwindow.cpp \
    vcsmanager.cpp \
    statusbarmanager.cpp \
    versiondialog.cpp \
    editormanager/editormanager.cpp \
    editormanager/editorview.cpp \
    editormanager/documentmodel.cpp \
    editormanager/openeditorsview.cpp \
    editormanager/openeditorswindow.cpp \
    editormanager/ieditorfactory.cpp \
    editormanager/iexternaleditor.cpp \
    actionmanager/actionmanager.cpp \
    actionmanager/command.cpp \
    actionmanager/commandbutton.cpp \
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
    statusbarwidget.cpp \
    coreplugin.cpp \
    variablemanager.cpp \
    modemanager.cpp \
    basefilewizard.cpp \
    generatedfile.cpp \
    plugindialog.cpp \
    inavigationwidgetfactory.cpp \
    navigationwidget.cpp \
    manhattanstyle.cpp \
    minisplitter.cpp \
    styleanimator.cpp \
    findplaceholder.cpp \
    rightpane.cpp \
    sidebar.cpp \
    fileiconprovider.cpp \
    mimedatabase.cpp \
    icore.cpp \
    infobar.cpp \
    editormanager/ieditor.cpp \
    dialogs/ioptionspage.cpp \
    dialogs/iwizard.cpp \
    settingsdatabase.cpp \
    imode.cpp \
#    editormanager/systemeditor.cpp \ #ROOPAK
#    designmode.cpp \                        #ROOPAK
    editortoolbar.cpp \
    helpmanager.cpp \
    outputpanemanager.cpp \
    navigationsubwidget.cpp \
    sidebarwidget.cpp \
#    externaltool.cpp \#ROOPAK
#    dialogs/externaltoolconfig.cpp \ #ROOPAK
#    toolsettings.cpp \#ROOPAK
    variablechooser.cpp \
#    mimetypemagicdialog.cpp \#ROOPAK
#    mimetypesettings.cpp \#ROOPAK
#    dialogs/promptoverwritedialog.cpp \ #ROOPAK
    fileutils.cpp \
    featureprovider.cpp \
    idocument.cpp \
    textdocument.cpp \
    documentmanager.cpp \
#    removefiledialog.cpp \#ROOPAK
    iversioncontrol.cpp \
#    dialogs/addtovcsdialog.cpp \    #ROOPAK
    icorelistener.cpp \
    ioutputpane.cpp

HEADERS += mainwindow.h \
    editmode.h \
    tabpositionindicator.h \
#    fancyactionbar.h \ #ROOPAK
    fancytabwidget.h \
#    generalsettings.h \#ROOPAK
    id.h \
    messagemanager.h \
#    messageoutputwindow.h \#ROOPAK
    outputpane.h \
    outputwindow.h \
    vcsmanager.h \
    statusbarmanager.h \
    editormanager/editormanager.h \
    editormanager/editorview.h \
    editormanager/documentmodel.h \
    editormanager/openeditorsview.h \
    editormanager/openeditorswindow.h \
    editormanager/ieditor.h \
    editormanager/iexternaleditor.h \
    editormanager/ieditorfactory.h \
    actionmanager/actioncontainer.h \
    actionmanager/actionmanager.h \
    actionmanager/command.h \
    actionmanager/commandbutton.h \
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
    dialogs/iwizard.h \
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
    iversioncontrol.h \
    ifilewizardextension.h \
    icorelistener.h \
    versiondialog.h \
    core_global.h \
    statusbarwidget.h \
    coreplugin.h \
    variablemanager.h \
    modemanager.h \
    basefilewizard.h \
    generatedfile.h \
    plugindialog.h \
    inavigationwidgetfactory.h \
    navigationwidget.h \
    manhattanstyle.h \
    minisplitter.h \
    styleanimator.h \
    findplaceholder.h \
    rightpane.h \
    sidebar.h \
    fileiconprovider.h \
    mimedatabase.h \
    settingsdatabase.h \
#    editormanager/systemeditor.h \ #ROOPAK
#    designmode.h \                 #ROOPAK
    editortoolbar.h \
    helpmanager.h \
    outputpanemanager.h \
    navigationsubwidget.h \
    sidebarwidget.h \
#    externaltool.h \#ROOPAK
#    dialogs/externaltoolconfig.h \ #ROOPAK
#    toolsettings.h \ #ROOPAK
    variablechooser.h \
#    mimetypemagicdialog.h \#ROOPAK
#    mimetypesettings.h \#ROOPAK
#    dialogs/promptoverwritedialog.h \ #ROOPAK
    fileutils.h \
#    externaltoolmanager.h \#ROOPAK
    generatedfile.h \
    featureprovider.h \
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
    variablechooser.ui \
#    mimetypesettingspage.ui \#ROOPAK
#    mimetypemagicdialog.ui \#ROOPAK
#    removefiledialog.ui \ #ROOPAK
#   dialogs/addtovcsdialog.ui   #ROOPAK

RESOURCES += core.qrc \
#    fancyactionbar.qrc#ROOPAK

include(find/find.pri)
include(locator/locator.pri)

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
    SOURCES += testdatadir.cpp
    HEADERS += testdatadir.h
}

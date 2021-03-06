INCLUDEPATH +=

QT += sql

HEADERS += \
    $$PWD/core_global.h \
    $$PWD/icore.h \
    $$PWD/id.h \
    $$PWD/icontext.h \
    $$PWD/coreplugin.h \
    $$PWD/mainwindow.h \
    $$PWD/coreconstants.h \
    $$PWD/fancytabwidget.h \
    $$PWD/documentmanager.h \
    $$PWD/idocumentfactory.h \
    $$PWD/messagemanager.h \
    $$PWD/ioutputpane.h \
    $$PWD/modemanager.h \
    $$PWD/editmode.h \
    $$PWD/imode.h \
    $$PWD/mimedatabase.h \
    $$PWD/infobar.h \
    $$PWD/actionmanager/actioncontainer.h \
    $$PWD/actionmanager/actionmanager.h \
    $$PWD/actionmanager/command.h \
    $$PWD/actionmanager/actionmanager_p.h \
    $$PWD/actionmanager/command_p.h \
    $$PWD/actionmanager/actioncontainer_p.h \
    $$PWD/editormanager/editormanager.h \
    $$PWD/editormanager/editorview.h \
    $$PWD/editormanager/documentmodel.h \
    $$PWD/editormanager/openeditorswindow.h \
    $$PWD/editormanager/ieditor.h \
    $$PWD/editormanager/ieditorfactory.h \
    $$PWD/idocument.h \
    $$PWD/outputpanemanager.h \
    $$PWD/plugindialog.h \
    $$PWD/variablemanager.h \
    $$PWD/rightpane.h \
    $$PWD/dialogs/settingsdialog.h \
    $$PWD/dialogs/ioptionspage.h \
    $$PWD/icorelistener.h \
    $$PWD/progressmanager/progressmanager_p.h \
    $$PWD/progressmanager/progressview.h \
    $$PWD/progressmanager/progressbar.h \
    $$PWD/progressmanager/futureprogress.h \
    $$PWD/progressmanager/progressmanager.h \
    $$PWD/settingsdatabase.h \
    $$PWD/minisplitter.h \
    $$PWD/outputpane.h \
    $$PWD/fileutils.h \
    $$PWD/findplaceholder.h \
    $$PWD/textdocument.h \

SOURCES += \
    $$PWD/icore.cpp \
    $$PWD/id.cpp \
    $$PWD/icontext.cpp \
    $$PWD/coreplugin.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/fancytabwidget.cpp \
    $$PWD/documentmanager.cpp \
    $$PWD/messagemanager.cpp \
    $$PWD/ioutputpane.cpp \
    $$PWD/modemanager.cpp \
    $$PWD/editmode.cpp \
    $$PWD/imode.cpp \
    $$PWD/mimedatabase.cpp \
    $$PWD/infobar.cpp \
    $$PWD/actionmanager/actionmanager.cpp \
    $$PWD/actionmanager/command.cpp \
    $$PWD/actionmanager/actioncontainer.cpp \
    $$PWD/editormanager/editormanager.cpp \
    $$PWD/editormanager/editorview.cpp \
    $$PWD/editormanager/documentmodel.cpp \
    $$PWD/editormanager/openeditorswindow.cpp \
    $$PWD/editormanager/ieditorfactory.cpp \
    $$PWD/editormanager/ieditor.cpp \
    $$PWD/idocument.cpp \
    $$PWD/outputpanemanager.cpp \
    $$PWD/plugindialog.cpp \
    $$PWD/variablemanager.cpp \
    $$PWD/rightpane.cpp \
    $$PWD/dialogs/settingsdialog.cpp \
    $$PWD/dialogs/ioptionspage.cpp \
    $$PWD/icorelistener.cpp \
    $$PWD/progressmanager/progressmanager.cpp \
    $$PWD/progressmanager/progressview.cpp \
    $$PWD/progressmanager/progressbar.cpp \
    $$PWD/progressmanager/futureprogress.cpp \
    $$PWD/settingsdatabase.cpp \
    $$PWD/minisplitter.cpp \
    $$PWD/outputpane.cpp \
    $$PWD/fileutils.cpp \
    $$PWD/findplaceholder.cpp \
    $$PWD/textdocument.cpp \

RESOURCES += \
    $$PWD/core.qrc \

include(find/find.pri)

win32 {
    SOURCES += $$PWD/progressmanager/progressmanager_win.cpp
    greaterThan(QT_MAJOR_VERSION, 4): QT += gui-private # Uses QPlatformNativeInterface.
    LIBS += -lole32 -luser32
}
else:macx {
    HEADERS += macfullscreen.h
    OBJECTIVE_SOURCES += \
        $$PWD/progressmanager/progressmanager_mac.mm \
        $$PWD/macfullscreen.mm
    LIBS += -framework AppKit
}
else:unix {
    SOURCES += $$PWD/progressmanager/progressmanager_x11.cpp
    IMAGE_SIZE_LIST = 16 24 32 48 64 128 256 512

    for(imagesize, IMAGE_SIZE_LIST) {
        eval(image$${imagesize}.files = images/logo/$${imagesize}/QtProject-qtcreator.png)
        eval(image$${imagesize}.path = $$QTC_PREFIX/share/icons/hicolor/$${imagesize}x$${imagesize}/apps)
        INSTALLS += image$${imagesize}
    }
}

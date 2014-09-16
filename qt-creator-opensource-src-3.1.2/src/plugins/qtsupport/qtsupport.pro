DEFINES += QTSUPPORT_LIBRARY
QT += network

include(../../qtcreatorplugin.pri)

DEFINES += QMAKE_LIBRARY
include(../../shared/proparser/proparser.pri)

HEADERS += \
    qtsupportplugin.h \
    qtsupport_global.h \
#    qtkitconfigwidget.h \//#720 ROOPAK
#    qtkitinformation.h \//#720 ROOPAK
#    qtoutputformatter.h \//#720 ROOPAK
    qtversionmanager.h \
    qtversionfactory.h \
#    uicodemodelsupport.h \//#720 ROOPAK
    baseqtversion.h \
    qmldumptool.h \
    qtoptionspage.h \
#    customexecutablerunconfiguration.h \#ROOPAK
#    customexecutableconfigurationwidget.h \#ROOPAK
    debugginghelperbuildtask.h \
    qtsupportconstants.h \
    profilereader.h \
#    qtparser.h \//#720 ROOPAK
    exampleslistmodel.h \
    screenshotcropper.h \
    qtconfigwidget.h \
    qtfeatureprovider.h \
    desktopqtversionfactory.h \
#    simulatorqtversionfactory.h \//#720 ROOPAK
    desktopqtversion.h \
#    simulatorqtversion.h \//#720 ROOPAK
#    winceqtversionfactory.h \//#720 ROOPAK
#    winceqtversion.h//#720 ROOPAK

SOURCES += \
    qtsupportplugin.cpp \
#    qtkitconfigwidget.cpp \//#720 ROOPAK
#    qtkitinformation.cpp \//#720 ROOPAK
#    qtoutputformatter.cpp \//#720 ROOPAK
    qtversionmanager.cpp \
    qtversionfactory.cpp \
#    uicodemodelsupport.cpp \//#720 ROOPAK
    baseqtversion.cpp \
    qmldumptool.cpp \
    qtoptionspage.cpp \
#    customexecutablerunconfiguration.cpp \#ROOPAK
#    customexecutableconfigurationwidget.cpp \#ROOPAK
    debugginghelperbuildtask.cpp \
    profilereader.cpp \
#    qtparser.cpp \//#720 ROOPAK
    exampleslistmodel.cpp \
    screenshotcropper.cpp \
    qtconfigwidget.cpp \
    desktopqtversionfactory.cpp \
#    simulatorqtversionfactory.cpp \//#720 ROOPAK
    desktopqtversion.cpp \
#    simulatorqtversion.cpp \//#720 ROOPAK
#    winceqtversionfactory.cpp \//#720 ROOPAK
#    winceqtversion.cpp//#720 ROOPAK

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += quick
#    HEADERS += gettingstartedwelcomepage.h//#720 ROOPAK
#    SOURCES += gettingstartedwelcomepage.cpp//#720 ROOPAK
}

FORMS   +=  \
    showbuildlog.ui \
    qtversioninfo.ui \
    debugginghelper.ui \
    qtversionmanager.ui \

RESOURCES += \
    qtsupport.qrc

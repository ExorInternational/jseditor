DEFINES += QTSUPPORT_LIBRARY
QT += network

include(../../qtcreatorplugin.pri)

DEFINES += QMAKE_LIBRARY
include(../../shared/proparser/proparser.pri)

HEADERS += \
#    qtsupportplugin.h \//#720 ROOPAK
    qtsupport_global.h \
#    qtkitconfigwidget.h \//#720 ROOPAK
#    qtkitinformation.h \//#720 ROOPAK
#    qtoutputformatter.h \//#720 ROOPAK
#    qtversionmanager.h \//#720 ROOPAK
#    qtversionfactory.h \//#720 ROOPAK
#    uicodemodelsupport.h \//#720 ROOPAK
#    baseqtversion.h \//#720 ROOPAK
#    qmldumptool.h \//#720 ROOPAK
#    qtoptionspage.h \//#720 ROOPAK
#    customexecutablerunconfiguration.h \#ROOPAK
#    customexecutableconfigurationwidget.h \#ROOPAK
#    debugginghelperbuildtask.h \//#720 ROOPAK
#    qtsupportconstants.h \//#720 ROOPAK
#    profilereader.h \//#720 ROOPAK
#    qtparser.h \//#720 ROOPAK
#    exampleslistmodel.h \//#720 ROOPAK
#    screenshotcropper.h \//#720 ROOPAK
#    qtconfigwidget.h \//#720 ROOPAK
#    qtfeatureprovider.h \//#720 ROOPAK
#    desktopqtversionfactory.h \//#720 ROOPAK
#    simulatorqtversionfactory.h \//#720 ROOPAK
#    desktopqtversion.h \//#720 ROOPAK
#    simulatorqtversion.h \//#720 ROOPAK
#    winceqtversionfactory.h \//#720 ROOPAK
#    winceqtversion.h//#720 ROOPAK

SOURCES += \
#    qtsupportplugin.cpp \//#720 ROOPAK
#    qtkitconfigwidget.cpp \//#720 ROOPAK
#    qtkitinformation.cpp \//#720 ROOPAK
#    qtoutputformatter.cpp \//#720 ROOPAK
#    qtversionmanager.cpp \//#720 ROOPAK
#    qtversionfactory.cpp \//#720 ROOPAK
#    uicodemodelsupport.cpp \//#720 ROOPAK
#    baseqtversion.cpp \//#720 ROOPAK
#    qmldumptool.cpp \//#720 ROOPAK
#    qtoptionspage.cpp \//#720 ROOPAK
#    customexecutablerunconfiguration.cpp \#ROOPAK
#    customexecutableconfigurationwidget.cpp \#ROOPAK
#    debugginghelperbuildtask.cpp \//#720 ROOPAK
#    profilereader.cpp \//#720 ROOPAK
#    qtparser.cpp \//#720 ROOPAK
#    exampleslistmodel.cpp \//#720 ROOPAK
#    screenshotcropper.cpp \//#720 ROOPAK
#    qtconfigwidget.cpp \//#720 ROOPAK
#    desktopqtversionfactory.cpp \//#720 ROOPAK
#    simulatorqtversionfactory.cpp \//#720 ROOPAK
#    desktopqtversion.cpp \//#720 ROOPAK
#    simulatorqtversion.cpp \//#720 ROOPAK
#    winceqtversionfactory.cpp \//#720 ROOPAK
#    winceqtversion.cpp//#720 ROOPAK

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += quick
#    HEADERS += gettingstartedwelcomepage.h//#720 ROOPAK
#    SOURCES += gettingstartedwelcomepage.cpp//#720 ROOPAK
}

FORMS   +=  \
#    showbuildlog.ui \//#720 ROOPAK
#    qtversioninfo.ui \//#720 ROOPAK
#    debugginghelper.ui \//#720 ROOPAK
#    qtversionmanager.ui \//#720 ROOPAK

RESOURCES += \
    qtsupport.qrc

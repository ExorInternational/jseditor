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
#    qtoptionspage.h \//#720 ROOPAK
#    customexecutablerunconfiguration.h \#ROOPAK
#    customexecutableconfigurationwidget.h \#ROOPAK
    debugginghelperbuildtask.h \
    qtsupportconstants.h \
#    profilereader.h \//#720 ROOPAK
#    qtparser.h \//#720 ROOPAK
#    exampleslistmodel.h \//#720 ROOPAK
#    screenshotcropper.h \//#720 ROOPAK
    qtconfigwidget.h \
#    qtfeatureprovider.h \//#720 ROOPAK
#    desktopqtversionfactory.h \//#720 ROOPAK
#    simulatorqtversionfactory.h \//#720 ROOPAK
#    desktopqtversion.h \//#720 ROOPAK
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
#    qtoptionspage.cpp \//#720 ROOPAK
#    customexecutablerunconfiguration.cpp \#ROOPAK
#    customexecutableconfigurationwidget.cpp \#ROOPAK
    debugginghelperbuildtask.cpp \
#    profilereader.cpp \//#720 ROOPAK
#    qtparser.cpp \//#720 ROOPAK
#    exampleslistmodel.cpp \//#720 ROOPAK
#    screenshotcropper.cpp \//#720 ROOPAK
    qtconfigwidget.cpp \
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
    qtversioninfo.ui \
    debugginghelper.ui \
    qtversionmanager.ui \

RESOURCES += \
    qtsupport.qrc

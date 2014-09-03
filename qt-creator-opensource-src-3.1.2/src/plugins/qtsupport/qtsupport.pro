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
    qtoutputformatter.h \
    qtversionmanager.h \
    qtversionfactory.h \
    uicodemodelsupport.h \
    baseqtversion.h \
    qmldumptool.h \
    qtoptionspage.h \
#    customexecutablerunconfiguration.h \#ROOPAK
#    customexecutableconfigurationwidget.h \#ROOPAK
    debugginghelperbuildtask.h \
    qtsupportconstants.h \
    profilereader.h \
    qtparser.h \
    exampleslistmodel.h \
    screenshotcropper.h \
    qtconfigwidget.h \
    qtfeatureprovider.h \
    desktopqtversionfactory.h \
    simulatorqtversionfactory.h \
    desktopqtversion.h \
    simulatorqtversion.h \
    winceqtversionfactory.h \
    winceqtversion.h

SOURCES += \
    qtsupportplugin.cpp \
#    qtkitconfigwidget.cpp \//#720 ROOPAK
#    qtkitinformation.cpp \//#720 ROOPAK
    qtoutputformatter.cpp \
    qtversionmanager.cpp \
    qtversionfactory.cpp \
    uicodemodelsupport.cpp \
    baseqtversion.cpp \
    qmldumptool.cpp \
    qtoptionspage.cpp \
#    customexecutablerunconfiguration.cpp \#ROOPAK
#    customexecutableconfigurationwidget.cpp \#ROOPAK
    debugginghelperbuildtask.cpp \
    profilereader.cpp \
    qtparser.cpp \
    exampleslistmodel.cpp \
    screenshotcropper.cpp \
    qtconfigwidget.cpp \
    desktopqtversionfactory.cpp \
    simulatorqtversionfactory.cpp \
    desktopqtversion.cpp \
    simulatorqtversion.cpp \
    winceqtversionfactory.cpp \
    winceqtversion.cpp

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += quick
    HEADERS += gettingstartedwelcomepage.h
    SOURCES += gettingstartedwelcomepage.cpp
}

FORMS   +=  \
    showbuildlog.ui \
    qtversioninfo.ui \
    debugginghelper.ui \
    qtversionmanager.ui \

RESOURCES += \
    qtsupport.qrc

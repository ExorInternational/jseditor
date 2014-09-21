include(../../qtcreatorplugin.pri)

DEFINES += QMLJSTOOLS_LIBRARY

!dll {
    DEFINES += QMLJSTOOLS_STATIC
}

HEADERS += \
    $$PWD/qmljsbundleprovider.h \
    $$PWD/qmljstoolsplugin.h \
    $$PWD/qmljstoolsconstants.h \
    $$PWD/qmljstoolssettings.h \
#    $$PWD/qmljscodestylepreferencesfactory.h \//#720 ROOPAK
    $$PWD/qmljsmodelmanager.h \
    $$PWD/qmljsqtstylecodeformatter.h \
    $$PWD/qmljsrefactoringchanges.h \
#    $$PWD/qmljsfunctionfilter.h \//#720 ROOPAK
#    $$PWD/qmljslocatordata.h \//#720 ROOPAK
    $$PWD/qmljsindenter.h \
#    $$PWD/qmljscodestylesettingspage.h \//#720 ROOPAK
    $$PWD/qmljssemanticinfo.h \
    $$PWD/qmljstools_global.h \
    $$PWD/qmlconsolemanager.h \
    $$PWD/qmlconsoleitemmodel.h \
#    $$PWD/qmlconsolemodel.h \//#720 ROOPAK
    $$PWD/qmlconsolepane.h \
    $$PWD/qmlconsoleview.h \
    $$PWD/qmlconsoleitemdelegate.h \
    $$PWD/qmlconsoleedit.h \
    $$PWD/qmljsinterpreter.h \
    $$PWD/qmlconsoleproxymodel.h

SOURCES += \
    $$PWD/qmljsbundleprovider.cpp \
    $$PWD/qmljstoolsplugin.cpp \
    $$PWD/qmljstoolssettings.cpp \
#    $$PWD/qmljscodestylepreferencesfactory.cpp \//#720 ROOPAK
    $$PWD/qmljsmodelmanager.cpp \
    $$PWD/qmljsqtstylecodeformatter.cpp \
    $$PWD/qmljsrefactoringchanges.cpp \
#    $$PWD/qmljsfunctionfilter.cpp \//#720 ROOPAK
#    $$PWD/qmljslocatordata.cpp \//#720 ROOPAK
    $$PWD/qmljsindenter.cpp \
#    $$PWD/qmljscodestylesettingspage.cpp \//#720 ROOPAK
    $$PWD/qmljssemanticinfo.cpp \
    $$PWD/qmlconsolemanager.cpp \
    $$PWD/qmlconsoleitemmodel.cpp \
    $$PWD/qmlconsolepane.cpp \
    $$PWD/qmlconsoleview.cpp \
    $$PWD/qmlconsoleitemdelegate.cpp \
    $$PWD/qmlconsoleedit.cpp \
    $$PWD/qmljsinterpreter.cpp \
    $$PWD/qmlconsoleproxymodel.cpp

RESOURCES += \
    qmljstools.qrc

OTHER_FILES += \
    QmlJSTools.mimetypes.xml

#FORMS += \//#720 ROOPAK
#    $$PWD/qmljscodestylesettingspage.ui//#720 ROOPAK

equals(TEST, 1) {
    SOURCES += \
        $$PWD/qmljstools_test.cpp
}

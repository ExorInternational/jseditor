include(../../qtcreatorplugin.pri)

DEFINES += QMLJSTOOLS_LIBRARY

!dll {
    DEFINES += QMLJSTOOLS_STATIC
}

HEADERS += \
#    $$PWD/qmljsbundleprovider.h \//#720 ROOPAK
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
#    $$PWD/qmlconsolemanager.h \//#720 ROOPAK
#    $$PWD/qmlconsoleitemmodel.h \//#720 ROOPAK
#    $$PWD/qmlconsolemodel.h \//#720 ROOPAK
#    $$PWD/qmlconsolepane.h \//#720 ROOPAK
#    $$PWD/qmlconsoleview.h \//#720 ROOPAK
#    $$PWD/qmlconsoleitemdelegate.h \//#720 ROOPAK
#    $$PWD/qmlconsoleedit.h \//#720 ROOPAK
    $$PWD/qmljsinterpreter.h \
#    $$PWD/qmlconsoleproxymodel.h//#720 ROOPAK

SOURCES += \
#    $$PWD/qmljsbundleprovider.cpp \//#720 ROOPAK
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
#    $$PWD/qmlconsolemanager.cpp \//#720 ROOPAK
#    $$PWD/qmlconsoleitemmodel.cpp \//#720 ROOPAK
#    $$PWD/qmlconsolepane.cpp \//#720 ROOPAK
#    $$PWD/qmlconsoleview.cpp \//#720 ROOPAK
#    $$PWD/qmlconsoleitemdelegate.cpp \//#720 ROOPAK
#    $$PWD/qmlconsoleedit.cpp \//#720 ROOPAK
    $$PWD/qmljsinterpreter.cpp \
#    $$PWD/qmlconsoleproxymodel.cpp//#720 ROOPAK

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

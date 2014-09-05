HEADERS += \
    $$PWD/locator.h \
#    $$PWD/commandlocator.h \//#720 ROOPAK
    $$PWD/locatorwidget.h \
    $$PWD/locatorfiltersfilter.h \
#    $$PWD/settingspage.h \//#720 ROOPAK
    $$PWD/ilocatorfilter.h \
#    $$PWD/opendocumentsfilter.h \//#720 ROOPAK
#    $$PWD/filesystemfilter.h \//#720 ROOPAK
    $$PWD/locatorconstants.h \
#    $$PWD/directoryfilter.h \//#720 ROOPAK
    $$PWD/locatormanager.h \
#    $$PWD/basefilefilter.h \//#720 ROOPAK
#    $$PWD/executefilter.h \//#720 ROOPAK
    $$PWD/locatorsearchutils.h

SOURCES += \
    $$PWD/locator.cpp \
#    $$PWD/commandlocator.cpp \//#720 ROOPAK
    $$PWD/locatorwidget.cpp \
    $$PWD/locatorfiltersfilter.cpp \
#    $$PWD/opendocumentsfilter.cpp \//#720 ROOPAK
#    $$PWD/filesystemfilter.cpp \//#720 ROOPAK
#    $$PWD/settingspage.cpp \//#720 ROOPAK
#    $$PWD/directoryfilter.cpp \//#720 ROOPAK
    $$PWD/locatormanager.cpp \
#    $$PWD/basefilefilter.cpp \//#720 ROOPAK
    $$PWD/ilocatorfilter.cpp \
#    $$PWD/executefilter.cpp \//#720 ROOPAK
    $$PWD/locatorsearchutils.cpp

FORMS += \
#    $$PWD/settingspage.ui \//#720 ROOPAK
#    $$PWD/filesystemfilter.ui \//#720 ROOPAK
#    $$PWD/directoryfilter.ui//#720 ROOPAK

RESOURCES += \
    $$PWD/locator.qrc

#equals(TEST, 1) {
#    HEADERS += $$PWD/locatorfiltertest.h
#    SOURCES += \
#        $$PWD/locatorfiltertest.cpp \
#        $$PWD/locator_test.cpp
#    DEFINES += SRCDIR=\\\"$$PWD\\\"
#}

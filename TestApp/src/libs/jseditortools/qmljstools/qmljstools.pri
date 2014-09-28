

HEADERS += \
    $$PWD/qmljstoolsplugin.h \
    $$PWD/qmljstoolsconstants.h \
    $$PWD/qmljstoolssettings.h \
    $$PWD/qmljsmodelmanager.h \
    $$PWD/qmljsqtstylecodeformatter.h \
    $$PWD/qmljsrefactoringchanges.h \
    $$PWD/qmljsindenter.h \
    $$PWD/qmljssemanticinfo.h \
    $$PWD/qmljstools_global.h \
    $$PWD/qmljsinterpreter.h \

SOURCES += \
    $$PWD/qmljstoolsplugin.cpp \
    $$PWD/qmljstoolssettings.cpp \
    $$PWD/qmljsmodelmanager.cpp \
    $$PWD/qmljsqtstylecodeformatter.cpp \
    $$PWD/qmljsrefactoringchanges.cpp \
    $$PWD/qmljsindenter.cpp \
    $$PWD/qmljssemanticinfo.cpp \
    $$PWD/qmljsinterpreter.cpp \

RESOURCES += \
    $$PWD/qmljstools.qrc

OTHER_FILES += \
    $$PWD/QmlJSTools.mimetypes.xml

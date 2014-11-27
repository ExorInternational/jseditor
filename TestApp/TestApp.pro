#include(TestApp.pri)


#! [0]

TEMPLATE  = subdirs
#TEMPLATE  = app
CONFIG   += ordered

#SUBDIRS =   src/libs/utils \
#            src/libs/3rdparty/botan

#LIBS += -L /media/New_Volume/Ubuntu-Build/Test-project/build-TestApp2-Desktop-Debug/src/libs/utils -lUtils


#LIBS += -L $$OUT_PWD/src/libs/utils -lUtils

#MY_LIB_FILES += $$OUT_PWD/src/libs/utils/libUtils.so.1.0.0
## Define what files are 'extra_libs' and where to put them
#extra_libs.files = MY_LIB_FILES
#extra_libs.path = $$OUT_PWD

#INSTALLS += extra_libs

#app_info.input = $$PWD/src/app/app_version.h.in//#720 ROOPAK - START
#app_info.output = $$OUT_PWD/src/app/app_version.h
#QMAKE_SUBSTITUTES += app_info//#720 ROOPAK - END

SUBDIRS = \
##         ./src/libs/3rdparty/botan \
#         ./src/libs/utils \
#         ./src/libs/languageutils \
#         ./src/libs/cplusplus \
#         ./src/libs/qmljs \
#         ./src/libs/aggregation \
#         ./src/libs/extensionsystem \
#         ./src/libs/qmleditorwidgets \
         src \
         bin \


target.path = $$OUT_PWD
INSTALLS += target

contains(QT_ARCH, i386): ARCHITECTURE = x86
else: ARCHITECTURE = $$QT_ARCH

macx: PLATFORM = "mac"
else:win32: PLATFORM = "windows"
else:linux-*: PLATFORM = "linux-$${ARCHITECTURE}"
else: PLATFORM = "unknown"



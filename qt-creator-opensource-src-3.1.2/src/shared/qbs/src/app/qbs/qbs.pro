include(../app.pri)
include(parser/parser.pri)

TARGET = qbs

SOURCES += main.cpp \
    ctrlchandler.cpp \
    application.cpp \
    status.cpp \
    consoleprogressobserver.cpp \
    commandlinefrontend.cpp \
    qbstool.cpp

HEADERS += \
    ctrlchandler.h \
    application.h \
    status.h \
    consoleprogressobserver.h \
    commandlinefrontend.h \
    qbstool.h \
    ../shared/qbssettings.h

include(../../library_dirname.pri)
DEFINES += QBS_LIBRARY_DIRNAME=\\\"$${QBS_LIBRARY_DIRNAME}\\\"

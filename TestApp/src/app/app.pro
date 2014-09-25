include(../../TestApp.pri)

TARGET = $$IDE_APP_TARGET
DESTDIR = $$IDE_APP_PATH

QMAKE_SUBSTITUTES += $$PWD/app_version.h.in

include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$QTC_LIB_NAME

include(../TestApp.pri)#ROOPAK

DESTDIR = $$IDE_LIBRARY_PATH

TARGET = $$qtLibraryName($$TARGET)

TEMPLATE = lib
CONFIG += shared dll

!macx {
    win32 {
        target.path = /bin
    } else {
        target.path = /$$IDE_LIBRARY_BASENAME/qtcreator
    }
    INSTALLS += target
}

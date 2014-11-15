QT += network script
include(../TestApp.pri)

TEMPLATE = app
TARGET = $$IDE_APP_TARGET
DESTDIR = $$IDE_APP_PATH

HEADERS       = mainwindow-app.h \
    CustomTypes/FileSystemObj.h
SOURCES       = main.cpp \
                mainwindow-app.cpp \
    CustomTypes/FileSystemObj.cpp
FORMS         = mainwindow-app.ui

HEADERS      += CustomTypes/JSObjects.h     \
                CustomTypes/PageWgt.h       \
                CustomTypes/ProjectWgt.h    \
                CustomTypes/Widget.h

SOURCES      += CustomTypes/JSObjects.cpp     \
                CustomTypes/PageWgt.cpp       \
                CustomTypes/ProjectWgt.cpp    \
                CustomTypes/Widget.cpp

#! [0]
#RESOURCES     = application.qrc


LIBS *= \
#        -l$$qtLibraryName(Utils) \//#720 ROOPAK
#        -l$$qtLibraryName(LanguageUtils) \//#720 ROOPAK
#        -l$$qtLibraryName(CPlusPlus) \//#720 ROOPAK
#        -l$$qtLibraryName(QmlJS) \//#720 ROOPAK
        -l$$qtLibraryName(JsEditorTools) \ #720 - COMMENTED BY ROOPAK - USED QLIBRARY TO LOAD THE DLL
#        -l$$qtLibraryName(Aggregation) \//#720 ROOPAK
#        -l$$qtLibraryName(ExtensionSystem) \//#720 ROOPAK
#        -l$$qtLibraryName(QmlEditorWidgets) \//#720 ROOPAK
#        -l$$qtLibraryName(QtcSsh) \

#win32 {
#    RC_FILE = qtcreator.rc
#    target.path = $$QTC_PREFIX/bin
#    INSTALLS += target
#} else:macx {
#    LIBS += -framework CoreFoundation
#    ICON = qtcreator.icns
#    FILETYPES.files = profile.icns prifile.icns
#    FILETYPES.path = Contents/Resources
#    QMAKE_BUNDLE_DATA += FILETYPES
#    info.input = Info.plist.in
#    info.output = $$IDE_BIN_PATH/../Info.plist
#    QMAKE_SUBSTITUTES = info
#} else {
#    target.path  = $$QTC_PREFIX/bin
#    INSTALLS    += target
#}

#This is a temp fix for QString error("QString::QString(const char*)' is privateQString(const char *ch)").
DEFINES -= QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII
#This removes the unused parameter warnings
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

INCLUDEPATH += $$PWD/../src/libs/jseditortools
#LIBS *= -l$$qtLibraryName(JsEditorTools) \

#QMAKE_SUBSTITUTES += $$PWD/app_version.h.in

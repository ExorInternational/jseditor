QT += network
include(../TestApp.pri)

TEMPLATE = app
TARGET = $$IDE_APP_TARGET
DESTDIR = $$IDE_APP_PATH

HEADERS       = mainwindow.h
SOURCES       = main.cpp \
                mainwindow.cpp
FORMS         = mainwindow.ui

#! [0]
#RESOURCES     = application.qrc


#LIBS *= \
#        -l$$qtLibraryName(Utils) \
#        -l$$qtLibraryName(LanguageUtils) \
#        -l$$qtLibraryName(CPlusPlus) \
#        -l$$qtLibraryName(QmlJS) \
#        -l$$qtLibraryName(Aggregation) \
#        -l$$qtLibraryName(ExtensionSystem) \
#        -l$$qtLibraryName(QmlEditorWidgets) \
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


#INCLUDEPATH += $$PWD/../src/libs/jseditortools
#LIBS *= -l$$qtLibraryName(JsEditorTools) \

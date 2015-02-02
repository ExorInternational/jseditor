!isEmpty(JSEDITORTOOLS_LIB_PRI_INCLUDED):error("JsEditorTools-Lib.pri already included")
JSEDITORTOOLS_LIB_PRI_INCLUDED = 1

#TestApp.pro ----------------------------------------------------------------------- END
contains(QT_ARCH, i386): ARCHITECTURE = x86
else: ARCHITECTURE = $$QT_ARCH

macx: PLATFORM = "mac"
else:win32: PLATFORM = "windows"
else:linux-*: PLATFORM = "linux-$${ARCHITECTURE}"
else: PLATFORM = "unknown"
#TestApp.pro ----------------------------------------------------------------------- END

#bin.pro ----------------------------------------------------------------------- START
QT += network script
#This is a temp fix for QString error("QString::QString(const char*)' is privateQString(const char *ch)").
DEFINES -= QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII
#This removes the unused parameter warnings
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter
#bin.pro ----------------------------------------------------------------------- END

#libs.pro ----------------------------------------------------------------------- START
TEMPLATE  = subdirs
for(l, SUBDIRS) {
    QTC_LIB_DEPENDS =
    include($$l/$${l}_dependencies.pri)
    lv = $${l}.depends
    $$lv = $$QTC_LIB_DEPENDS
}
#libs.pro ----------------------------------------------------------------------- END

#TestApp.pri ----------------------------------------------------------------------- START


defineReplace(qtLibraryName) {
   unset(LIBRARY_NAME)
   LIBRARY_NAME = $$1
   CONFIG(debug, debug|release) {
      !debug_and_release|build_pass {
          mac:RET = $$member(LIBRARY_NAME, 0)_debug
              else:win32:RET = $$member(LIBRARY_NAME, 0)d
      }
   }
   isEmpty(RET):RET = $$LIBRARY_NAME
   return($$RET)
}
isEmpty(IDE_LIBRARY_BASENAME) {
    IDE_LIBRARY_BASENAME = lib
}
defineReplace(cleanPath) {
    win32:1 ~= s|\\\\|/|g
    contains(1, ^/.*):pfx = /
    else:pfx =
    segs = $$split(1, /)
    out =
    for(seg, segs) {
        equals(seg, ..):out = $$member(out, 0, -2)
        else:!equals(seg, .):out += $$seg
    }
    return($$join(out, /, $$pfx))
}
IDE_SOURCE_TREE = $$PWD
isEmpty(IDE_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    IDE_BUILD_TREE = $$cleanPath($$OUT_PWD)
    IDE_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}
#IDE_APP_PATH = $$IDE_BUILD_TREE/bin
#IDE_APP_TARGET   = TestApp
IDE_LIBRARY_PATH = $$IDE_BUILD_TREE/$$IDE_LIBRARY_BASENAME
#IDE_PLUGIN_PATH  = $$IDE_LIBRARY_PATH/plugins

INCLUDEPATH += \
#    $$IDE_BUILD_TREE/src \ # for <app/app_version.h>//#720 ROOPAK
    $$IDE_SOURCE_TREE/src/libs #\
#    $$IDE_SOURCE_TREE/src/libs/3rdparty  \
#   $$IDE_SOURCE_TREE/tools  \
#    $$IDE_SOURCE_TREE/src/plugins

#QTC_PLUGIN_DIRS = $$(QTC_PLUGIN_DIRS)
#QTC_PLUGIN_DIRS = $$split(QTC_PLUGIN_DIRS, $$QMAKE_DIRLIST_SEP)
#QTC_PLUGIN_DIRS += $$IDE_SOURCE_TREE/src/plugins
#for(dir, QTC_PLUGIN_DIRS) {
#    INCLUDEPATH += $$dir
#}

LIBS += -L$$IDE_LIBRARY_PATH

DEFINES += QT_CREATOR QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII
!macx:DEFINES += QT_USE_FAST_OPERATOR_PLUS QT_USE_FAST_CONCATENATION

unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

# recursively resolve plugin deps
#done_plugins =
#for(ever) {
#    isEmpty(QTC_PLUGIN_DEPENDS): \
#        break()
#    done_plugins += $$QTC_PLUGIN_DEPENDS
#    for(dep, QTC_PLUGIN_DEPENDS) {
#        dependencies_file =
#        for(dir, QTC_PLUGIN_DIRS) {
#            exists($$dir/$$dep/$${dep}_dependencies.pri) {
#                dependencies_file = $$dir/$$dep/$${dep}_dependencies.pri
#                break()
#            }
#        }
#        isEmpty(dependencies_file): \
#            error("Plugin dependency $$dep not found")
#        include($$dependencies_file)
#        LIBS += -l$$qtLibraryName($$QTC_PLUGIN_NAME)
#    }
#    QTC_PLUGIN_DEPENDS = $$unique(QTC_PLUGIN_DEPENDS)
#    QTC_PLUGIN_DEPENDS -= $$unique(done_plugins)
#}

# recursively resolve library deps
done_libs =
for(ever) {
    isEmpty(QTC_LIB_DEPENDS): \
        break()
    done_libs += $$QTC_LIB_DEPENDS
    for(dep, QTC_LIB_DEPENDS) {
        include($$PWD/src/libs/$$dep/$${dep}_dependencies.pri)
        LIBS += -l$$qtLibraryName($$QTC_LIB_NAME)
    }
    QTC_LIB_DEPENDS = $$unique(QTC_LIB_DEPENDS)
    QTC_LIB_DEPENDS -= $$unique(done_libs)
}

CONFIG += depend_includepath

!isEmpty(vcproj) {
    DEFINES += IDE_LIBRARY_BASENAME=\"$$IDE_LIBRARY_BASENAME\"
} else {
    DEFINES += IDE_LIBRARY_BASENAME=\\\"$$IDE_LIBRARY_BASENAME\\\"
}

QTCREATOR_VERSION = 3.1.2
QTCREATOR_COMPAT_VERSION = 3.1.0

#TestApp.pri ----------------------------------------------------------------------- END

#qtcreatorlibrar.pri ----------------------------------------------------------------------- START
include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$QTC_LIB_NAME

#include(../TestApp.pri)#ROOPAK

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
#qtcreatorlibrar.pri ----------------------------------------------------------------------- END

contains(CONFIG, dll) {
    DEFINES += BUILD_JSEDITORTOOLS_LIB
} else {
    DEFINES += BUILD_JSEDITORTOOLS_STATIC_LIB
}

include(utils/utils.pri)
include(languageutils/languageutils.pri)
include(qmljs/qmljs.pri)
include(aggregation/aggregation.pri)
include(extensionsystem/extensionsystem.pri)
include(qmljseditor/qmljseditor.pri)
include(qmljstools/qmljstools.pri)
include(coreplugin/coreplugin.pri)
include(texteditor/texteditor.pri)

HEADERS += jseditortools.h \
    jseditortools_global.h \
    jseditormenuitems.h

SOURCES += jseditortools.cpp \
    jseditormenuitems.cpp

RESOURCES += \
    $$PWD/Resources/jseditortools.qrc



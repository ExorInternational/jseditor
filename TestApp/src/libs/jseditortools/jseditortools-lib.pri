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



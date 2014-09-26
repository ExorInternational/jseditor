contains(CONFIG, dll) {
    DEFINES += BUILD_JSEDITORTOOLS_LIB
} else {
    DEFINES += BUILD_JSEDITORTOOLS_STATIC_LIB
}

include(qmljseditor/qmljseditor.pri)
include(qmljstools/qmljstools.pri)
include(coreplugin/coreplugin.pri)

HEADERS += jseditortools.h \
    jseditortools_global.h \
#    qmljssemanticinfoupdater.h \
#    qmljssemanticinfo.h

SOURCES += jseditortools.cpp \
#    qmljssemanticinfoupdater.cpp \
#    qmljssemanticinfo.cpp



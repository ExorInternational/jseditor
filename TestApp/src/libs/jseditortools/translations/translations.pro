#include(../jseditortools-lib.pri)

LANGUAGES = cs de fr ja pl ru sl zh_CN zh_TW

defineReplace(targetPath) {
    return($$replace(1, /, $$QMAKE_DIR_SEP))
}

# var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}

TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/jseditortools_,.ts)

LUPDATE = $$targetPath($$[QT_INSTALL_BINS]/lupdate) -locations relative -no-ui-lines -no-sort
#LUPDATE = $$targetPath($$[QT_INSTALL_BINS]/lupdate) -locations relative -no-ui-lines -no-sort
#LRELEASE = $$targetPath($$[QT_INSTALL_BINS]/lrelease)
#LCONVERT = $$targetPath($$[QT_INSTALL_BINS]/lconvert)

#sources = src/app src/libs $$plugin_sources src/shared share/qtcreator/qmldesigner \
#          share/qtcreator/welcomescreen share/qtcreator/welcomescreen/widgets

sources =   ../aggregation \
            ../coreplugin \
            ../extensionsystem \
            ../find \
            ../jseditortools-lib \
            ../languageutils \
            ../parser \

files = $$files($$PWD/*_??.ts) $$PWD/jseditortools_untranslated.ts
for(file, files) {
    lang = $$replace(file, .*_([^/]*)\\.ts, \\1)
    v = ts-$${lang}.commands
    $$v = cd $$wd && $$LUPDATE $$sources -ts $$file
    v = ts-$${lang}.depends
    $$v = extract
    QMAKE_EXTRA_TARGETS += ts-$$lang
}


TEMPLATE = app
TARGET = phony_target2
QMAKE_LINK = @: IGNORE THIS LINE
OBJECTS_DIR =
win32:CONFIG -= embed_manifest_exe

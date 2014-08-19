TEMPLATE = subdirs

SUBDIRS = \#qtpromaker \    #ROOPAK
     qmlpuppet \
#     ../plugins/cpaster/frontend \ #ROOPAK
#     sdktool \     #ROOPAK
#     valgrindfake \ #ROOPAK
#     3rdparty \    #ROOPAK
#     buildoutputparser #ROOPAK

win32 {
#    SUBDIRS += qtcdebugger
#    SUBDIRS += wininterrupt
}

mac {
#    SUBDIRS += iostool    #ROOPAK
}

QT_BREAKPAD_ROOT_PATH = $$(QT_BREAKPAD_ROOT_PATH)
!isEmpty(QT_BREAKPAD_ROOT_PATH) {
    #SUBDIRS += qtcrashhandler
} else {
    linux-* {
        # Build only in debug mode.
        debug_and_release|CONFIG(debug, debug|release) {
#            SUBDIRS += qtcreatorcrashhandler #ROOPAK
        }
    }
}

greaterThan(QT_MAJOR_VERSION, 4) {
    !greaterThan(QT_MINOR_VERSION, 0):!greaterThan(QT_PATCH_VERSION, 0) {
    } else {
        SUBDIRS += qml2puppet
    }
}

TEMPLATE  = subdirs

SUBDIRS   = \
#    aggregation \//#720 ROOPAK
#    extensionsystem \//#720 ROOPAK
#    utils \//#720 ROOPAK
#    languageutils \//#720 ROOPAK
#    cplusplus \//#720 ROOPAK
#    qmljs \//#720 ROOPAK
#    qmleditorwidgets \//#720 ROOPAK
    jseditortools #//#720 ADDED BY ROOPAK

#for(l, SUBDIRS) {
#    QTC_LIB_DEPENDS =
#    include($$l/$${l}_dependencies.pri)
#    lv = $${l}.depends
#    $$lv = $$QTC_LIB_DEPENDS
#}

#SUBDIRS += \               #ROOPAK
#    utils/process_stub.pro

#QBS_DIRS = \                                       #ROOPAK - START
#    corelib \
#    qtprofilesetup \
#    ../shared/qbs/src/plugins \
#    ../shared/qbs/static.pro
#corelib.subdir = ../shared/qbs/src/lib/corelib
#qtprofilesetup.subdir = ../shared/qbs/src/lib/qtprofilesetup
#qtprofilesetup.depends = corelib

#exists(../shared/qbs/qbs.pro): SUBDIRS += $$QBS_DIRS
#TR_EXCLUDE = $$QBS_DIRS                            #ROOPAK - END

#win32:SUBDIRS += utils/process_ctrlc_stub.pro  #ROOPAK

# Windows: Compile Qt Creator CDB extension if Debugging tools can be detected.    
win32 {
#    include(qtcreatorcdbext/cdb_detect.pri)        #ROOPAK
#    exists($$CDB_PATH):SUBDIRS += qtcreatorcdbext  #ROOPAK
}

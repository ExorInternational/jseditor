include(../../qtcreator.pri)

TEMPLATE  = subdirs

SUBDIRS   = \
    coreplugin \
    find \
    texteditor \
    cppeditor \
    bineditor \
    diffeditor \
    imageviewer \
    bookmarks \
    projectexplorer \
#    vcsbase \     #ROOPAK
#    perforce \     #ROOPAK
#    subversion \   #ROOPAK
#    git \       #ROOPAK
#    cvs \       #ROOPAK
    cpptools \
    qtsupport \
    qmakeprojectmanager \
    locator \
    debugger \
#    help \     #ROOPAK
#    cpaster \     #ROOPAK
    cmakeprojectmanager \
    autotoolsprojectmanager \
#    fakevim \     #ROOPAK
    designer \
    resourceeditor \
    genericprojectmanager \
    qmljseditor \
    qmlprojectmanager \
    glsleditor \
    pythoneditor \
#    mercurial \     #ROOPAK
#    bazaar \     #ROOPAK
    classview \
#    tasklist \     #ROOPAK
#    analyzerbase \ #ROOPAK
    qmljstools \
    macros \
#    remotelinux \  #ROOPAK
#    android \      #ROOPAK
#    valgrind \     #ROOPAK
#    todo \         #ROOPAK
#    qnx \          #ROOPAK
#    clearcase \     #ROOPAK
#    baremetal \    #ROOPAK
#    ios \          #ROOPAK
    beautifier

minQtVersion(5, 0, 0) {
    SUBDIRS += winrt
}

# prefer qmake variable set on command line over env var
isEmpty(LLVM_INSTALL_DIR):LLVM_INSTALL_DIR=$$(LLVM_INSTALL_DIR)
!isEmpty(LLVM_INSTALL_DIR) {
    SUBDIRS += clangcodemodel
}

isEmpty(QBS_INSTALL_DIR): QBS_INSTALL_DIR = $$(QBS_INSTALL_DIR)
exists(../shared/qbs/qbs.pro)|!isEmpty(QBS_INSTALL_DIR): \
    SUBDIRS += \
        qbsprojectmanager

isEmpty(IDE_PACKAGE_MODE) {
    SUBDIRS += \
#        helloworld \     #ROOPAK
        updateinfo
} else:!isEmpty(UPDATEINFO_ENABLE) {
    SUBDIRS += \
        updateinfo
}

#minQtVersion(5, 2, 0) {                                #ROOPAK - START
#    SUBDIRS += \
#        qmldesigner \
#        qmlprofiler \
#        welcome
#} else {
#     warning("QmlDesigner plugin has been disabled.")
#     warning("QmlProfiler plugin has been disabled.")
#     warning("Welcome plugin has been disabled.")
#     warning("These plugins need at least Qt 5.2.")
#}                                                      #ROOPAK - END

for(p, SUBDIRS) {
    QTC_PLUGIN_DEPENDS =
    include($$p/$${p}_dependencies.pri)
    pv = $${p}.depends
    $$pv = $$QTC_PLUGIN_DEPENDS
}

linux-* {
     SUBDIRS += debugger/ptracepreload.pro
}

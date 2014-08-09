include(../../qtcreator.pri)

TEMPLATE  = subdirs

SUBDIRS   = \
    coreplugin \
    find \
    texteditor \
    cppeditor \
#    bineditor \    #ROOPAK
#    diffeditor \   #ROOPAK
#    imageviewer \  #ROOPAK
#    bookmarks \    #ROOPAK
    projectexplorer \
#    vcsbase \     #ROOPAK
#    perforce \     #ROOPAK
#    subversion \   #ROOPAK
#    git \       #ROOPAK
#    cvs \       #ROOPAK
    cpptools \
    qtsupport \
#    qmakeprojectmanager \  #ROOPAK
    locator \
    debugger \
#    help \     #ROOPAK
#    cpaster \     #ROOPAK
#    cmakeprojectmanager \  #ROOPAK
#    autotoolsprojectmanager \     #ROOPAK
#    fakevim \     #ROOPAK
#    designer \     #ROOPAK
#    resourceeditor \   #ROOPAK
#    genericprojectmanager \    #ROOPAK
    qmljseditor \
    qmlprojectmanager \
#    glsleditor \     #ROOPAK
#    pythoneditor \     #ROOPAK
#    mercurial \     #ROOPAK
#    bazaar \     #ROOPAK
#    classview \    #ROOPAK
#    tasklist \     #ROOPAK
#    analyzerbase \ #ROOPAK
    qmljstools \
#    macros \       #ROOPAK
#    remotelinux \  #ROOPAK
#    android \      #ROOPAK
#    valgrind \     #ROOPAK
#    todo \         #ROOPAK
#    qnx \          #ROOPAK
#    clearcase \     #ROOPAK
#    baremetal \    #ROOPAK
#    ios \          #ROOPAK
#    beautifier     #ROOPAK

minQtVersion(5, 0, 0) {
    SUBDIRS += winrt
}

# prefer qmake variable set on command line over env var
isEmpty(LLVM_INSTALL_DIR):LLVM_INSTALL_DIR=$$(LLVM_INSTALL_DIR)
!isEmpty(LLVM_INSTALL_DIR) {
    SUBDIRS += clangcodemodel
}

#isEmpty(QBS_INSTALL_DIR): QBS_INSTALL_DIR = $$(QBS_INSTALL_DIR)    #ROOPAK - START
#exists(../shared/qbs/qbs.pro)|!isEmpty(QBS_INSTALL_DIR): \
#    SUBDIRS += \
#        qbsprojectmanager

#isEmpty(IDE_PACKAGE_MODE) {
#    SUBDIRS += \
##        helloworld \     #ROOPAK
#        updateinfo
#} else:!isEmpty(UPDATEINFO_ENABLE) {
#    SUBDIRS += \
#        updateinfo
#}                                                                   #ROOPAK - END

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

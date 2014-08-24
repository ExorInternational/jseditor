QT += xml script

include(../../qtcreatorplugin.pri)
include(customwizard/customwizard.pri)
HEADERS += projectexplorer.h \
    abi.h \
    abiwidget.h \
    ansifilterparser.h \
    buildinfo.h \
    clangparser.h \
    environmentaspect.h \
    environmentaspectwidget.h \
    gcctoolchain.h \
    importwidget.h \
    localapplicationrunconfiguration.h \
    localenvironmentaspect.h \
    osparser.h \
    projectexplorer_export.h \
    projectimporter.h \
    projectwindow.h \
    removetaskhandler.h \
    targetsetuppage.h \
    targetsetupwidget.h \
    unconfiguredprojectpanel.h \
    kit.h \
    kitchooser.h \
    kitconfigwidget.h \
    kitinformation.h \
    kitinformationconfigwidget.h \
    kitmanager.h \
    kitmanagerconfigwidget.h \
    kitmodel.h \
    kitoptionspage.h \
    buildmanager.h \
    buildsteplist.h \
#    compileoutputwindow.h \#ROOPAK
    deployconfiguration.h \
    deployconfigurationmodel.h \
    namedwidget.h \
    target.h \
    targetsettingspanel.h \
    task.h \
    itaskhandler.h \
    copytaskhandler.h \
    showineditortaskhandler.h \
#    showoutputtaskhandler.h \#ROOPAK
    vcsannotatetaskhandler.h \
#    taskwindow.h \//ROOPAK
    taskmodel.h \
    projectfilewizardextension.h \
    session.h \
    dependenciespanel.h \
    allprojectsfilter.h \
    ioutputparser.h \
    projectconfiguration.h \
    gnumakeparser.h \
    projectexplorerconstants.h \
    projectexplorersettings.h \
    corelistenercheckingforrunningbuild.h \
    project.h \
    pluginfilefactory.h \
    iprojectmanager.h \
    currentprojectfilter.h \
    allprojectsfind.h \
    buildstep.h \
    buildconfiguration.h \
    iprojectproperties.h \
    buildsettingspropertiespage.h \
    environmentwidget.h \
#    processstep.h \#ROOPAK
    editorconfiguration.h \
#    editorsettingspropertiespage.h \#ROOPAK
    runconfiguration.h \
    applicationlauncher.h \
    runsettingspropertiespage.h \
#    projecttreewidget.h \ #ROOPAK
#    foldernavigationwidget.h \#ROOPAK
#    buildprogress.h \#ROOPAK
    projectnodes.h \
#    sessiondialog.h \#ROOPAK
#    projectwizardpage.h \#ROOPAK
    buildstepspage.h \
    nodesvisitor.h \
    projectmodels.h \
    currentprojectfind.h \
    toolchain.h \
    toolchainconfigwidget.h \
    toolchainmanager.h \
    toolchainoptionspage.h \
    cesdkhandler.h \
    gccparser.h \
#    projectexplorersettingspage.h \#ROOPAK
    baseprojectwizarddialog.h \
    miniprojecttargetselector.h \
    targetselector.h \
    targetsettingswidget.h \
#    doubletabwidget.h \#ROOPAK
    buildenvironmentwidget.h \
    ldparser.h \
    linuxiccparser.h \
    runconfigurationmodel.h \
    buildconfigurationmodel.h \
    processparameters.h \
#    abstractprocessstep.h \#ROOPAK
    taskhub.h \
    localapplicationruncontrol.h \
    metatypedeclarations.h \
    headerpath.h \
    gcctoolchainfactories.h \
#    appoutputpane.h \#ROOPAK
#    codestylesettingspropertiespage.h \ #ROOPAK
    settingsaccessor.h \
    environmentitemswidget.h \
    deployablefile.h \
    devicesupport/idevice.h \
    devicesupport/desktopdevice.h \
    devicesupport/desktopdevicefactory.h \
    devicesupport/idevicewidget.h \
    devicesupport/idevicefactory.h \
    devicesupport/desktopdeviceprocess.h \
    devicesupport/devicecheckbuildstep.h \
    devicesupport/devicemanager.h \
    devicesupport/devicemanagermodel.h \
    devicesupport/devicefactoryselectiondialog.h \
    devicesupport/deviceprocess.h \
    devicesupport/deviceprocesslist.h \
    devicesupport/deviceprocessesdialog.h \
    devicesupport/devicesettingswidget.h \
    devicesupport/devicesettingspage.h \
    devicesupport/devicetestdialog.h \
    devicesupport/devicetypekitchooser.h \
    devicesupport/deviceusedportsgatherer.h \
    devicesupport/deviceapplicationrunner.h \
    devicesupport/localprocesslist.h \
    devicesupport/sshdeviceprocess.h \
    devicesupport/sshdeviceprocesslist.h \
    devicesupport/desktopdeviceconfigurationwidget.h \
    devicesupport/desktopprocesssignaloperation.h \
    deploymentdata.h \
    buildtargetinfo.h \
    customtoolchain.h \
    projectmacroexpander.h \
    customparser.h \
#    customparserconfigdialog.h \#ROOPAK
    ipotentialkit.h \
    selectablefilesmodel.h \
    xcodebuildparser.h

SOURCES += projectexplorer.cpp \
    abi.cpp \
    abiwidget.cpp \
    ansifilterparser.cpp \
    clangparser.cpp \
    environmentaspect.cpp \
    environmentaspectwidget.cpp \
    gcctoolchain.cpp \
    importwidget.cpp \
    localapplicationrunconfiguration.cpp \
    localenvironmentaspect.cpp \
    osparser.cpp \
    projectimporter.cpp \
    projectwindow.cpp \
    removetaskhandler.cpp \
    targetsetuppage.cpp \
    targetsetupwidget.cpp \
    unconfiguredprojectpanel.cpp \
    kit.cpp \
    kitchooser.cpp \
    kitconfigwidget.cpp \
    kitinformation.cpp \
    kitinformationconfigwidget.cpp \
    kitmanager.cpp \
    kitmanagerconfigwidget.cpp \
    kitmodel.cpp \
    kitoptionspage.cpp \
    buildmanager.cpp \
    buildsteplist.cpp \
#    compileoutputwindow.cpp \#ROOPAK
    deployconfiguration.cpp \
    deployconfigurationmodel.cpp \
    namedwidget.cpp \
    target.cpp \
    targetsettingspanel.cpp \
    ioutputparser.cpp \
    projectconfiguration.cpp \
    gnumakeparser.cpp \
    task.cpp \
    copytaskhandler.cpp \
    showineditortaskhandler.cpp \
#    showoutputtaskhandler.cpp \#ROOPAK
    vcsannotatetaskhandler.cpp \
#    taskwindow.cpp \//ROOPAK
    taskmodel.cpp \
    projectfilewizardextension.cpp \
    session.cpp \
    dependenciespanel.cpp \
    allprojectsfilter.cpp \
    currentprojectfilter.cpp \
    allprojectsfind.cpp \
    project.cpp \
    pluginfilefactory.cpp \
    buildstep.cpp \
    buildconfiguration.cpp \
    buildsettingspropertiespage.cpp \
    environmentwidget.cpp \
#    processstep.cpp \#ROOPAK
#    abstractprocessstep.cpp \#ROOPAK
    editorconfiguration.cpp \
#    editorsettingspropertiespage.cpp \#ROOPAK
    runconfiguration.cpp \
    applicationlauncher.cpp \
    runsettingspropertiespage.cpp \
#    projecttreewidget.cpp \#ROOPAK
#    foldernavigationwidget.cpp \#ROOPAK
#    buildprogress.cpp \#ROOPAK
    projectnodes.cpp \
#    sessiondialog.cpp \#ROOPAK
#    projectwizardpage.cpp \#ROOPAK
    buildstepspage.cpp \
    nodesvisitor.cpp \
    projectmodels.cpp \
    currentprojectfind.cpp \
    toolchain.cpp \
    toolchainconfigwidget.cpp \
    toolchainmanager.cpp \
    toolchainoptionspage.cpp \
    cesdkhandler.cpp \
    gccparser.cpp \
#    projectexplorersettingspage.cpp \#ROOPAK
    corelistenercheckingforrunningbuild.cpp \
    baseprojectwizarddialog.cpp \
    miniprojecttargetselector.cpp \
    targetselector.cpp \
    targetsettingswidget.cpp \
#    doubletabwidget.cpp \#ROOPAK
    buildenvironmentwidget.cpp \
    ldparser.cpp \
    linuxiccparser.cpp \
    runconfigurationmodel.cpp \
    buildconfigurationmodel.cpp \
    taskhub.cpp \
    processparameters.cpp \
    localapplicationruncontrol.cpp \
#    appoutputpane.cpp \#ROOPAK
#    codestylesettingspropertiespage.cpp \#ROOPAK
    settingsaccessor.cpp \
    environmentitemswidget.cpp \
    devicesupport/idevice.cpp \
    devicesupport/desktopdevice.cpp \
    devicesupport/desktopdevicefactory.cpp \
    devicesupport/idevicefactory.cpp \
    devicesupport/desktopdeviceprocess.cpp \
    devicesupport/devicecheckbuildstep.cpp \
    devicesupport/devicemanager.cpp \
    devicesupport/devicemanagermodel.cpp \
    devicesupport/devicefactoryselectiondialog.cpp \
    devicesupport/deviceprocess.cpp \
    devicesupport/deviceprocesslist.cpp \
    devicesupport/deviceprocessesdialog.cpp \
    devicesupport/devicesettingswidget.cpp \
    devicesupport/devicesettingspage.cpp \
    devicesupport/devicetestdialog.cpp \
    devicesupport/devicetypekitchooser.cpp \
    devicesupport/deviceusedportsgatherer.cpp \
    devicesupport/deviceapplicationrunner.cpp \
    devicesupport/localprocesslist.cpp \
    devicesupport/sshdeviceprocess.cpp \
    devicesupport/sshdeviceprocesslist.cpp \
    devicesupport/desktopdeviceconfigurationwidget.cpp \
    devicesupport/desktopprocesssignaloperation.cpp \
    deployablefile.cpp \
    customtoolchain.cpp \
    projectmacroexpander.cpp \
    customparser.cpp \
#    customparserconfigdialog.cpp \#ROOPAK
    ipotentialkit.cpp \
    selectablefilesmodel.cpp \
    xcodebuildparser.cpp

FORMS += \#processstep.ui \#ROOPAK
#    editorsettingspropertiespage.ui \#ROOPAK
#    sessiondialog.ui \#ROOPAK
#    projectwizardpage.ui \#ROOPAK
#    projectexplorersettingspage.ui \#ROOPAK
    targetsettingswidget.ui \
#    doubletabwidget.ui \ #ROOPAK
#    codestylesettingspropertiespage.ui \#ROOPAK
    devicesupport/devicefactoryselectiondialog.ui \
    devicesupport/devicesettingswidget.ui \
    devicesupport/devicetestdialog.ui \
    devicesupport/desktopdeviceconfigurationwidget.ui \
#    customparserconfigdialog.ui#ROOPAK

WINSOURCES += \
    windebuginterface.cpp \
    msvcparser.cpp \
    msvctoolchain.cpp \
    abstractmsvctoolchain.cpp \
    wincetoolchain.cpp

WINHEADERS += \
    windebuginterface.h \
    msvcparser.h \
    msvctoolchain.h \
    abstractmsvctoolchain.h \
    wincetoolchain.h

win32|equals(TEST, 1) {
    SOURCES += $$WINSOURCES
    HEADERS += $$WINHEADERS
}

equals(TEST, 1) {
    SOURCES += \
        outputparser_test.cpp
    HEADERS += \
        outputparser_test.h
}

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += quick
#    HEADERS += projectwelcomepage.h//ROOPAK
#    SOURCES += projectwelcomepage.cpp//ROOPAK
}
macx:LIBS += -framework Carbon

RESOURCES += projectexplorer.qrc

# Some way to override the architecture used in Abi:
!isEmpty($$(QTC_CPU)) {
    DEFINES += QTC_CPU=$$(QTC_CPU)
} else {
    DEFINES += QTC_CPU=X86Architecture
}

DEFINES += PROJECTEXPLORER_LIBRARY

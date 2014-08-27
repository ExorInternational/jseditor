QT += xml script

include(../../qtcreatorplugin.pri)
#include(customwizard/customwizard.pri)//ROOPAK
HEADERS += projectexplorer.h \
    abi.h \
    abiwidget.h \
    ansifilterparser.h \
    buildinfo.h \
    clangparser.h \
    environmentaspect.h \
#    environmentaspectwidget.h \#ROOPAK
#    gcctoolchain.h \#ROOPAK
    importwidget.h \
    localapplicationrunconfiguration.h \
#    localenvironmentaspect.h \#ROOPAK
    osparser.h \
    projectexplorer_export.h \
#    projectimporter.h \#ROOPAK
#    projectwindow.h \#ROOPAK
#    removetaskhandler.h \#ROOPAK
#    targetsetuppage.h \ #ROOPAK
#    targetsetupwidget.h \#ROOPAK
#    unconfiguredprojectpanel.h \#ROOPAK
    kit.h \
#    kitchooser.h \#ROOPAK
    kitconfigwidget.h \
    kitinformation.h \
#    kitinformationconfigwidget.h \ #ROOPAK
    kitmanager.h \
#    kitmanagerconfigwidget.h \#ROOPAK
#    kitmodel.h \#ROOPAK
#    kitoptionspage.h \#ROOPAK
    buildmanager.h \
    buildsteplist.h \
#    compileoutputwindow.h \#ROOPAK
    deployconfiguration.h \
    deployconfigurationmodel.h \
    namedwidget.h \
    target.h \
#    targetsettingspanel.h \#ROOPAK
    task.h \
    itaskhandler.h \
#    copytaskhandler.h \#ROOPAK
#    showineditortaskhandler.h \ #ROOPAK
#    showoutputtaskhandler.h \#ROOPAK
#    vcsannotatetaskhandler.h \#ROOPAK
#    taskwindow.h \//ROOPAK
    taskmodel.h \
    projectfilewizardextension.h \
    session.h \
    dependenciespanel.h \
#    allprojectsfilter.h \#ROOPAK
    ioutputparser.h \
    projectconfiguration.h \
    gnumakeparser.h \
    projectexplorerconstants.h \
    projectexplorersettings.h \
#    corelistenercheckingforrunningbuild.h \#ROOPAK
    project.h \
    pluginfilefactory.h \
    iprojectmanager.h \
#    currentprojectfilter.h \#ROOPAK
    allprojectsfind.h \
    buildstep.h \
    buildconfiguration.h \
    iprojectproperties.h \
#    buildsettingspropertiespage.h \#ROOPAK
#    environmentwidget.h \#ROOPAK
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
#    toolchainoptionspage.h \#ROOPAK
    cesdkhandler.h \
    gccparser.h \
#    projectexplorersettingspage.h \#ROOPAK
    baseprojectwizarddialog.h \
    miniprojecttargetselector.h \
    targetselector.h \
#    targetsettingswidget.h \ #ROOPAK
#    doubletabwidget.h \#ROOPAK
#    buildenvironmentwidget.h \ #ROOPAK
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
#    gcctoolchainfactories.h \#ROOPAK
#    appoutputpane.h \#ROOPAK
#    codestylesettingspropertiespage.h \ #ROOPAK
    settingsaccessor.h \
#    environmentitemswidget.h \#ROOPAK
    deployablefile.h \
    devicesupport/idevice.h \
#    devicesupport/desktopdevice.h \#ROOPAK
#    devicesupport/desktopdevicefactory.h \#ROOPAK
    devicesupport/idevicewidget.h \
    devicesupport/idevicefactory.h \
#    devicesupport/desktopdeviceprocess.h \ #ROOPAK
#    devicesupport/devicecheckbuildstep.h \#ROOPAK
    devicesupport/devicemanager.h \
#    devicesupport/devicemanagermodel.h \ #ROOPAK
#    devicesupport/devicefactoryselectiondialog.h \#ROOPAK
#    devicesupport/deviceprocess.h \ #ROOPAK
#    devicesupport/deviceprocesslist.h \ #ROOPAK
#    devicesupport/deviceprocessesdialog.h \#ROOPAK
#    devicesupport/devicesettingswidget.h \#ROOPAK
#    devicesupport/devicesettingspage.h \#ROOPAK
#    devicesupport/devicetestdialog.h \ #ROOPAK
#    devicesupport/devicetypekitchooser.h \#ROOPAK
#    devicesupport/deviceusedportsgatherer.h \#ROOPAK
#    devicesupport/deviceapplicationrunner.h \#ROOPAK
#    devicesupport/localprocesslist.h \#ROOPAK
#    devicesupport/sshdeviceprocess.h \#ROOPAK
#    devicesupport/sshdeviceprocesslist.h \#ROOPAK
#    devicesupport/desktopdeviceconfigurationwidget.h \#ROOPAK
#    devicesupport/desktopprocesssignaloperation.h \#ROOPAK
    deploymentdata.h \
    buildtargetinfo.h \
#    customtoolchain.h \#ROOPAK
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
#    environmentaspectwidget.cpp \#ROOPAK
#    gcctoolchain.cpp \#ROOPAK
    importwidget.cpp \
    localapplicationrunconfiguration.cpp \
#    localenvironmentaspect.cpp \#ROOPAK
    osparser.cpp \
#    projectimporter.cpp \#ROOPAK
#    projectwindow.cpp \#ROOPAK
#    removetaskhandler.cpp \#ROOPAK
#    targetsetuppage.cpp \#ROOPAK
#    targetsetupwidget.cpp \#ROOPAK
#    unconfiguredprojectpanel.cpp \#ROOPAK
    kit.cpp \
#    kitchooser.cpp \#ROOPAK
    kitconfigwidget.cpp \
    kitinformation.cpp \
#    kitinformationconfigwidget.cpp \ #ROOPAK
    kitmanager.cpp \
#    kitmanagerconfigwidget.cpp \ #ROOPAK
#    kitmodel.cpp \#ROOPAK
#    kitoptionspage.cpp \#ROOPAK
    buildmanager.cpp \
    buildsteplist.cpp \
#    compileoutputwindow.cpp \#ROOPAK
    deployconfiguration.cpp \
    deployconfigurationmodel.cpp \
    namedwidget.cpp \
    target.cpp \
#    targetsettingspanel.cpp \#ROOPAK
    ioutputparser.cpp \
    projectconfiguration.cpp \
    gnumakeparser.cpp \
    task.cpp \
#    copytaskhandler.cpp \#ROOPAK
#    showineditortaskhandler.cpp \ #ROOPAK
#    showoutputtaskhandler.cpp \#ROOPAK
#    vcsannotatetaskhandler.cpp \#ROOPAK
#    taskwindow.cpp \//ROOPAK
    taskmodel.cpp \
    projectfilewizardextension.cpp \
    session.cpp \
    dependenciespanel.cpp \
#    allprojectsfilter.cpp \#ROOPAK
#    currentprojectfilter.cpp \#ROOPAK
    allprojectsfind.cpp \
    project.cpp \
    pluginfilefactory.cpp \
    buildstep.cpp \
    buildconfiguration.cpp \
#    buildsettingspropertiespage.cpp \#ROOPAK
#    environmentwidget.cpp \#ROOPAK
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
#    toolchainoptionspage.cpp \#ROOPAK
    cesdkhandler.cpp \
    gccparser.cpp \
#    projectexplorersettingspage.cpp \#ROOPAK
#    corelistenercheckingforrunningbuild.cpp \#ROOPAK
    baseprojectwizarddialog.cpp \
    miniprojecttargetselector.cpp \
    targetselector.cpp \
#    targetsettingswidget.cpp \#ROOPAK
#    doubletabwidget.cpp \#ROOPAK
#    buildenvironmentwidget.cpp \ #ROOPAK
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
#    environmentitemswidget.cpp \#ROOPAK
    devicesupport/idevice.cpp \
#    devicesupport/desktopdevice.cpp \ #ROOPAK
#    devicesupport/desktopdevicefactory.cpp \#ROOPAK
    devicesupport/idevicefactory.cpp \
#    devicesupport/desktopdeviceprocess.cpp \ #ROOPAK
#    devicesupport/devicecheckbuildstep.cpp \#ROOPAK
    devicesupport/devicemanager.cpp \
#    devicesupport/devicemanagermodel.cpp \ #ROOPAK
#    devicesupport/devicefactoryselectiondialog.cpp \#ROOPAK
#    devicesupport/deviceprocess.cpp \#ROOPAK
#    devicesupport/deviceprocesslist.cpp \#ROOPAK
#    devicesupport/deviceprocessesdialog.cpp \#ROOPAK
#    devicesupport/devicesettingswidget.cpp \#ROOPAK
#    devicesupport/devicesettingspage.cpp \#ROOPAK
#    devicesupport/devicetestdialog.cpp \#ROOPAK
#    devicesupport/devicetypekitchooser.cpp \#ROOPAK
#    devicesupport/deviceusedportsgatherer.cpp \#ROOPAK
#    devicesupport/deviceapplicationrunner.cpp \#ROOPAK
#    devicesupport/localprocesslist.cpp \#ROOPAK
#    devicesupport/sshdeviceprocess.cpp \#ROOPAK
#    devicesupport/sshdeviceprocesslist.cpp \#ROOPAK
#    devicesupport/desktopdeviceconfigurationwidget.cpp \#ROOPAK
#    devicesupport/desktopprocesssignaloperation.cpp \ #ROOPAK
    deployablefile.cpp \
#    customtoolchain.cpp \#ROOPAK
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
#    targetsettingswidget.ui \#ROOPAK
#    doubletabwidget.ui \ #ROOPAK
#    codestylesettingspropertiespage.ui \#ROOPAK
#    devicesupport/devicefactoryselectiondialog.ui \ #ROOPAK
#    devicesupport/devicesettingswidget.ui \ #ROOPAK
#    devicesupport/devicetestdialog.ui \ #ROOPAK
#    devicesupport/desktopdeviceconfigurationwidget.ui \#ROOPAK
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

QT += xml script

include(../../qtcreatorplugin.pri)
#include(customwizard/customwizard.pri)//ROOPAK
HEADERS += projectexplorer.h \
#    abi.h \//#720 ROOPAK
#    abiwidget.h \#ROOPAK
#    ansifilterparser.h \#ROOPAK
#    buildinfo.h \#ROOPAK
#    clangparser.h \#ROOPAK
#    environmentaspect.h \#ROOPAK
#    environmentaspectwidget.h \#ROOPAK
#    gcctoolchain.h \#ROOPAK
#    importwidget.h \#ROOPAK
#    localapplicationrunconfiguration.h \#ROOPAK
#    localenvironmentaspect.h \#ROOPAK
#    osparser.h \ #ROOPAK
    projectexplorer_export.h \
#    projectimporter.h \#ROOPAK
#    projectwindow.h \#ROOPAK
#    removetaskhandler.h \#ROOPAK
#    targetsetuppage.h \ #ROOPAK
#    targetsetupwidget.h \#ROOPAK
#    unconfiguredprojectpanel.h \#ROOPAK
#    kit.h \//#720 ROOPAK
#    kitchooser.h \#ROOPAK
#    kitconfigwidget.h \//#720 ROOPAK
#    kitinformation.h \//#720 ROOPAK
#    kitinformationconfigwidget.h \ #ROOPAK
#    kitmanager.h \//#720 ROOPAK
#    kitmanagerconfigwidget.h \#ROOPAK
#    kitmodel.h \#ROOPAK
#    kitoptionspage.h \#ROOPAK
#    buildmanager.h \#ROOPAK
#    buildsteplist.h \#ROOPAK
#    compileoutputwindow.h \#ROOPAK
#    deployconfiguration.h \#ROOPAK
#    deployconfigurationmodel.h \ #ROOPAK
#    namedwidget.h \//#720 ROOPAK
#    target.h \//#720 ROOPAK
#    targetsettingspanel.h \#ROOPAK
#    task.h \//#720 ROOPAK
#    itaskhandler.h \#ROOPAK
#    copytaskhandler.h \#ROOPAK
#    showineditortaskhandler.h \ #ROOPAK
#    showoutputtaskhandler.h \#ROOPAK
#    vcsannotatetaskhandler.h \#ROOPAK
#    taskwindow.h \//ROOPAK
#    taskmodel.h \#ROOPAK
#    projectfilewizardextension.h \#ROOPAK
#    session.h \//#720 ROOPAK
#    dependenciespanel.h \#ROOPAK
#    allprojectsfilter.h \#ROOPAK
#    ioutputparser.h \//#720 ROOPAK
#    projectconfiguration.h \//#720 ROOPAK
#    gnumakeparser.h \#ROOPAK
    projectexplorerconstants.h \
#    projectexplorersettings.h \#ROOPAK
#    corelistenercheckingforrunningbuild.h \#ROOPAK
    project.h \
#    pluginfilefactory.h \#ROOPAK
#    iprojectmanager.h \//#720 ROOPAK
#    currentprojectfilter.h \#ROOPAK
#    allprojectsfind.h \//#720 ROOPAK
#    buildstep.h \#ROOPAK
#    buildconfiguration.h \#ROOPAK
#    iprojectproperties.h \//#720 ROOPAK
#    buildsettingspropertiespage.h \#ROOPAK
#    environmentwidget.h \#ROOPAK
#    processstep.h \#ROOPAK
#    editorconfiguration.h \//#720 ROOPAK
#    editorsettingspropertiespage.h \#ROOPAK
#    runconfiguration.h \#720 ROOPAK
#    applicationlauncher.h \#ROOPAK
#    runsettingspropertiespage.h \#ROOPAK
#    projecttreewidget.h \ #ROOPAK
#    foldernavigationwidget.h \#ROOPAK
#    buildprogress.h \#ROOPAK
#    projectnodes.h \#ROOPAK
#    sessiondialog.h \#ROOPAK
#    projectwizardpage.h \#ROOPAK
#    buildstepspage.h \#ROOPAK
#    nodesvisitor.h \#ROOPAK
#    projectmodels.h \#ROOPAK
#    currentprojectfind.h \//#720 ROOPAK
#    toolchain.h \//#720 ROOPAK
#    toolchainconfigwidget.h \#ROOPAK
#    toolchainmanager.h \//#720 ROOPAK
#    toolchainoptionspage.h \#ROOPAK
#    cesdkhandler.h \#ROOPAK
#    gccparser.h \#ROOPAK
#    projectexplorersettingspage.h \#ROOPAK
#    baseprojectwizarddialog.h \#ROOPAK
#    miniprojecttargetselector.h \#ROOPAK
#    targetselector.h \#ROOPAK
#    targetsettingswidget.h \ #ROOPAK
#    doubletabwidget.h \#ROOPAK
#    buildenvironmentwidget.h \ #ROOPAK
#    ldparser.h \#ROOPAK
#    linuxiccparser.h \#ROOPAK
#    runconfigurationmodel.h \#ROOPAK
#    buildconfigurationmodel.h \#ROOPAK
#    processparameters.h \#ROOPAK
#    abstractprocessstep.h \#ROOPAK
#    taskhub.h \//#720 ROOPAK
#    localapplicationruncontrol.h \#ROOPAK
#    metatypedeclarations.h \//#720 ROOPAK
#    headerpath.h \//#720 ROOPAK
#    gcctoolchainfactories.h \#ROOPAK
#    appoutputpane.h \#ROOPAK
#    codestylesettingspropertiespage.h \ #ROOPAK
#    settingsaccessor.h \#ROOPAK
#    environmentitemswidget.h \#ROOPAK
#    deployablefile.h \#ROOPAK
#    devicesupport/idevice.h \#ROOPAK
#    devicesupport/desktopdevice.h \#ROOPAK
#    devicesupport/desktopdevicefactory.h \#ROOPAK
#    devicesupport/idevicewidget.h \#ROOPAK
#    devicesupport/idevicefactory.h \#ROOPAK
#    devicesupport/desktopdeviceprocess.h \ #ROOPAK
#    devicesupport/devicecheckbuildstep.h \#ROOPAK
#    devicesupport/devicemanager.h \#ROOPAK
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
#    deploymentdata.h \#ROOPAK
#    buildtargetinfo.h \#ROOPAK
#    customtoolchain.h \#ROOPAK
#    projectmacroexpander.h \#ROOPAK
#    customparser.h \#ROOPAK
#    customparserconfigdialog.h \#ROOPAK
#    ipotentialkit.h \#ROOPAK
#    selectablefilesmodel.h \#ROOPAK
#    xcodebuildparser.h#ROOPAK

SOURCES += projectexplorer.cpp \
#    abi.cpp \//#720 ROOPAK
#    abiwidget.cpp \#ROOPAK
#    ansifilterparser.cpp \#ROOPAK
#    clangparser.cpp \#ROOPAK
#    environmentaspect.cpp \#ROOPAK
#    environmentaspectwidget.cpp \#ROOPAK
#    gcctoolchain.cpp \#ROOPAK
#    importwidget.cpp \#ROOPAK
#    localapplicationrunconfiguration.cpp \#ROOPAK
#    localenvironmentaspect.cpp \#ROOPAK
#    osparser.cpp \#ROOPAK
#    projectimporter.cpp \#ROOPAK
#    projectwindow.cpp \#ROOPAK
#    removetaskhandler.cpp \#ROOPAK
#    targetsetuppage.cpp \#ROOPAK
#    targetsetupwidget.cpp \#ROOPAK
#    unconfiguredprojectpanel.cpp \#ROOPAK
#    kit.cpp \//#720 ROOPAK
#    kitchooser.cpp \#ROOPAK
#    kitconfigwidget.cpp \//#720 ROOPAK
#    kitinformation.cpp \//#720 ROOPAK
#    kitinformationconfigwidget.cpp \ #ROOPAK
#    kitmanager.cpp \//#720 ROOPAK
#    kitmanagerconfigwidget.cpp \ #ROOPAK
#    kitmodel.cpp \#ROOPAK
#    kitoptionspage.cpp \#ROOPAK
#    buildmanager.cpp \#ROOPAK
#    buildsteplist.cpp \#ROOPAK
#    compileoutputwindow.cpp \#ROOPAK
#    deployconfiguration.cpp \#ROOPAK
#    deployconfigurationmodel.cpp \#ROOPAK
#    namedwidget.cpp \//#720 ROOPAK
#    target.cpp \//#720 ROOPAK
#    targetsettingspanel.cpp \#ROOPAK
#    ioutputparser.cpp \//#720 ROOPAK
#    projectconfiguration.cpp \//#720 ROOPAK
#    gnumakeparser.cpp \#ROOPAK
#    task.cpp \//#720 ROOPAK
#    copytaskhandler.cpp \#ROOPAK
#    showineditortaskhandler.cpp \ #ROOPAK
#    showoutputtaskhandler.cpp \#ROOPAK
#    vcsannotatetaskhandler.cpp \#ROOPAK
#    taskwindow.cpp \//ROOPAK
#    taskmodel.cpp \#ROOPAK
#    projectfilewizardextension.cpp \#ROOPAK
#    session.cpp \//#720 ROOPAK
#    dependenciespanel.cpp \#ROOPAK
#    allprojectsfilter.cpp \#ROOPAK
#    currentprojectfilter.cpp \#ROOPAK
#    allprojectsfind.cpp \//#720 ROOPAK
    project.cpp \
#    pluginfilefactory.cpp \#ROOPAK
#    buildstep.cpp \#ROOPAK
#    buildconfiguration.cpp \#ROOPAK
#    buildsettingspropertiespage.cpp \#ROOPAK
#    environmentwidget.cpp \#ROOPAK
#    processstep.cpp \#ROOPAK
#    abstractprocessstep.cpp \#ROOPAK
#    editorconfiguration.cpp \//#720 ROOPAK
#    editorsettingspropertiespage.cpp \#ROOPAK
#    runconfiguration.cpp \#720 #ROOPAK
#    applicationlauncher.cpp \#ROOPAK
#    runsettingspropertiespage.cpp \#ROOPAK
#    projecttreewidget.cpp \#ROOPAK
#    foldernavigationwidget.cpp \#ROOPAK
#    buildprogress.cpp \#ROOPAK
#    projectnodes.cpp \#ROOPAK
#    sessiondialog.cpp \#ROOPAK
#    projectwizardpage.cpp \#ROOPAK
#    buildstepspage.cpp \#ROOPAK
#    nodesvisitor.cpp \#ROOPAK
#    projectmodels.cpp \#ROOPAK
#    currentprojectfind.cpp \//#720 ROOPAK
#    toolchain.cpp \//#720 ROOPAK
#    toolchainconfigwidget.cpp \#ROOPAK
#    toolchainmanager.cpp \//#720 ROOPAK
#    toolchainoptionspage.cpp \#ROOPAK
#    cesdkhandler.cpp \#ROOPAK
#    gccparser.cpp \#ROOPAK
#    projectexplorersettingspage.cpp \#ROOPAK
#    corelistenercheckingforrunningbuild.cpp \#ROOPAK
#    baseprojectwizarddialog.cpp \#ROOPAK
#    miniprojecttargetselector.cpp \#ROOPAK
#    targetselector.cpp \#ROOPAK
#    targetsettingswidget.cpp \#ROOPAK
#    doubletabwidget.cpp \#ROOPAK
#    buildenvironmentwidget.cpp \ #ROOPAK
#    ldparser.cpp \#ROOPAK
#    linuxiccparser.cpp \#ROOPAK
#    runconfigurationmodel.cpp \#ROOPAK
#    buildconfigurationmodel.cpp \#ROOPAK
#    taskhub.cpp \//#720 ROOPAK
#    processparameters.cpp \#ROOPAK
#    localapplicationruncontrol.cpp \#ROOPAK
#    appoutputpane.cpp \#ROOPAK
#    codestylesettingspropertiespage.cpp \#ROOPAK
#    settingsaccessor.cpp \#ROOPAK
#    environmentitemswidget.cpp \#ROOPAK
#    devicesupport/idevice.cpp \#ROOPAK
#    devicesupport/desktopdevice.cpp \ #ROOPAK
#    devicesupport/desktopdevicefactory.cpp \#ROOPAK
#    devicesupport/idevicefactory.cpp \#ROOPAK
#    devicesupport/desktopdeviceprocess.cpp \ #ROOPAK
#    devicesupport/devicecheckbuildstep.cpp \#ROOPAK
#    devicesupport/devicemanager.cpp \#ROOPAK
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
#    deployablefile.cpp \#ROOPAK
#    customtoolchain.cpp \#ROOPAK
#    projectmacroexpander.cpp \#ROOPAK
#    customparser.cpp \#ROOPAK
#    customparserconfigdialog.cpp \#ROOPAK
#    ipotentialkit.cpp \#ROOPAK
#    selectablefilesmodel.cpp \#ROOPAK
#    xcodebuildparser.cpp#ROOPAK

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
#    windebuginterface.cpp \//#720 ROOPAK
#    msvcparser.cpp \#ROOPAK
#    msvctoolchain.cpp \#ROOPAK
#    abstractmsvctoolchain.cpp \#ROOPAK
#    wincetoolchain.cpp#ROOPAK

WINHEADERS += \
#    windebuginterface.h \//#720 ROOPAK
#    msvcparser.h \#ROOPAK
#    msvctoolchain.h \#ROOPAK
#    abstractmsvctoolchain.h \#ROOPAK
#    wincetoolchain.h#ROOPAK

win32|equals(TEST, 1) {
    SOURCES += $$WINSOURCES
    HEADERS += $$WINHEADERS
}

#equals(TEST, 1) {//#720 ROOPAK - START
#    SOURCES += \
#        outputparser_test.cpp
#    HEADERS += \
#        outputparser_test.h
#}//#720 ROOPAK - END

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

QTC_PLUGIN_NAME = QtSupport
QTC_LIB_DEPENDS += \
    aggregation \
    extensionsystem \
    qmljs \
    utils
QTC_PLUGIN_DEPENDS += \
    coreplugin #\
#    cpptools \//#720 ROOPAK
#    projectexplorer//#720 ROOPAK
DEFINES *= \
    QMAKE_AS_LIBRARY \
    PROPARSER_THREAD_SAFE \
    PROEVALUATOR_THREAD_SAFE \
    PROEVALUATOR_CUMULATIVE \
    PROEVALUATOR_SETENV
INCLUDEPATH *= $$PWD/../../shared

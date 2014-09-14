DEFINES += CPPTOOLS_LIBRARY
win32-msvc*:DEFINES += _SCL_SECURE_NO_WARNINGS
include(../../qtcreatorplugin.pri)

HEADERS += \
#    abstracteditorsupport.h \//#720 ROOPAK
#    builtinindexingsupport.h \//#720 ROOPAK
#    commentssettings.h \//#720 ROOPAK
#    completionsettingspage.h \//#720 ROOPAK
    cppchecksymbols.h \
#    cppclassesfilter.h \//#720 ROOPAK
    cppcodeformatter.h \
#    cppcodemodelinspectordumper.h \//#720 ROOPAK
    cppcodemodelsettings.h \
    cppcodemodelsettingspage.h \
    cppcodestylepreferences.h \
    cppcodestylepreferencesfactory.h \
    cppcodestylesettings.h \
    cppcodestylesettingspage.h \
#    cppcompletionassist.h \//#720 ROOPAK
    cppcompletionassistprovider.h \
#    cppcurrentdocumentfilter.h \//#720 ROOPAK
    cppdoxygen.h \
    cppfilesettingspage.h \
#    cppfindreferences.h \//#720 ROOPAK
#    cppfunctionsfilter.h \//#720 ROOPAK
    cpphighlightingsupport.h \
    cpphighlightingsupportinternal.h \
#    cppindexingsupport.h \//#720 ROOPAK
    cpplocalsymbols.h \
#    cpplocatordata.h \//#720 ROOPAK
#    cpplocatorfilter.h \//#720 ROOPAK
#    cppmodelmanager.h \//#720 ROOPAK
#    cppmodelmanagerinterface.h \//#720 ROOPAK
    cppmodelmanagersupport.h \
    cppmodelmanagersupportinternal.h \
#    cpppointerdeclarationformatter.h \//#720 ROOPAK
#    cpppreprocessor.h \//#720 ROOPAK
    cppprojectfile.h \
    cppqtstyleindenter.h \
#    cpprefactoringchanges.h \//#720 ROOPAK
    cppsemanticinfo.h \
#    cppsnapshotupdater.h \//#720 ROOPAK
    cpptools_global.h \
    cpptoolsconstants.h \
#    cpptoolseditorsupport.h \//#720 ROOPAK
    cpptoolsplugin.h \
    cpptoolsreuse.h \
    cpptoolssettings.h \
    doxygengenerator.h \
    functionutils.h \
    includeutils.h \
    insertionpointlocator.h \
#    searchsymbols.h \//#720 ROOPAK
    symbolfinder.h \
#    symbolsfindfilter.h \//#720 ROOPAK
#    typehierarchybuilder.h//#720 ROOPAK

SOURCES += \
#    abstracteditorsupport.cpp \//#720 ROOPAK
#    builtinindexingsupport.cpp \//#720 ROOPAK
#    commentssettings.cpp \//#720 ROOPAK
#    completionsettingspage.cpp \//#720 ROOPAK
    cppchecksymbols.cpp \
#    cppclassesfilter.cpp \//#720 ROOPAK
    cppcodeformatter.cpp \
#    cppcodemodelinspectordumper.cpp \//#720 ROOPAK
    cppcodemodelsettings.cpp \
    cppcodemodelsettingspage.cpp \
    cppcodestylepreferences.cpp \
    cppcodestylepreferencesfactory.cpp \
    cppcodestylesettings.cpp \
    cppcodestylesettingspage.cpp \
#    cppcompletionassist.cpp \//#720 ROOPAK
    cppcompletionassistprovider.cpp \
#    cppcurrentdocumentfilter.cpp \//#720 ROOPAK
    cppdoxygen.cpp \
    cppfilesettingspage.cpp \
#    cppfindreferences.cpp \//#720 ROOPAK
#    cppfunctionsfilter.cpp \//#720 ROOPAK
    cpphighlightingsupport.cpp \
    cpphighlightingsupportinternal.cpp \
#    cppindexingsupport.cpp \//#720 ROOPAK
    cpplocalsymbols.cpp \
#    cpplocatordata.cpp \//#720 ROOPAK
#    cpplocatorfilter.cpp \//#720 ROOPAK
#    cppmodelmanager.cpp \//#720 ROOPAK
#    cppmodelmanagerinterface.cpp \//#720 ROOPAK
    cppmodelmanagersupport.cpp \
    cppmodelmanagersupportinternal.cpp \
#    cpppointerdeclarationformatter.cpp \//#720 ROOPAK
#    cpppreprocessor.cpp \//#720 ROOPAK
    cppprojectfile.cpp \
    cppqtstyleindenter.cpp \
#    cpprefactoringchanges.cpp \//#720 ROOPAK
    cppsemanticinfo.cpp \
#    cppsnapshotupdater.cpp \//#720 ROOPAK
#    cpptoolseditorsupport.cpp \//#720 ROOPAK
    cpptoolsplugin.cpp \
    cpptoolsreuse.cpp \
    cpptoolssettings.cpp \
    doxygengenerator.cpp \
    functionutils.cpp \
    includeutils.cpp \
    insertionpointlocator.cpp \
#    searchsymbols.cpp \//#720 ROOPAK
    symbolfinder.cpp \
#    symbolsfindfilter.cpp \//#720 ROOPAK
#    typehierarchybuilder.cpp//#720 ROOPAK

FORMS += \
#    completionsettingspage.ui \//#720 ROOPAK
    cppcodemodelsettingspage.ui \
    cppcodestylesettingspage.ui \
    cppfilesettingspage.ui

#equals(TEST, 1) {//#720 ROOPAK - START
#    HEADERS += \
#        cpppreprocessertesthelper.h \
#        cpptoolstestcase.h \
#        modelmanagertesthelper.h

#    SOURCES += \
#        cppcodegen_test.cpp \
#        cppcompletion_test.cpp \
#        cppheadersource_test.cpp \
#        cpplocatorfilter_test.cpp \
#        cppmodelmanager_test.cpp \
#        cpppointerdeclarationformatter_test.cpp \
#        cpppreprocessertesthelper.cpp \
#        cpppreprocessor_test.cpp \
#        cpptoolstestcase.cpp \
#        modelmanagertesthelper.cpp \
#        symbolsearcher_test.cpp \
#        typehierarchybuilder_test.cpp

#    DEFINES += SRCDIR=\\\"$$PWD\\\"
#}//#720 ROOPAK - END

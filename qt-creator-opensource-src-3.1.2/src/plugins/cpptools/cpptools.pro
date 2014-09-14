DEFINES += CPPTOOLS_LIBRARY
win32-msvc*:DEFINES += _SCL_SECURE_NO_WARNINGS
include(../../qtcreatorplugin.pri)

HEADERS += \
#    abstracteditorsupport.h \//#720 ROOPAK
#    builtinindexingsupport.h \//#720 ROOPAK
#    commentssettings.h \//#720 ROOPAK
#    completionsettingspage.h \//#720 ROOPAK
#    cppchecksymbols.h \//#720 ROOPAK
#    cppclassesfilter.h \//#720 ROOPAK
#    cppcodeformatter.h \//#720 ROOPAK
#    cppcodemodelinspectordumper.h \//#720 ROOPAK
#    cppcodemodelsettings.h \//#720 ROOPAK
#    cppcodemodelsettingspage.h \//#720 ROOPAK
    cppcodestylepreferences.h \
#    cppcodestylepreferencesfactory.h \//#720 ROOPAK
    cppcodestylesettings.h \
#    cppcodestylesettingspage.h \//#720 ROOPAK
#    cppcompletionassist.h \//#720 ROOPAK
#    cppcompletionassistprovider.h \//#720 ROOPAK
#    cppcurrentdocumentfilter.h \//#720 ROOPAK
#    cppdoxygen.h \//#720 ROOPAK
#    cppfilesettingspage.h \//#720 ROOPAK
#    cppfindreferences.h \//#720 ROOPAK
#    cppfunctionsfilter.h \//#720 ROOPAK
#    cpphighlightingsupport.h \//#720 ROOPAK
#    cpphighlightingsupportinternal.h \//#720 ROOPAK
#    cppindexingsupport.h \//#720 ROOPAK
#    cpplocalsymbols.h \//#720 ROOPAK
#    cpplocatordata.h \//#720 ROOPAK
#    cpplocatorfilter.h \//#720 ROOPAK
#    cppmodelmanager.h \//#720 ROOPAK
#    cppmodelmanagerinterface.h \//#720 ROOPAK
#    cppmodelmanagersupport.h \//#720 ROOPAK
#    cppmodelmanagersupportinternal.h \//#720 ROOPAK
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
#    cppchecksymbols.cpp \//#720 ROOPAK
#    cppclassesfilter.cpp \//#720 ROOPAK
#    cppcodeformatter.cpp \//#720 ROOPAK
#    cppcodemodelinspectordumper.cpp \//#720 ROOPAK
#    cppcodemodelsettings.cpp \//#720 ROOPAK
#    cppcodemodelsettingspage.cpp \//#720 ROOPAK
    cppcodestylepreferences.cpp \
#    cppcodestylepreferencesfactory.cpp \//#720 ROOPAK
    cppcodestylesettings.cpp \
#    cppcodestylesettingspage.cpp \//#720 ROOPAK
#    cppcompletionassist.cpp \//#720 ROOPAK
#    cppcompletionassistprovider.cpp \//#720 ROOPAK
#    cppcurrentdocumentfilter.cpp \//#720 ROOPAK
#    cppdoxygen.cpp \//#720 ROOPAK
#    cppfilesettingspage.cpp \//#720 ROOPAK
#    cppfindreferences.cpp \//#720 ROOPAK
#    cppfunctionsfilter.cpp \//#720 ROOPAK
#    cpphighlightingsupport.cpp \//#720 ROOPAK
#    cpphighlightingsupportinternal.cpp \//#720 ROOPAK
#    cppindexingsupport.cpp \//#720 ROOPAK
#    cpplocalsymbols.cpp \//#720 ROOPAK
#    cpplocatordata.cpp \//#720 ROOPAK
#    cpplocatorfilter.cpp \//#720 ROOPAK
#    cppmodelmanager.cpp \//#720 ROOPAK
#    cppmodelmanagerinterface.cpp \//#720 ROOPAK
#    cppmodelmanagersupport.cpp \//#720 ROOPAK
#    cppmodelmanagersupportinternal.cpp \//#720 ROOPAK
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
#    cppcodemodelsettingspage.ui \//#720 ROOPAK
#    cppcodestylesettingspage.ui \//#720 ROOPAK
#    cppfilesettingspage.ui//#720 ROOPAK

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

cd %~dp0

@echo off
set QT_DIR=C:\Qt_shadowbuild\Qt484\build-win32\bin

@echo on
"%QT_DIR%\lconvert.exe" -locations relative ".\po_files\jseditortools_es.po" -o "jseditortools_es.ts"
"%QT_DIR%\lconvert.exe" -locations relative ".\po_files\jseditortools_de.po" -o "jseditortools_de.ts"
"%QT_DIR%\lconvert.exe" -locations relative ".\po_files\jseditortools_fr.po" -o "jseditortools_fr.ts"
"%QT_DIR%\lconvert.exe" -locations relative ".\po_files\jseditortools_it.po" -o "jseditortools_it.ts"


cd %~dp0

@echo off
set QT_DIR=C:\Qt_shadowbuild\Qt484\build-win32\bin

@echo on
"%QT_DIR%\lrelease.exe" ".\jseditortools_es.ts" -qm "..\Resources\translations\jseditortools_es.qm"
"%QT_DIR%\lrelease.exe" ".\jseditortools_de.ts" -qm "..\Resources\translations\jseditortools_de.qm"
"%QT_DIR%\lrelease.exe" ".\jseditortools_fr.ts" -qm "..\Resources\translations\jseditortools_fr.qm"
"%QT_DIR%\lrelease.exe" ".\jseditortools_it.ts" -qm "..\Resources\translations\jseditortools_it.qm"


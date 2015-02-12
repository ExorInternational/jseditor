cd %~dp0

@echo off
set QT_DIR=C:\Qt_shadowbuild\Qt484\build-win32\bin

@echo on
"%QT_DIR%\lupdate.exe" "..\jseditortools.pro" -ts "jseditortools_en.ts"

"%QT_DIR%\lconvert.exe" jseditortools_en.ts -o ".\po_files\jseditortools_en.po"

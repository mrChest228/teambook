@echo off
rem Starts txt2typ in its own window and typst watch in this one
cd /d "%~dp0"
start "txt2typ" txt2typ.exe
typst watch TeamBook.typ --font-path fonts
taskkill /im txt2typ.exe >nul 2>&1

@echo off

set v_filePath=%1
setlocal enabledelayedexpansion
for /r %%i in (%v_filePath%) do (
set s=%%i
set s=!s:%~dp0=!
set s=!s:\=\\!
echo !s!
)
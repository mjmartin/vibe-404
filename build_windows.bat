@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64
set "CMAKEDIR=C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
set "NINJADIR=C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja"
set "PATH=%CMAKEDIR%;%NINJADIR%;%PATH%"
cd /d "%~dp0"
cmake --preset windows-debug
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
cmake --build --preset build-windows-debug

@echo off
REM Change directory to your project root
cd /d %~dp0

REM Create and change to the build directory
if not exist out mkdir out
cd out

REM Configure and build the project
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release

echo Build completed.
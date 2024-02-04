@echo off
cd /d %~dp0\out

REM Run tests
ctest -C Release

echo Testing completed.
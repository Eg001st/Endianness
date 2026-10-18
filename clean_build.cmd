:: script\clean_build.cmd <preset>
@echo off
set "PRESET=%~1"
set "BUILD_DIR="

if "%PRESET%"=="msvc-debug" set "BUILD_DIR=build\msvc"
if "%PRESET%"=="msvc-release" set "BUILD_DIR=build\msvc"
if "%PRESET%"=="msvc-asan" set "BUILD_DIR=build\msvc-asan"

if not defined BUILD_DIR (
	echo usage: clean_build.cmd PRESET
	echo 	PRESET is one of: msvc-debug, msvc-release, msvc-asan
	exit /b 1
)

if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
cmake --workflow --preset %PRESET%
exit /b %errorlevel%
@echo off
setlocal EnableExtensions
cd /d "%~dp0"

echo ==========================================================
echo   NLib - CMake build (Windows / Visual Studio)
echo ==========================================================
echo.

where cmake >nul 2>nul
if errorlevel 1 (
    echo [ERROR] 'cmake' was not found on PATH.
    echo         Install CMake from https://cmake.org and add it to PATH.
    goto :fail
)

rem ------------------------------------------------------------------
rem Prefer the newest installed Visual Studio generator (auto-detected
rem via vswhere) so double-clicking always produces a .sln/.vcxproj.
rem ------------------------------------------------------------------
set "GEN_NAME="
set "VS_MAJOR="
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    for /f "usebackq tokens=1 delims=." %%V in (`"%VSWHERE%" -latest -products * -requires Microsoft.Component.MSBuild -property installationVersion 2^>nul`) do set "VS_MAJOR=%%V"
)
if "%VS_MAJOR%"=="17" set "GEN_NAME=Visual Studio 17 2022"
if "%VS_MAJOR%"=="16" set "GEN_NAME=Visual Studio 16 2019"
if "%VS_MAJOR%"=="15" set "GEN_NAME=Visual Studio 15 2017"

echo [1/2] Configuring...
if defined GEN_NAME (
    cmake -S . -B build -G "%GEN_NAME%" -A x64
) else (
    cmake -S . -B build
)
if errorlevel 1 goto :fail

echo.
echo [2/2] Building (Release)...
cmake --build build --config Release
if errorlevel 1 goto :fail

echo.
echo ==========================================================
echo   Build succeeded: build\Release\NLib.lib
echo ==========================================================
echo.
echo Opening the Visual Studio solution...
cmake --open build

endlocal
echo.
pause
exit /b 0

:fail
endlocal
echo.
echo [ERROR] Build failed. Review the messages above.
pause
exit /b 1

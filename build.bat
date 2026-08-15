@echo off
setlocal enabledelayedexpansion

:: Ensure execution starts from the project root directory
cd /d "%~dp0"

:: Handle 'clean' argument
if /I "%~1"=="clean" (
    echo [INFO] Cleaning build artifacts...
    if exist "bin" (
        rmdir /s /q "bin"
        echo Removed bin\ directory.
    )
    if exist "cache_sim.exe" (
        del /f /q "cache_sim.exe"
        echo Removed cache_sim.exe
    )
    echo Clean completed.
    exit /b 0
)

echo ===================================================
echo        RISC-V Cache Simulator - Build Script
echo ===================================================
echo.

:: Check for GCC / g++ in PATH
where g++ >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] g++ compiler was not found in your PATH!
    echo Please make sure MinGW / GCC is installed and added to your system PATH.
    echo.
    pause
    exit /b 1
)

:: Output directory and binary name
set "OUT_DIR=bin"
set "TARGET=%OUT_DIR%\cache_sim.exe"

if not exist "%OUT_DIR%" (
    mkdir "%OUT_DIR%"
)

:: Compile sources
echo [INFO] Compiling project files...
echo   - Sources:  main.cpp src\*.cpp
echo   - Includes: include\
echo   - Target:   %TARGET%
echo.

g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/*.cpp -o "%TARGET%"

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ===================================================
    echo [BUILD FAILED] Compilation errors occurred above.
    echo ===================================================
    echo.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ===================================================
echo [BUILD SUCCESS] Executable created at: %TARGET%
echo ===================================================
echo.

:: If run argument was provided (e.g. build.bat run), run directly
if /I "%~1"=="run" (
    echo [INFO] Running %TARGET%...
    echo ---------------------------------------------------
    "%TARGET%"
    echo.
    echo ---------------------------------------------------
    pause
    exit /b 0
)

:: Prompt to run the program (auto-defaults to N after 5 seconds)
choice /C YN /M "Do you want to run the program now?" /T 5 /D N
if !ERRORLEVEL! EQU 1 (
    echo.
    echo [INFO] Running %TARGET%...
    echo ---------------------------------------------------
    "%TARGET%"
    echo.
    echo ---------------------------------------------------
)

echo.
pause

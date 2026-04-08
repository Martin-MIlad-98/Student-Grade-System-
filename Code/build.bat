@echo off
echo ========================================
echo  Student Grade Management System Build
echo ========================================
echo.

where qmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Qt is not installed or qmake is not in PATH
    echo.
    echo Please install Qt from https://www.qt.io/download
    echo Or add Qt bin directory to your PATH
    pause
    exit /b 1
)

echo Step 1: Generating Makefiles...
qmake StudentGradeSystem.pro

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: qmake failed
    pause
    exit /b 1
)

echo.
echo Step 2: Building application...
where nmake >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    nmake
) else (
    where mingw32-make >nul 2>&1
    if %ERRORLEVEL% EQU 0 (
        mingw32-make
    ) else (
        where make >nul 2>&1
        if %ERRORLEVEL% EQU 0 (
            make
        ) else (
            echo ERROR: No build tool found (nmake, mingw32-make, or make)
            pause
            exit /b 1
        )
    )
)

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed
    pause
    exit /b 1
)

echo.
echo ========================================
echo  Build Successful!
echo ========================================
echo.
echo You can now run the application:
echo   - On Windows: release\StudentGradeSystem.exe or debug\StudentGradeSystem.exe
echo.
pause

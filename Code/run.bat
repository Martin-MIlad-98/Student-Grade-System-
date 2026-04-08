@echo off
echo Setting up Qt environment...
set PATH=C:\Qt\6.10.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;%PATH%

echo Building project...
call qmake StudentGradeSystem.pro
if %ERRORLEVEL% NEQ 0 (
    echo qmake failed!
    pause
    exit /b 1
)

call mingw32-make
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful!
echo Running application...
echo.

if exist release\StudentGradeSystem.exe (
    start release\StudentGradeSystem.exe
) else if exist debug\StudentGradeSystem.exe (
    start debug\StudentGradeSystem.exe
) else (
    echo Executable not found!
    pause
    exit /b 1
)

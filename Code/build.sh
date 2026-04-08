#!/bin/bash

echo "========================================"
echo " Student Grade Management System Build"
echo "========================================"
echo ""

if ! command -v qmake &> /dev/null; then
    echo "ERROR: Qt is not installed or qmake is not in PATH"
    echo ""
    echo "Please install Qt from https://www.qt.io/download"
    echo "Or install via package manager:"
    echo "  Ubuntu/Debian: sudo apt-get install qt6-base-dev qt6-charts-dev"
    echo "  Fedora: sudo dnf install qt6-qtbase-devel qt6-qtcharts-devel"
    echo "  macOS: brew install qt@6"
    exit 1
fi

echo "Step 1: Generating Makefiles..."
qmake StudentGradeSystem.pro

if [ $? -ne 0 ]; then
    echo "ERROR: qmake failed"
    exit 1
fi

echo ""
echo "Step 2: Building application..."
make

if [ $? -ne 0 ]; then
    echo ""
    echo "ERROR: Build failed"
    exit 1
fi

echo ""
echo "========================================"
echo " Build Successful!"
echo "========================================"
echo ""
echo "You can now run the application:"
echo "  ./StudentGradeSystem"
echo ""

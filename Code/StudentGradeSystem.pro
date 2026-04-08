QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = StudentGradeSystem
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/sources/main.cpp \
    src/sources/Person.cpp \
    src/sources/Student.cpp \
    src/sources/Professor.cpp \
    src/sources/Course.cpp \
    src/sources/Grade.cpp \
    src/sources/GradeManager.cpp \
    src/sources/MainWindow.cpp \
    src/sources/StudentDialog.cpp \
    src/sources/CourseDialog.cpp \
    src/sources/GradeDialog.cpp \
    src/sources/ProfessorDialog.cpp

HEADERS += \
    src/headers/Person.h \
    src/headers/Student.h \
    src/headers/Professor.h \
    src/headers/Course.h \
    src/headers/Grade.h \
    src/headers/DataRepository.h \
    src/headers/GradeManager.h \
    src/headers/MainWindow.h \
    src/headers/StudentDialog.h \
    src/headers/CourseDialog.h \
    src/headers/GradeDialog.h \
    src/headers/ProfessorDialog.h

INCLUDEPATH += src/headers

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

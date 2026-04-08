#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include "GradeManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    GradeManager* manager;
    QTabWidget* tabWidget;

    QWidget *studentsTab, *coursesTab, *gradesTab, *professorsTab, *analyticsTab;
    QTableWidget *studentsTable, *coursesTable, *gradesTable, *professorsTable;
    QTableWidget *topStudentsList, *gradeDistTable, *courseStatsTable;

    QPushButton *btnAddStudent, *btnEditStudent, *btnDeleteStudent, *btnRefreshStudents;
    QPushButton *btnAddCourse, *btnEditCourse, *btnDeleteCourse, *btnRefreshCourses;
    QPushButton *btnEnrollStudent, *btnUpdateGrade, *btnRefreshGrades;
    QPushButton *btnAddProfessor, *btnDeleteProfessor, *btnAssignCourse;

    QComboBox* filterCombo;
    QLineEdit* searchBox;

    void setupUI();
    void setupMenuBar();
    void setupStudentsTab();
    void setupCoursesTab();
    void setupGradesTab();
    void setupProfessorsTab();
    void setupAnalyticsTab();

    void refreshStudentsTable();
    void refreshCoursesTable();
    void refreshGradesTable();
    void refreshProfessorsTable();
    void refreshAnalytics();
    void applyStudentFilter();
    void searchStudents(const QString& query);

private slots:
    void onAddStudent();
    void onEditStudent();
    void onDeleteStudent();
    void onAddCourse();
    void onEditCourse();
    void onDeleteCourse();
    void onEnrollStudent();
    void onUpdateGrade();
    void onAddProfessor();
    void onDeleteProfessor();
    void onAssignCourse();
    void onSaveData();
    void onLoadData();
    void onCreateSampleData();
    void onExportReport();
    void onAbout();
    void onTabChanged(int index);

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

#endif

#include "MainWindow.h"
#include "StudentDialog.h"
#include "CourseDialog.h"
#include "GradeDialog.h"
#include "ProfessorDialog.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QGroupBox>
#include <QFrame>
#include <QGridLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    manager = GradeManager::getInstance();
    setupUI();
    setupMenuBar();
    refreshStudentsTable();
    refreshCoursesTable();
    refreshGradesTable();
    refreshProfessorsTable();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    setWindowTitle("Student Grade Management System");
    setMinimumSize(1200, 800);

    auto* central = new QWidget(this);
    auto* layout = new QVBoxLayout(central);
    
    // Apply dark theme stylesheet to the main widget
    central->setStyleSheet(
        "QWidget {"
        "    background-color: #1e1e1e;"
        "    color: #e0e0e0;"
        "}"
        "QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox {"
        "    background-color: #2d2d2d;"
        "    color: #e0e0e0;"
        "    border: 1px solid #3d3d3d;"
        "    padding: 5px;"
        "    border-radius: 3px;"
        "}"
        "QLineEdit:focus, QComboBox:focus {"
        "    border: 1px solid #007acc;"
        "}"
        "QPushButton {"
        "    background-color: #0e639c;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1177bb;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #0d5a8f;"
        "}"
        "QTableWidget {"
        "    background-color: #252525;"
        "    alternate-background-color: #2d2d2d;"
        "    color: #e0e0e0;"
        "    gridline-color: #3d3d3d;"
        "    border: 1px solid #3d3d3d;"
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #0e639c;"
        "    color: white;"
        "}"
        "QHeaderView::section {"
        "    background-color: #2d2d2d;"
        "    color: #e0e0e0;"
        "    padding: 5px;"
        "    border: 1px solid #3d3d3d;"
        "    font-weight: bold;"
        "}"
        "QLabel {"
        "    color: #e0e0e0;"
        "}"
        "QGroupBox {"
        "    color: #e0e0e0;"
        "    border: 1px solid #3d3d3d;"
        "    border-radius: 5px;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    color: #e0e0e0;"
        "    subcontrol-origin: margin;"
        "    subcontrol-position: top left;"
        "    padding: 0 5px;"
        "}"
    );

    auto* title = new QLabel("Student Grade Management System", this);
    QFont font = title->font();
    font.setPointSize(18);
    font.setBold(true);
    title->setFont(font);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #ffffff; padding: 10px; background-color: transparent;");
    layout->addWidget(title);

    tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet(
        "QTabWidget::pane { border: 1px solid #3d3d3d; background-color: #1e1e1e; }"
        "QTabBar::tab { background-color: #2d2d2d; color: #e0e0e0; padding: 10px 20px; margin-right: 2px; border: 1px solid #3d3d3d; }"
        "QTabBar::tab:selected { background: #0e639c; color: white; border-bottom: none; }"
        "QTabBar::tab:!selected { background: #252525; }"
        "QTabBar::tab:hover:!selected { background: #3d3d3d; }");

    setupStudentsTab();
    setupCoursesTab();
    setupGradesTab();
    setupProfessorsTab();
    setupAnalyticsTab();

    layout->addWidget(tabWidget);
    setCentralWidget(central);

    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
}

void MainWindow::setupMenuBar() {
    auto* fileMenu = menuBar()->addMenu("&File");

    auto* load = new QAction("&Load Data", this);
    load->setShortcut(QKeySequence::Open);
    connect(load, &QAction::triggered, this, &MainWindow::onLoadData);
    fileMenu->addAction(load);

    auto* save = new QAction("&Save Data", this);
    save->setShortcut(QKeySequence::Save);
    connect(save, &QAction::triggered, this, &MainWindow::onSaveData);
    fileMenu->addAction(save);

    fileMenu->addSeparator();
    auto* exp = new QAction("&Export Report", this);
    connect(exp, &QAction::triggered, this, &MainWindow::onExportReport);
    fileMenu->addAction(exp);

    fileMenu->addSeparator();
    auto* exit = new QAction("E&xit", this);
    exit->setShortcut(QKeySequence::Quit);
    connect(exit, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exit);

    auto* dataMenu = menuBar()->addMenu("&Data");
    auto* sample = new QAction("Create &Sample Data", this);
    connect(sample, &QAction::triggered, this, &MainWindow::onCreateSampleData);
    dataMenu->addAction(sample);

    auto* helpMenu = menuBar()->addMenu("&Help");
    auto* about = new QAction("&About", this);
    connect(about, &QAction::triggered, this, &MainWindow::onAbout);
    helpMenu->addAction(about);
}

void MainWindow::setupStudentsTab() {
    studentsTab = new QWidget();
    auto* layout = new QVBoxLayout(studentsTab);

    auto* topBar = new QHBoxLayout();
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Search students...");
    searchBox->setMaximumWidth(300);
    connect(searchBox, &QLineEdit::textChanged, this, &MainWindow::searchStudents);

    filterCombo = new QComboBox();
    filterCombo->addItems({"All Students", "Computer Science", "Physical Therapy", "Art and Design", "Engineering", "Business"});
    filterCombo->setMaximumWidth(200);
    connect(filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::applyStudentFilter);

    topBar->addWidget(new QLabel("Search:"));
    topBar->addWidget(searchBox);
    topBar->addWidget(new QLabel("Filter:"));
    topBar->addWidget(filterCombo);
    topBar->addStretch();
    layout->addLayout(topBar);

    studentsTable = new QTableWidget();
    studentsTable->setColumnCount(7);
    studentsTable->setHorizontalHeaderLabels({"ID", "Student #", "Name", "Email", "Major", "Year", "GPA"});
    studentsTable->horizontalHeader()->setStretchLastSection(true);
    studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentsTable->setAlternatingRowColors(true);
    layout->addWidget(studentsTable);

    auto* btns = new QHBoxLayout();
    btnAddStudent = new QPushButton("Add Student");
    btnAddStudent->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnAddStudent, &QPushButton::clicked, this, &MainWindow::onAddStudent);

    btnEditStudent = new QPushButton("Edit Student");
    btnEditStudent->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnEditStudent, &QPushButton::clicked, this, &MainWindow::onEditStudent);

    btnDeleteStudent = new QPushButton("Delete Student");
    btnDeleteStudent->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnDeleteStudent, &QPushButton::clicked, this, &MainWindow::onDeleteStudent);

    btnRefreshStudents = new QPushButton("Refresh");
    btnRefreshStudents->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnRefreshStudents, &QPushButton::clicked, this, &MainWindow::refreshStudentsTable);

    btns->addWidget(btnAddStudent);
    btns->addWidget(btnEditStudent);
    btns->addWidget(btnDeleteStudent);
    btns->addStretch();
    btns->addWidget(btnRefreshStudents);
    layout->addLayout(btns);

    tabWidget->addTab(studentsTab, "Students");
}

void MainWindow::setupCoursesTab() {
    coursesTab = new QWidget();
    auto* layout = new QVBoxLayout(coursesTab);

    coursesTable = new QTableWidget();
    coursesTable->setColumnCount(7);
    coursesTable->setHorizontalHeaderLabels({"ID", "Code", "Name", "Type", "Credits", "Enrolled", "Status"});
    coursesTable->horizontalHeader()->setStretchLastSection(true);
    coursesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    coursesTable->setAlternatingRowColors(true);
    layout->addWidget(coursesTable);

    auto* btns = new QHBoxLayout();
    btnAddCourse = new QPushButton("Add Course");
    btnAddCourse->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnAddCourse, &QPushButton::clicked, this, &MainWindow::onAddCourse);

    btnEditCourse = new QPushButton("Edit Course");
    btnEditCourse->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnEditCourse, &QPushButton::clicked, this, &MainWindow::onEditCourse);

    btnDeleteCourse = new QPushButton("Delete Course");
    btnDeleteCourse->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnDeleteCourse, &QPushButton::clicked, this, &MainWindow::onDeleteCourse);

    btnRefreshCourses = new QPushButton("Refresh");
    btnRefreshCourses->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnRefreshCourses, &QPushButton::clicked, this, &MainWindow::refreshCoursesTable);

    btns->addWidget(btnAddCourse);
    btns->addWidget(btnEditCourse);
    btns->addWidget(btnDeleteCourse);
    btns->addStretch();
    btns->addWidget(btnRefreshCourses);
    layout->addLayout(btns);

    tabWidget->addTab(coursesTab, "Courses");
}

void MainWindow::setupGradesTab() {
    gradesTab = new QWidget();
    auto* layout = new QVBoxLayout(gradesTab);

    gradesTable = new QTableWidget();
    gradesTable->setColumnCount(8);
    gradesTable->setHorizontalHeaderLabels({"Student", "Course", "Midterm", "Final", "Assignment", "Total", "Letter", "Status"});
    gradesTable->horizontalHeader()->setStretchLastSection(true);
    gradesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    gradesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    gradesTable->setAlternatingRowColors(true);
    layout->addWidget(gradesTable);

    auto* btns = new QHBoxLayout();
    btnEnrollStudent = new QPushButton("Enroll Student");
    btnEnrollStudent->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnEnrollStudent, &QPushButton::clicked, this, &MainWindow::onEnrollStudent);

    btnUpdateGrade = new QPushButton("Update Grade");
    btnUpdateGrade->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnUpdateGrade, &QPushButton::clicked, this, &MainWindow::onUpdateGrade);

    btnRefreshGrades = new QPushButton("Refresh");
    btnRefreshGrades->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnRefreshGrades, &QPushButton::clicked, this, &MainWindow::refreshGradesTable);

    btns->addWidget(btnEnrollStudent);
    btns->addWidget(btnUpdateGrade);
    btns->addStretch();
    btns->addWidget(btnRefreshGrades);
    layout->addLayout(btns);

    tabWidget->addTab(gradesTab, "Grades");
}

void MainWindow::setupProfessorsTab() {
    professorsTab = new QWidget();
    auto* layout = new QVBoxLayout(professorsTab);

    professorsTable = new QTableWidget();
    professorsTable->setColumnCount(6);
    professorsTable->setHorizontalHeaderLabels({"ID", "Employee ID", "Name", "Email", "Department", "Courses"});
    professorsTable->horizontalHeader()->setStretchLastSection(true);
    professorsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    professorsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    professorsTable->setAlternatingRowColors(true);
    layout->addWidget(professorsTable);

    auto* btns = new QHBoxLayout();
    btnAddProfessor = new QPushButton("Add Professor");
    btnAddProfessor->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnAddProfessor, &QPushButton::clicked, this, &MainWindow::onAddProfessor);

    btnDeleteProfessor = new QPushButton("Delete Professor");
    btnDeleteProfessor->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnDeleteProfessor, &QPushButton::clicked, this, &MainWindow::onDeleteProfessor);

    btnAssignCourse = new QPushButton("Assign to Course");
    btnAssignCourse->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 8px 20px; border-radius: 4px; }");
    connect(btnAssignCourse, &QPushButton::clicked, this, &MainWindow::onAssignCourse);

    btns->addWidget(btnAddProfessor);
    btns->addWidget(btnDeleteProfessor);
    btns->addWidget(btnAssignCourse);
    btns->addStretch();
    layout->addLayout(btns);

    tabWidget->addTab(professorsTab, "Professors");
}

void MainWindow::setupAnalyticsTab() {
    analyticsTab = new QWidget();
    auto* layout = new QVBoxLayout(analyticsTab);

    auto* title = new QLabel("System Analytics Dashboard");
    QFont titleFont = title->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #2c3e50; padding: 15px;");
    layout->addWidget(title);

    // Statistics Cards Row
    auto* statsGroup = new QGroupBox("Quick Statistics");
    statsGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 12px; }");
    auto* statsLayout = new QHBoxLayout(statsGroup);

    // Create stat cards
    auto createStatCard = [](const QString& label, const QString& value, const QString& color) {
        auto* card = new QFrame();
        card->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        card->setStyleSheet(QString("QFrame { background: %1; border-radius: 8px; padding: 10px; }").arg(color));
        auto* cardLayout = new QVBoxLayout(card);

        auto* valueLabel = new QLabel(value);
        valueLabel->setObjectName("statValue");
        QFont vFont; vFont.setPointSize(28); vFont.setBold(true);
        valueLabel->setFont(vFont);
        valueLabel->setAlignment(Qt::AlignCenter);
        valueLabel->setStyleSheet("color: white;");

        auto* nameLabel = new QLabel(label);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setStyleSheet("color: white; font-size: 11px;");

        cardLayout->addWidget(valueLabel);
        cardLayout->addWidget(nameLabel);
        return card;
    };

    statsLayout->addWidget(createStatCard("Total Students", "0", "#3498db"));
    statsLayout->addWidget(createStatCard("Total Professors", "0", "#9b59b6"));
    statsLayout->addWidget(createStatCard("Total Courses", "0", "#27ae60"));
    statsLayout->addWidget(createStatCard("Total Grades", "0", "#e67e22"));
    layout->addWidget(statsGroup);

    // Analytics Details Section
    auto* detailsLayout = new QHBoxLayout();

    // Top Students Section
    auto* topStudentsGroup = new QGroupBox("Top 5 Students by GPA");
    topStudentsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    auto* topStudentsLayout = new QVBoxLayout(topStudentsGroup);
    topStudentsList = new QTableWidget();
    topStudentsList->setColumnCount(3);
    topStudentsList->setHorizontalHeaderLabels({"Rank", "Name", "GPA"});
    topStudentsList->horizontalHeader()->setStretchLastSection(true);
    topStudentsList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    topStudentsList->setAlternatingRowColors(true);
    topStudentsLayout->addWidget(topStudentsList);
    detailsLayout->addWidget(topStudentsGroup);

    // Grade Distribution Section
    auto* gradeDistGroup = new QGroupBox("Overall Grade Distribution");
    gradeDistGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    auto* gradeDistLayout = new QVBoxLayout(gradeDistGroup);
    gradeDistTable = new QTableWidget();
    gradeDistTable->setColumnCount(3);
    gradeDistTable->setHorizontalHeaderLabels({"Grade", "Count", "Percentage"});
    gradeDistTable->horizontalHeader()->setStretchLastSection(true);
    gradeDistTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    gradeDistTable->setAlternatingRowColors(true);
    gradeDistLayout->addWidget(gradeDistTable);
    detailsLayout->addWidget(gradeDistGroup);

    layout->addLayout(detailsLayout);

    // Course Statistics Section
    auto* courseStatsGroup = new QGroupBox("Course Statistics");
    courseStatsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    auto* courseStatsLayout = new QVBoxLayout(courseStatsGroup);
    courseStatsTable = new QTableWidget();
    courseStatsTable->setColumnCount(5);
    courseStatsTable->setHorizontalHeaderLabels({"Course", "Enrolled", "Average Score", "Pass Rate", "Professor"});
    courseStatsTable->horizontalHeader()->setStretchLastSection(true);
    courseStatsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    courseStatsTable->setAlternatingRowColors(true);
    courseStatsLayout->addWidget(courseStatsTable);
    layout->addWidget(courseStatsGroup);

    // Refresh button
    auto* btnRefresh = new QPushButton("Refresh Analytics");
    btnRefresh->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 10px 30px; border-radius: 4px; font-size: 12px; }");
    connect(btnRefresh, &QPushButton::clicked, this, &MainWindow::refreshAnalytics);
    auto* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnRefresh);
    btnLayout->addStretch();
    layout->addLayout(btnLayout);

    tabWidget->addTab(analyticsTab, "Analytics");
}

void MainWindow::refreshStudentsTable() {
    studentsTable->setRowCount(0);
    for (const auto& s : manager->getAllStudents()) {
        int row = studentsTable->rowCount();
        studentsTable->insertRow(row);
        studentsTable->setItem(row, 0, new QTableWidgetItem(QString::number(s->getId())));
        studentsTable->setItem(row, 1, new QTableWidgetItem(s->getStudentNumber()));
        studentsTable->setItem(row, 2, new QTableWidgetItem(s->getFullName()));
        studentsTable->setItem(row, 3, new QTableWidgetItem(s->getEmail()));
        studentsTable->setItem(row, 4, new QTableWidgetItem(s->getMajor()));
        studentsTable->setItem(row, 5, new QTableWidgetItem(QString::number(s->getEnrollmentYear())));
        studentsTable->setItem(row, 6, new QTableWidgetItem(QString::number(s->calculateGPA(), 'f', 2)));
    }
    studentsTable->resizeColumnsToContents();
}

void MainWindow::refreshCoursesTable() {
    coursesTable->setRowCount(0);
    for (const auto& c : manager->getAllCourses()) {
        int row = coursesTable->rowCount();
        coursesTable->insertRow(row);
        coursesTable->setItem(row, 0, new QTableWidgetItem(QString::number(c->getCourseId())));
        coursesTable->setItem(row, 1, new QTableWidgetItem(c->getCourseCode()));
        coursesTable->setItem(row, 2, new QTableWidgetItem(c->getCourseName()));
        coursesTable->setItem(row, 3, new QTableWidgetItem(c->getCourseType()));
        coursesTable->setItem(row, 4, new QTableWidgetItem(QString::number(c->getCredits())));
        coursesTable->setItem(row, 5, new QTableWidgetItem(QString::number(c->getEnrolledCount())));
        coursesTable->setItem(row, 6, new QTableWidgetItem(c->getStatusString()));
    }
    coursesTable->resizeColumnsToContents();
}

void MainWindow::refreshGradesTable() {
    gradesTable->setRowCount(0);
    for (const auto& g : manager->getAllGrades()) {
        auto s = manager->getStudent(g->getStudentId());
        auto c = manager->getCourse(g->getCourseId());
        if (!s || !c) continue;

        int row = gradesTable->rowCount();
        gradesTable->insertRow(row);
        gradesTable->setItem(row, 0, new QTableWidgetItem(s->getFullName()));
        gradesTable->setItem(row, 1, new QTableWidgetItem(c->getCourseName()));
        gradesTable->setItem(row, 2, new QTableWidgetItem(QString::number(g->getMidtermScore(), 'f', 1)));
        gradesTable->setItem(row, 3, new QTableWidgetItem(QString::number(g->getFinalScore(), 'f', 1)));
        gradesTable->setItem(row, 4, new QTableWidgetItem(QString::number(g->getAssignmentScore(), 'f', 1)));
        gradesTable->setItem(row, 5, new QTableWidgetItem(QString::number(g->getTotalScore(), 'f', 1)));
        gradesTable->setItem(row, 6, new QTableWidgetItem(g->getLetterGrade()));
        gradesTable->setItem(row, 7, new QTableWidgetItem(g->getStatus()));
    }
    gradesTable->resizeColumnsToContents();
}

void MainWindow::refreshProfessorsTable() {
    professorsTable->setRowCount(0);
    for (const auto& p : manager->getAllProfessors()) {
        int row = professorsTable->rowCount();
        professorsTable->insertRow(row);
        professorsTable->setItem(row, 0, new QTableWidgetItem(QString::number(p->getId())));
        professorsTable->setItem(row, 1, new QTableWidgetItem(p->getEmployeeId()));
        professorsTable->setItem(row, 2, new QTableWidgetItem(p->getFullName()));
        professorsTable->setItem(row, 3, new QTableWidgetItem(p->getEmail()));
        professorsTable->setItem(row, 4, new QTableWidgetItem(p->getDepartment()));
        professorsTable->setItem(row, 5, new QTableWidgetItem(QString::number(p->getCourseCount())));
    }
    professorsTable->resizeColumnsToContents();
}

void MainWindow::refreshAnalytics() {
    // Update stat cards
    auto* statsGroup = analyticsTab->findChild<QGroupBox*>();
    if (statsGroup) {
        auto cards = statsGroup->findChildren<QFrame*>();
        QStringList values = {
            QString::number(manager->getStudentCount()),
            QString::number(manager->getProfessorCount()),
            QString::number(manager->getCourseCount()),
            QString::number(manager->getGradeCount())
        };
        int i = 0;
        for (auto* card : cards) {
            auto* label = card->findChild<QLabel*>("statValue");
            if (label && i < values.size()) label->setText(values[i++]);
        }
    }

    // Top Students
    topStudentsList->setRowCount(0);
    auto topStudents = manager->getTopStudents(5);
    int rank = 1;
    for (const auto& s : topStudents) {
        int row = topStudentsList->rowCount();
        topStudentsList->insertRow(row);
        topStudentsList->setItem(row, 0, new QTableWidgetItem(QString::number(rank++)));
        topStudentsList->setItem(row, 1, new QTableWidgetItem(s->getFullName()));
        topStudentsList->setItem(row, 2, new QTableWidgetItem(QString::number(s->calculateGPA(), 'f', 2)));
    }
    topStudentsList->resizeColumnsToContents();

    // Grade Distribution
    gradeDistTable->setRowCount(0);
    QMap<QString, int> dist{{"A", 0}, {"B", 0}, {"C", 0}, {"D", 0}, {"F", 0}};
    int totalGrades = 0;
    for (const auto& g : manager->getAllGrades()) {
        QString letter = g->getLetterGrade();
        if (letter.startsWith("A")) dist["A"]++;
        else if (letter.startsWith("B")) dist["B"]++;
        else if (letter.startsWith("C")) dist["C"]++;
        else if (letter.startsWith("D")) dist["D"]++;
        else dist["F"]++;
        totalGrades++;
    }
    for (auto it = dist.begin(); it != dist.end(); ++it) {
        int row = gradeDistTable->rowCount();
        gradeDistTable->insertRow(row);
        gradeDistTable->setItem(row, 0, new QTableWidgetItem(it.key()));
        gradeDistTable->setItem(row, 1, new QTableWidgetItem(QString::number(it.value())));
        double pct = totalGrades > 0 ? (it.value() * 100.0 / totalGrades) : 0;
        gradeDistTable->setItem(row, 2, new QTableWidgetItem(QString::number(pct, 'f', 1) + "%"));
    }
    gradeDistTable->resizeColumnsToContents();

    // Course Statistics
    courseStatsTable->setRowCount(0);
    for (const auto& c : manager->getAllCourses()) {
        int row = courseStatsTable->rowCount();
        courseStatsTable->insertRow(row);
        courseStatsTable->setItem(row, 0, new QTableWidgetItem(c->getCourseName()));
        courseStatsTable->setItem(row, 1, new QTableWidgetItem(QString::number(c->getEnrolledCount())));

        double avg = manager->calculateCourseAverage(c->getCourseId());
        courseStatsTable->setItem(row, 2, new QTableWidgetItem(QString::number(avg, 'f', 1)));

        // Calculate pass rate
        auto courseGrades = manager->getCourseGrades(c->getCourseId());
        int passed = 0;
        for (const auto& g : courseGrades) {
            if (g->getTotalScore() >= 60) passed++;
        }
        double passRate = courseGrades.isEmpty() ? 0 : (passed * 100.0 / courseGrades.size());
        courseStatsTable->setItem(row, 3, new QTableWidgetItem(QString::number(passRate, 'f', 1) + "%"));

        // Professor name
        auto prof = manager->getProfessor(c->getTeacherId());
        courseStatsTable->setItem(row, 4, new QTableWidgetItem(prof ? prof->getFullName() : "Unassigned"));
    }
    courseStatsTable->resizeColumnsToContents();
}

void MainWindow::applyStudentFilter() {
    QString filter = filterCombo->currentText();
    studentsTable->setRowCount(0);
    for (const auto& s : manager->getAllStudents()) {
        if (filter == "All Students" || s->getMajor() == filter) {
            int row = studentsTable->rowCount();
            studentsTable->insertRow(row);
            studentsTable->setItem(row, 0, new QTableWidgetItem(QString::number(s->getId())));
            studentsTable->setItem(row, 1, new QTableWidgetItem(s->getStudentNumber()));
            studentsTable->setItem(row, 2, new QTableWidgetItem(s->getFullName()));
            studentsTable->setItem(row, 3, new QTableWidgetItem(s->getEmail()));
            studentsTable->setItem(row, 4, new QTableWidgetItem(s->getMajor()));
            studentsTable->setItem(row, 5, new QTableWidgetItem(QString::number(s->getEnrollmentYear())));
            studentsTable->setItem(row, 6, new QTableWidgetItem(QString::number(s->calculateGPA(), 'f', 2)));
        }
    }
}

void MainWindow::searchStudents(const QString& query) {
    if (query.isEmpty()) { applyStudentFilter(); return; }

    studentsTable->setRowCount(0);
    QString q = query.toLower();
    for (const auto& s : manager->getAllStudents()) {
        if (s->getFullName().toLower().contains(q) || s->getStudentNumber().toLower().contains(q)) {
            int row = studentsTable->rowCount();
            studentsTable->insertRow(row);
            studentsTable->setItem(row, 0, new QTableWidgetItem(QString::number(s->getId())));
            studentsTable->setItem(row, 1, new QTableWidgetItem(s->getStudentNumber()));
            studentsTable->setItem(row, 2, new QTableWidgetItem(s->getFullName()));
            studentsTable->setItem(row, 3, new QTableWidgetItem(s->getEmail()));
            studentsTable->setItem(row, 4, new QTableWidgetItem(s->getMajor()));
            studentsTable->setItem(row, 5, new QTableWidgetItem(QString::number(s->getEnrollmentYear())));
            studentsTable->setItem(row, 6, new QTableWidgetItem(QString::number(s->calculateGPA(), 'f', 2)));
        }
    }
}

void MainWindow::onAddStudent() {
    StudentDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) refreshStudentsTable();
}

void MainWindow::onEditStudent() {
    int row = studentsTable->currentRow();
    if (row < 0) { QMessageBox::warning(this, "No Selection", "Please select a student."); return; }
    StudentDialog dlg(this, studentsTable->item(row, 0)->text().toInt());
    if (dlg.exec() == QDialog::Accepted) refreshStudentsTable();
}

void MainWindow::onDeleteStudent() {
    int row = studentsTable->currentRow();
    if (row < 0) { QMessageBox::warning(this, "No Selection", "Please select a student."); return; }

    int id = studentsTable->item(row, 0)->text().toInt();
    auto s = manager->getStudent(id);
    if (!s) return;

    if (QMessageBox::question(this, "Confirm", QString("Delete student: %1?").arg(s->getFullName())) == QMessageBox::Yes) {
        manager->removeStudent(id);
        refreshStudentsTable();
    }
}

void MainWindow::onAddCourse() {
    CourseDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) refreshCoursesTable();
}

void MainWindow::onEditCourse() {
    int row = coursesTable->currentRow();
    if (row < 0) { QMessageBox::warning(this, "No Selection", "Please select a course."); return; }
    CourseDialog dlg(this, coursesTable->item(row, 0)->text().toInt());
    if (dlg.exec() == QDialog::Accepted) refreshCoursesTable();
}

void MainWindow::onDeleteCourse() {
    int row = coursesTable->currentRow();
    if (row < 0) { QMessageBox::warning(this, "No Selection", "Please select a course."); return; }
    manager->removeCourse(coursesTable->item(row, 0)->text().toInt());
    refreshCoursesTable();
}

void MainWindow::onEnrollStudent() {
    GradeDialog dlg(this, true);
    if (dlg.exec() == QDialog::Accepted) refreshGradesTable();
}

void MainWindow::onUpdateGrade() {
    if (gradesTable->currentRow() < 0) { QMessageBox::warning(this, "No Selection", "Please select a grade."); return; }
    GradeDialog dlg(this, false);
    if (dlg.exec() == QDialog::Accepted) { refreshGradesTable(); refreshStudentsTable(); }
}

void MainWindow::onAddProfessor() {
    ProfessorDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) refreshProfessorsTable();
}

void MainWindow::onDeleteProfessor() {
    int row = professorsTable->currentRow();
    if (row < 0) { QMessageBox::warning(this, "No Selection", "Please select a professor."); return; }
    manager->removeProfessor(professorsTable->item(row, 0)->text().toInt());
    refreshProfessorsTable();
}

void MainWindow::onAssignCourse() {
    int row = professorsTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a professor first.");
        return;
    }

    int profId = professorsTable->item(row, 0)->text().toInt();
    auto prof = manager->getProfessor(profId);
    if (!prof) return;

    // Build list of available courses
    QStringList courseItems;
    QVector<int> courseIds;
    for (const auto& c : manager->getAllCourses()) {
        courseItems << QString("%1 - %2").arg(c->getCourseCode(), c->getCourseName());
        courseIds.append(c->getCourseId());
    }

    if (courseItems.isEmpty()) {
        QMessageBox::warning(this, "No Courses", "No courses available. Please add courses first.");
        return;
    }

    bool ok;
    QString selected = QInputDialog::getItem(this, "Assign Course",
        QString("Select course to assign to %1:").arg(prof->getFullName()),
        courseItems, 0, false, &ok);

    if (ok && !selected.isEmpty()) {
        int idx = courseItems.indexOf(selected);
        if (idx >= 0 && idx < courseIds.size()) {
            int courseId = courseIds[idx];
            if (prof->isAssignedTo(courseId)) {
                QMessageBox::information(this, "Already Assigned",
                    "Professor is already assigned to this course.");
            } else {
                manager->assignProfessorToCourse(profId, courseId);
                refreshProfessorsTable();
                refreshCoursesTable();
                QMessageBox::information(this, "Success",
                    QString("%1 has been assigned to %2").arg(prof->getFullName(), selected));
            }
        }
    }
}

void MainWindow::onSaveData() {
    QString file = QFileDialog::getSaveFileName(this, "Save Data", "", "JSON (*.json)");
    if (!file.isEmpty()) {
        if (manager->saveToFile(file)) QMessageBox::information(this, "Success", "Data saved!");
        else QMessageBox::warning(this, "Error", "Failed to save.");
    }
}

void MainWindow::onLoadData() {
    QString file = QFileDialog::getOpenFileName(this, "Load Data", "", "JSON (*.json)");
    if (!file.isEmpty()) {
        if (manager->loadFromFile(file)) {
            refreshStudentsTable(); refreshCoursesTable(); refreshGradesTable(); refreshProfessorsTable();
            QMessageBox::information(this, "Success", "Data loaded!");
        } else QMessageBox::warning(this, "Error", "Failed to load.");
    }
}

void MainWindow::onCreateSampleData() {
    if (QMessageBox::question(this, "Confirm", "Create sample data?") == QMessageBox::Yes) {
        manager->createSampleData();
        refreshStudentsTable(); refreshCoursesTable(); refreshGradesTable(); refreshProfessorsTable();
        QMessageBox::information(this, "Success", "Sample data created!");
    }
}

void MainWindow::onExportReport() { QMessageBox::information(this, "Export", "Report export feature."); }

void MainWindow::onAbout() {
    QMessageBox::about(this, "About",
        "<h2>Student Grade System</h2>"
        "<p>Version 1.0</p>"
        "<p>A comprehensive grade management application for universities.</p>");
}

void MainWindow::onTabChanged(int index) {
    switch (index) {
        case 0: refreshStudentsTable(); break;
        case 1: refreshCoursesTable(); break;
        case 2: refreshGradesTable(); break;
        case 3: refreshProfessorsTable(); break;
        case 4: refreshAnalytics(); break;
    }
}

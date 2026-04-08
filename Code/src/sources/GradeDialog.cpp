#include "GradeDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

GradeDialog::GradeDialog(QWidget* parent, bool enroll) : QDialog(parent), enrollMode(enroll) {
    manager = GradeManager::getInstance();
    setupUI();
    loadStudentsAndCourses();
}

void GradeDialog::setupUI() {
    setWindowTitle(enrollMode ? "Enroll Student in Course" : "Update Grade");
    setMinimumWidth(450);

    auto* main = new QVBoxLayout(this);
    auto* form = new QFormLayout();

    comboStudent = new QComboBox();
    form->addRow("Student:", comboStudent);

    comboCourse = new QComboBox();
    form->addRow("Course:", comboCourse);

    if (!enrollMode) {
        spinMidterm = new QDoubleSpinBox();
        spinMidterm->setRange(0, 100);
        spinMidterm->setDecimals(1);
        form->addRow("Midterm Score:", spinMidterm);

        spinFinal = new QDoubleSpinBox();
        spinFinal->setRange(0, 100);
        spinFinal->setDecimals(1);
        form->addRow("Final Score:", spinFinal);

        spinAssignment = new QDoubleSpinBox();
        spinAssignment->setRange(0, 100);
        spinAssignment->setDecimals(1);
        form->addRow("Assignment Score:", spinAssignment);
    }

    main->addLayout(form);

    auto* btns = new QHBoxLayout();
    btnSave = new QPushButton(enrollMode ? "Enroll" : "Update");
    btnSave->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px 30px; border-radius: 5px; }");
    connect(btnSave, &QPushButton::clicked, this, &GradeDialog::onSave);

    btnCancel = new QPushButton("Cancel");
    btnCancel->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 10px 30px; border-radius: 5px; }");
    connect(btnCancel, &QPushButton::clicked, this, &GradeDialog::onCancel);

    btns->addStretch();
    btns->addWidget(btnSave);
    btns->addWidget(btnCancel);
    main->addLayout(btns);
}

void GradeDialog::loadStudentsAndCourses() {
    for (const auto& s : manager->getAllStudents())
        comboStudent->addItem(QString("%1 - %2").arg(s->getStudentNumber(), s->getFullName()), s->getId());
    for (const auto& c : manager->getAllCourses())
        comboCourse->addItem(QString("%1 - %2").arg(c->getCourseCode(), c->getCourseName()), c->getCourseId());
}

void GradeDialog::onSave() {
    if (comboStudent->currentIndex() < 0 || comboCourse->currentIndex() < 0) {
        QMessageBox::warning(this, "Error", "Select student and course.");
        return;
    }

    int sId = comboStudent->currentData().toInt();
    int cId = comboCourse->currentData().toInt();

    if (enrollMode) {
        if (manager->enrollStudentInCourse(sId, cId)) {
            QMessageBox::information(this, "Success", "Student enrolled!");
            accept();
        } else {
            QMessageBox::warning(this, "Error", "Failed to enroll. Course may be full.");
        }
    } else {
        if (auto g = manager->findGrade(sId, cId)) {
            g->setMidtermScore(spinMidterm->value());
            g->setFinalScore(spinFinal->value());
            g->setAssignmentScore(spinAssignment->value());
            g->calculateTotal(0.3, 0.5, 0.2);
            if (auto s = manager->getStudent(sId)) s->addGrade(cId, g->getTotalScore());
            QMessageBox::information(this, "Success", "Grade updated!");
            accept();
        } else {
            QMessageBox::warning(this, "Error", "Grade not found.");
        }
    }
}

void GradeDialog::onCancel() { reject(); }

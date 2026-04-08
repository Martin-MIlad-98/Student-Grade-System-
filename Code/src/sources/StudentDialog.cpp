#include "StudentDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

StudentDialog::StudentDialog(QWidget* parent, int studId)
    : QDialog(parent), studentId(studId), isEditMode(studId != -1) {
    manager = GradeManager::getInstance();
    setupUI();
    if (isEditMode) loadStudentData();
}

void StudentDialog::setupUI() {
    setWindowTitle(isEditMode ? "Edit Student" : "Add New Student");
    setMinimumWidth(450);

    auto* main = new QVBoxLayout(this);
    auto* form = new QFormLayout();

    txtFirstName = new QLineEdit();
    form->addRow("First Name:", txtFirstName);

    txtLastName = new QLineEdit();
    form->addRow("Last Name:", txtLastName);

    txtEmail = new QLineEdit();
    txtEmail->setPlaceholderText("student@ecu.edu.eg");
    form->addRow("Email:", txtEmail);

    txtStudentNumber = new QLineEdit();
    txtStudentNumber->setPlaceholderText("STU001");
    txtStudentNumber->setEnabled(!isEditMode);
    form->addRow("Student Number:", txtStudentNumber);

    dateBirth = new QDateEdit();
    dateBirth->setCalendarPopup(true);
    dateBirth->setDate(QDate(2000, 1, 1));
    dateBirth->setDisplayFormat("yyyy-MM-dd");
    form->addRow("Birth Date:", dateBirth);

    comboMajor = new QComboBox();
    comboMajor->addItems({"Computer Science", "Physical Therapy", "Art and Design", "Engineering", "Business"});
    form->addRow("Major:", comboMajor);

    spinYear = new QSpinBox();
    spinYear->setRange(2015, 2030);
    spinYear->setValue(2021);
    form->addRow("Enrollment Year:", spinYear);

    main->addLayout(form);

    auto* btns = new QHBoxLayout();
    btnSave = new QPushButton(isEditMode ? "Update" : "Add");
    btnSave->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px 30px; border-radius: 5px; }");
    connect(btnSave, &QPushButton::clicked, this, &StudentDialog::onSave);

    btnCancel = new QPushButton("Cancel");
    btnCancel->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 10px 30px; border-radius: 5px; }");
    connect(btnCancel, &QPushButton::clicked, this, &StudentDialog::onCancel);

    btns->addStretch();
    btns->addWidget(btnSave);
    btns->addWidget(btnCancel);
    main->addLayout(btns);
}

void StudentDialog::loadStudentData() {
    if (auto s = manager->getStudent(studentId)) {
        txtFirstName->setText(s->getFirstName());
        txtLastName->setText(s->getLastName());
        txtEmail->setText(s->getEmail());
        txtStudentNumber->setText(s->getStudentNumber());
        dateBirth->setDate(s->getBirthDate());
        comboMajor->setCurrentText(s->getMajor());
        spinYear->setValue(s->getEnrollmentYear());
    }
}

bool StudentDialog::validateInput() {
    if (txtFirstName->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "First name required."); return false; }
    if (txtLastName->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "Last name required."); return false; }
    if (txtEmail->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "Email required."); return false; }
    if (txtStudentNumber->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "Student number required."); return false; }
    return true;
}

void StudentDialog::onSave() {
    if (!validateInput()) return;

    if (isEditMode) {
        if (auto s = manager->getStudent(studentId)) {
            s->setFirstName(txtFirstName->text().trimmed());
            s->setLastName(txtLastName->text().trimmed());
            s->setEmail(txtEmail->text().trimmed());
            s->setMajor(comboMajor->currentText());
        }
    } else {
        manager->addStudent(std::make_shared<Student>(
            manager->getStudentCount() + 1,
            txtFirstName->text().trimmed(), txtLastName->text().trimmed(),
            txtEmail->text().trimmed(), dateBirth->date(),
            txtStudentNumber->text().trimmed(), comboMajor->currentText(), spinYear->value()
        ));
    }
    accept();
}

void StudentDialog::onCancel() { reject(); }

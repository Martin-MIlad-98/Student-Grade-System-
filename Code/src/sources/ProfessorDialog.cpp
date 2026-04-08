#include "ProfessorDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

ProfessorDialog::ProfessorDialog(QWidget* parent) : QDialog(parent) {
    manager = GradeManager::getInstance();
    setupUI();
}

void ProfessorDialog::setupUI() {
    setWindowTitle("Add New Professor");
    setMinimumWidth(450);

    auto* main = new QVBoxLayout(this);
    auto* form = new QFormLayout();

    txtFirstName = new QLineEdit();
    form->addRow("First Name:", txtFirstName);

    txtLastName = new QLineEdit();
    form->addRow("Last Name:", txtLastName);

    txtEmail = new QLineEdit();
    txtEmail->setPlaceholderText("professor@ecu.edu.eg");
    form->addRow("Email:", txtEmail);

    txtEmployeeId = new QLineEdit();
    txtEmployeeId->setPlaceholderText("EMP001");
    form->addRow("Employee ID:", txtEmployeeId);

    dateBirth = new QDateEdit();
    dateBirth->setCalendarPopup(true);
    dateBirth->setDate(QDate(1980, 1, 1));
    dateBirth->setDisplayFormat("yyyy-MM-dd");
    form->addRow("Birth Date:", dateBirth);

    comboDepartment = new QComboBox();
    comboDepartment->addItems({"Computer Science", "Mathematics", "Physics", "Engineering", "Business"});
    form->addRow("Department:", comboDepartment);

    txtSpecialization = new QLineEdit();
    txtSpecialization->setPlaceholderText("e.g., Algorithms, Calculus");
    form->addRow("Specialization:", txtSpecialization);

    main->addLayout(form);

    auto* btns = new QHBoxLayout();
    btnSave = new QPushButton("Add");
    btnSave->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px 30px; border-radius: 5px; }");
    connect(btnSave, &QPushButton::clicked, this, &ProfessorDialog::onSave);

    btnCancel = new QPushButton("Cancel");
    btnCancel->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 10px 30px; border-radius: 5px; }");
    connect(btnCancel, &QPushButton::clicked, this, &ProfessorDialog::onCancel);

    btns->addStretch();
    btns->addWidget(btnSave);
    btns->addWidget(btnCancel);
    main->addLayout(btns);
}

bool ProfessorDialog::validateInput() {
    if (txtFirstName->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "First name required."); return false; }
    if (txtLastName->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "Last name required."); return false; }
    if (txtEmail->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "Email required."); return false; }
    if (txtEmployeeId->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "Employee ID required."); return false; }
    return true;
}

void ProfessorDialog::onSave() {
    if (!validateInput()) return;

    manager->addProfessor(std::make_shared<Professor>(
        manager->getProfessorCount() + 1,
        txtFirstName->text().trimmed(), txtLastName->text().trimmed(),
        txtEmail->text().trimmed(), dateBirth->date(),
        txtEmployeeId->text().trimmed(), comboDepartment->currentText(),
        txtSpecialization->text().trimmed()
    ));
    accept();
}

void ProfessorDialog::onCancel() { reject(); }

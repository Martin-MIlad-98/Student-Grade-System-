#ifndef PROFESSORDIALOG_H
#define PROFESSORDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include "GradeManager.h"

class ProfessorDialog : public QDialog {
    Q_OBJECT

private:
    GradeManager* manager;

    QLineEdit *txtFirstName, *txtLastName, *txtEmail, *txtEmployeeId, *txtSpecialization;
    QDateEdit* dateBirth;
    QComboBox* comboDepartment;
    QPushButton *btnSave, *btnCancel;

    void setupUI();
    bool validateInput();

private slots:
    void onSave();
    void onCancel();

public:
    ProfessorDialog(QWidget* parent = nullptr);
    ~ProfessorDialog() = default;
};

#endif

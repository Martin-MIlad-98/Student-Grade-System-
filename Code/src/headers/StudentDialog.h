#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include "GradeManager.h"

class StudentDialog : public QDialog {
    Q_OBJECT

private:
    GradeManager* manager;
    int studentId;
    bool isEditMode;

    QLineEdit *txtFirstName, *txtLastName, *txtEmail, *txtStudentNumber;
    QDateEdit* dateBirth;
    QComboBox* comboMajor;
    QSpinBox* spinYear;
    QPushButton *btnSave, *btnCancel;

    void setupUI();
    void loadStudentData();
    bool validateInput();

private slots:
    void onSave();
    void onCancel();

public:
    StudentDialog(QWidget* parent = nullptr, int studId = -1);
    ~StudentDialog() = default;
};

#endif

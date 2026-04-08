#ifndef COURSEDIALOG_H
#define COURSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include "GradeManager.h"

class CourseDialog : public QDialog {
    Q_OBJECT

private:
    GradeManager* manager;
    int courseId;
    bool isEditMode;

    QLineEdit *txtCourseCode, *txtCourseName, *txtExtraField;
    QTextEdit* txtDescription;
    QComboBox* comboCourseType;
    QSpinBox *spinCredits, *spinCapacity;
    QPushButton *btnSave, *btnCancel;

    void setupUI();
    void loadCourseData();
    bool validateInput();

private slots:
    void onSave();
    void onCancel();
    void onCourseTypeChanged(int index);

public:
    CourseDialog(QWidget* parent = nullptr, int crsId = -1);
    ~CourseDialog() = default;
};

#endif

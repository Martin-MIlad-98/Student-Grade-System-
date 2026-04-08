#ifndef GRADEDIALOG_H
#define GRADEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "GradeManager.h"

class GradeDialog : public QDialog {
    Q_OBJECT

private:
    GradeManager* manager;
    bool enrollMode;

    QComboBox *comboStudent, *comboCourse;
    QDoubleSpinBox *spinMidterm, *spinFinal, *spinAssignment;
    QPushButton *btnSave, *btnCancel;

    void setupUI();
    void loadStudentsAndCourses();

private slots:
    void onSave();
    void onCancel();

public:
    GradeDialog(QWidget* parent = nullptr, bool enroll = true);
    ~GradeDialog() = default;
};

#endif

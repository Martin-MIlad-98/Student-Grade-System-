#include "CourseDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

CourseDialog::CourseDialog(QWidget* parent, int crsId)
    : QDialog(parent), courseId(crsId), isEditMode(crsId != -1) {
    manager = GradeManager::getInstance();
    setupUI();
    if (isEditMode) loadCourseData();
}

void CourseDialog::setupUI() {
    setWindowTitle(isEditMode ? "Edit Course" : "Add New Course");
    setMinimumWidth(500);

    auto* main = new QVBoxLayout(this);
    auto* form = new QFormLayout();

    txtCourseCode = new QLineEdit();
    txtCourseCode->setPlaceholderText("CS101");
    form->addRow("Course Code:", txtCourseCode);

    txtCourseName = new QLineEdit();
    form->addRow("Course Name:", txtCourseName);

    txtDescription = new QTextEdit();
    txtDescription->setMaximumHeight(80);
    form->addRow("Description:", txtDescription);

    comboCourseType = new QComboBox();
    comboCourseType->addItems({"Core", "Elective", "Laboratory"});
    comboCourseType->setEnabled(!isEditMode);  // Can't change type after creation
    connect(comboCourseType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CourseDialog::onCourseTypeChanged);
    form->addRow("Course Type:", comboCourseType);

    spinCredits = new QSpinBox();
    spinCredits->setRange(1, 6);
    spinCredits->setValue(3);
    form->addRow("Credits:", spinCredits);

    spinCapacity = new QSpinBox();
    spinCapacity->setRange(10, 100);
    spinCapacity->setValue(30);
    form->addRow("Max Capacity:", spinCapacity);

    txtExtraField = new QLineEdit();
    form->addRow("Category/Lab Hours:", txtExtraField);

    main->addLayout(form);

    auto* btns = new QHBoxLayout();
    btnSave = new QPushButton(isEditMode ? "Update" : "Add");
    btnSave->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px 30px; border-radius: 5px; }");
    connect(btnSave, &QPushButton::clicked, this, &CourseDialog::onSave);

    btnCancel = new QPushButton("Cancel");
    btnCancel->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 10px 30px; border-radius: 5px; }");
    connect(btnCancel, &QPushButton::clicked, this, &CourseDialog::onCancel);

    btns->addStretch();
    btns->addWidget(btnSave);
    btns->addWidget(btnCancel);
    main->addLayout(btns);
}

void CourseDialog::loadCourseData() {
    if (auto c = manager->getCourse(courseId)) {
        txtCourseCode->setText(c->getCourseCode());
        txtCourseName->setText(c->getCourseName());
        txtDescription->setPlainText(c->getDescription());
        comboCourseType->setCurrentText(c->getCourseType());
        spinCredits->setValue(c->getCredits());
        spinCapacity->setValue(c->getMaxCapacity());
    }
}

bool CourseDialog::validateInput() {
    if (txtCourseCode->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "Course code required."); return false; }
    if (txtCourseName->text().trimmed().isEmpty()) { QMessageBox::warning(this, "Error", "Course name required."); return false; }
    return true;
}

void CourseDialog::onSave() {
    if (!validateInput()) return;

    if (isEditMode) {
        // Edit existing course - only update editable fields
        if (auto c = manager->getCourse(courseId)) {
            c->setCourseCode(txtCourseCode->text().trimmed());
            c->setCourseName(txtCourseName->text().trimmed());
            c->setDescription(txtDescription->toPlainText());
            c->setCredits(spinCredits->value());
            c->setMaxCapacity(spinCapacity->value());
        }
    } else {
        int id = manager->getCourseCount() + 1;
        QString type = comboCourseType->currentText();
        std::shared_ptr<Course> course;

        if (type == "Core") {
            course = std::make_shared<CoreCourse>(id, txtCourseCode->text().trimmed(),
                txtCourseName->text().trimmed(), txtDescription->toPlainText(),
                spinCredits->value(), spinCapacity->value());
        } else if (type == "Elective") {
            course = std::make_shared<ElectiveCourse>(id, txtCourseCode->text().trimmed(),
                txtCourseName->text().trimmed(), txtDescription->toPlainText(),
                spinCredits->value(), txtExtraField->text().isEmpty() ? "General" : txtExtraField->text(),
                spinCapacity->value());
        } else {
            course = std::make_shared<LabCourse>(id, txtCourseCode->text().trimmed(),
                txtCourseName->text().trimmed(), txtDescription->toPlainText(),
                spinCredits->value(), txtExtraField->text().isEmpty() ? 2 : txtExtraField->text().toInt(),
                spinCapacity->value());
        }
        manager->addCourse(course);
    }
    accept();
}

void CourseDialog::onCancel() { reject(); }
void CourseDialog::onCourseTypeChanged(int) {}

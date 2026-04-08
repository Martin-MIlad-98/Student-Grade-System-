#include "Course.h"

// ==================== Course Base Class ====================

int Course::getCourseId() const { return courseId; }
QString Course::getCourseCode() const { return courseCode; }
QString Course::getCourseName() const { return courseName; }
QString Course::getDescription() const { return description; }
int Course::getCredits() const { return credits; }
int Course::getTeacherId() const { return teacherId; }
int Course::getMaxCapacity() const { return maxCapacity; }
int Course::getEnrolledCount() const { return enrolledStudents.size(); }

void Course::setTeacher(int id) { teacherId = id; }
void Course::setDescription(const QString& d) { description = d; }
void Course::setCourseName(const QString& name) { courseName = name; }
void Course::setCourseCode(const QString& code) { courseCode = code; }
void Course::setCredits(int cred) { if (cred > 0 && cred <= 6) credits = cred; }
void Course::setMaxCapacity(int cap) { if (cap >= 10 && cap <= 200) maxCapacity = cap; }

bool Course::enrollStudent(int studentId) {
    if (isFull() || isStudentEnrolled(studentId)) return false;
    enrolledStudents.append(studentId);
    return true;
}

bool Course::removeStudent(int studentId) { return enrolledStudents.removeOne(studentId); }
bool Course::isStudentEnrolled(int id) const { return enrolledStudents.contains(id); }
QVector<int> Course::getEnrolledStudents() const { return enrolledStudents; }
bool Course::isFull() const { return enrolledStudents.size() >= maxCapacity; }

QString Course::getStatusString() const {
    if (isFull()) return "Full";
    return QString("%1 seats available").arg(maxCapacity - enrolledStudents.size());
}

// ==================== CoreCourse ====================

CoreCourse::CoreCourse(int id, const QString& code, const QString& name, const QString& desc, int cred, int cap)
    : Course(id, code, name, desc, cred, cap) {}

QString CoreCourse::getCourseType() const { return "Core"; }

double CoreCourse::calculateWeightedGrade(double mid, double fin, double assign) const {
    return mid * 0.30 + fin * 0.50 + assign * 0.20;
}

// ==================== ElectiveCourse ====================

ElectiveCourse::ElectiveCourse(int id, const QString& code, const QString& name, const QString& desc,
                               int cred, const QString& cat, int cap)
    : Course(id, code, name, desc, cred, cap), category(cat) {}

QString ElectiveCourse::getCourseType() const { return "Elective"; }

double ElectiveCourse::calculateWeightedGrade(double mid, double fin, double assign) const {
    return mid * 0.25 + fin * 0.40 + assign * 0.35;
}

QString ElectiveCourse::getCategory() const { return category; }

// ==================== LabCourse ====================

LabCourse::LabCourse(int id, const QString& code, const QString& name, const QString& desc,
                     int cred, int hours, int cap)
    : Course(id, code, name, desc, cred, cap), labHours(hours) {}

QString LabCourse::getCourseType() const { return "Laboratory"; }

double LabCourse::calculateWeightedGrade(double mid, double fin, double assign) const {
    return mid * 0.20 + fin * 0.30 + assign * 0.50;
}

int LabCourse::getLabHours() const { return labHours; }
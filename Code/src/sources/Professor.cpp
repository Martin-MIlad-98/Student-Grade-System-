#include "Professor.h"

QString Professor::getRole() const { return "Professor"; }

QString Professor::getDisplayInfo() const {
    return QString("Professor: %1\nEmployee ID: %2\nDepartment: %3\nCourses: %4")
        .arg(getFullName(), employeeId, department, QString::number(assignedCourses.size()));
}

QString Professor::getEmployeeId() const { return employeeId; }
QString Professor::getDepartment() const { return department; }
QString Professor::getSpecialization() const { return specialization; }

void Professor::setDepartment(const QString& d) { department = d; }
void Professor::setSpecialization(const QString& s) { specialization = s; }

void Professor::assignCourse(int courseId) {
    if (!assignedCourses.contains(courseId)) assignedCourses.append(courseId);
}

void Professor::removeCourse(int courseId) { assignedCourses.removeAll(courseId); }
bool Professor::isAssignedTo(int courseId) const { return assignedCourses.contains(courseId); }
QVector<int> Professor::getAssignedCourses() const { return assignedCourses; }
int Professor::getCourseCount() const { return assignedCourses.size(); }

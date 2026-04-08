#include "Student.h"

QString Student::getRole() const { return "Student"; }

QString Student::getDisplayInfo() const {
    return QString("Student: %1\nID: %2\nMajor: %3\nGPA: %4")
        .arg(getFullName(), studentNumber, major, QString::number(calculateGPA(), 'f', 2));
}

QString Student::getStudentNumber() const { return studentNumber; }
QString Student::getMajor() const { return major; }
int Student::getEnrollmentYear() const { return enrollmentYear; }
void Student::setMajor(const QString& m) { major = m; }

void Student::addGrade(int courseId, double grade) {
    if (grade >= 0.0 && grade <= 100.0) courseGrades.insert(courseId, grade);
}

void Student::updateGrade(int courseId, double grade) {
    if (courseGrades.contains(courseId) && grade >= 0.0 && grade <= 100.0)
        courseGrades[courseId] = grade;
}

double Student::getGrade(int courseId) const { return courseGrades.value(courseId, -1.0); }
bool Student::hasGrade(int courseId) const { return courseGrades.contains(courseId); }
QMap<int, double> Student::getAllGrades() const { return courseGrades; }

double Student::calculateGPA() const {
    if (courseGrades.isEmpty()) return 0.0;

    double total = 0.0;
    for (double grade : courseGrades) {
        if (grade >= 90) total += 4.0;
        else if (grade >= 85) total += 3.7;
        else if (grade >= 80) total += 3.3;
        else if (grade >= 75) total += 3.0;
        else if (grade >= 70) total += 2.7;
        else if (grade >= 65) total += 2.3;
        else if (grade >= 60) total += 2.0;
        else if (grade >= 55) total += 1.7;
        else if (grade >= 50) total += 1.0;
    }
    return total / courseGrades.size();
}

double Student::calculateCourseAverage() const {
    if (courseGrades.isEmpty()) return 0.0;
    double total = 0.0;
    for (double grade : courseGrades) total += grade;
    return total / courseGrades.size();
}

QString Student::getLetterGrade(double grade) const {
    if (grade >= 95) return "A+";
    if (grade >= 90) return "A";
    if (grade >= 85) return "A-";
    if (grade >= 80) return "B+";
    if (grade >= 75) return "B";
    if (grade >= 70) return "B-";
    if (grade >= 65) return "C+";
    if (grade >= 60) return "C";
    if (grade >= 55) return "C-";
    if (grade >= 50) return "D";
    return "F";
}

QString Student::getAcademicStanding() const {
    double gpa = calculateGPA();
    if (gpa >= 3.5) return "Dean's List";
    if (gpa >= 3.0) return "Good Standing";
    if (gpa >= 2.0) return "Satisfactory";
    if (gpa >= 1.0) return "Academic Warning";
    return "Academic Probation";
}

#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <QMap>

class Student : public Person {
private:
    QString studentNumber, major;
    int enrollmentYear;
    QMap<int, double> courseGrades;

public:
    Student(int id, const QString& first, const QString& last, const QString& mail,
            const QDate& birth, const QString& stdNum, const QString& maj, int year)
        : Person(id, first, last, mail, birth), studentNumber(stdNum), major(maj), enrollmentYear(year) {}

    QString getRole() const override;
    QString getDisplayInfo() const override;

    QString getStudentNumber() const;
    QString getMajor() const;
    int getEnrollmentYear() const;
    void setMajor(const QString& m);

    void addGrade(int courseId, double grade);
    void updateGrade(int courseId, double grade);
    double getGrade(int courseId) const;
    bool hasGrade(int courseId) const;
    QMap<int, double> getAllGrades() const;

    double calculateGPA() const;
    double calculateCourseAverage() const;
    QString getLetterGrade(double grade) const;
    QString getAcademicStanding() const;

    bool operator<(const Student& o) const { return calculateGPA() < o.calculateGPA(); }
    bool operator>(const Student& o) const { return calculateGPA() > o.calculateGPA(); }
};

#endif

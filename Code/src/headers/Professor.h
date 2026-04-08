#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Person.h"
#include <QVector>

class Professor : public Person {
private:
    QString employeeId, department, specialization;
    QVector<int> assignedCourses;

public:
    Professor(int id, const QString& first, const QString& last, const QString& mail,
              const QDate& birth, const QString& empId, const QString& dept, const QString& spec)
        : Person(id, first, last, mail, birth), employeeId(empId), department(dept), specialization(spec) {}

    QString getRole() const override;
    QString getDisplayInfo() const override;

    QString getEmployeeId() const;
    QString getDepartment() const;
    QString getSpecialization() const;

    void setDepartment(const QString& d);
    void setSpecialization(const QString& s);

    void assignCourse(int courseId);
    void removeCourse(int courseId);
    bool isAssignedTo(int courseId) const;
    QVector<int> getAssignedCourses() const;
    int getCourseCount() const;
};

#endif

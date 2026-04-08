#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QVector>

class Course {
private:
    int courseId, credits, teacherId, maxCapacity;
    QString courseCode, courseName, description;
    QVector<int> enrolledStudents;

public:
    Course(int id, const QString& code, const QString& name, const QString& desc, int cred, int cap = 30)
        : courseId(id), credits(cred), teacherId(-1), maxCapacity(cap),
          courseCode(code), courseName(name), description(desc) {}
    virtual ~Course() = default;

    virtual QString getCourseType() const = 0;
    virtual double calculateWeightedGrade(double mid, double fin, double assign) const = 0;

    int getCourseId() const;
    QString getCourseCode() const;
    QString getCourseName() const;
    QString getDescription() const;
    int getCredits() const;
    int getTeacherId() const;
    int getMaxCapacity() const;
    int getEnrolledCount() const;

    void setTeacher(int id);
    void setDescription(const QString& d);
    void setCourseName(const QString& name);
    void setCourseCode(const QString& code);
    void setCredits(int cred);
    void setMaxCapacity(int cap);

    bool enrollStudent(int studentId);
    bool removeStudent(int studentId);
    bool isStudentEnrolled(int id) const;
    QVector<int> getEnrolledStudents() const;
    bool isFull() const;
    QString getStatusString() const;
};

class CoreCourse : public Course {
public:
    CoreCourse(int id, const QString& code, const QString& name, const QString& desc, int cred, int cap = 30);
    QString getCourseType() const override;
    double calculateWeightedGrade(double mid, double fin, double assign) const override;
};

class ElectiveCourse : public Course {
private:
    QString category;
public:
    ElectiveCourse(int id, const QString& code, const QString& name, const QString& desc,
                   int cred, const QString& cat, int cap = 25);
    QString getCourseType() const override;
    double calculateWeightedGrade(double mid, double fin, double assign) const override;
    QString getCategory() const;
};

class LabCourse : public Course {
private:
    int labHours;
public:
    LabCourse(int id, const QString& code, const QString& name, const QString& desc,
              int cred, int hours, int cap = 20);
    QString getCourseType() const override;
    double calculateWeightedGrade(double mid, double fin, double assign) const override;
    int getLabHours() const;
};

#endif

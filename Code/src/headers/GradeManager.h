#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include "DataRepository.h"
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "Grade.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QVector>
#include <QMap>

class GradeManager {
private:
    DataRepository<Student> students;
    DataRepository<Professor> professors;
    DataRepository<Course> courses;
    DataRepository<Grade> grades;
    QString dataFilePath;
    static GradeManager* instance;

    GradeManager();

public:
    static GradeManager* getInstance();
    ~GradeManager() = default;

    GradeManager(const GradeManager&) = delete;
    GradeManager& operator=(const GradeManager&) = delete;

    // Add operations
    int addStudent(std::shared_ptr<Student> s) { return students.addWithId(s->getId(), s), s->getId(); }
    int addProfessor(std::shared_ptr<Professor> p) { return professors.addWithId(p->getId(), p), p->getId(); }
    int addCourse(std::shared_ptr<Course> c) { return courses.addWithId(c->getCourseId(), c), c->getCourseId(); }
    int addGrade(std::shared_ptr<Grade> g) { return grades.add(g); }

    // Remove operations
    bool removeStudent(int id) { return students.remove(id); }
    bool removeProfessor(int id) { return professors.remove(id); }
    bool removeCourse(int id) { return courses.remove(id); }
    bool removeGrade(int id) { return grades.remove(id); }

    // Get operations
    std::shared_ptr<Student> getStudent(int id) const { return students.get(id); }
    std::shared_ptr<Professor> getProfessor(int id) const { return professors.get(id); }
    std::shared_ptr<Course> getCourse(int id) const { return courses.get(id); }
    std::shared_ptr<Grade> getGrade(int id) const { return grades.get(id); }

    // Get all
    QVector<std::shared_ptr<Student>> getAllStudents() const;
    QVector<std::shared_ptr<Professor>> getAllProfessors() const;
    QVector<std::shared_ptr<Course>> getAllCourses() const;
    QVector<std::shared_ptr<Grade>> getAllGrades() const;

    // Grade queries
    QVector<std::shared_ptr<Grade>> getStudentGrades(int studentId) const;
    QVector<std::shared_ptr<Grade>> getCourseGrades(int courseId) const;
    std::shared_ptr<Grade> findGrade(int studentId, int courseId) const;

    // Operations
    bool enrollStudentInCourse(int studentId, int courseId);
    bool assignProfessorToCourse(int professorId, int courseId);

    // Analytics
    double calculateCourseAverage(int courseId) const;
    QVector<std::shared_ptr<Student>> getTopStudents(int count) const;
    QMap<QString, int> getGradeDistribution(int courseId) const;

    // Persistence
    bool saveToFile(const QString& filename = "");
    bool loadFromFile(const QString& filename = "");
    void createSampleData();

    // Counts
    int getStudentCount() const { return students.count(); }
    int getProfessorCount() const { return professors.count(); }
    int getCourseCount() const { return courses.count(); }
    int getGradeCount() const { return grades.count(); }
};

#endif

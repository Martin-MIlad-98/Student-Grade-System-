#ifndef GRADE_H
#define GRADE_H

#include <QString>
#include <QDateTime>

class Grade {
private:
    int gradeId, studentId, courseId;
    double midtermScore, finalScore, assignmentScore, totalScore;
    QString letterGrade, comments;
    QDateTime lastUpdated;

public:
    Grade(int id, int studId, int crsId)
        : gradeId(id), studentId(studId), courseId(crsId),
          midtermScore(0), finalScore(0), assignmentScore(0), totalScore(0),
          letterGrade("N/A"), lastUpdated(QDateTime::currentDateTime()) {}

    int getGradeId() const;
    int getStudentId() const;
    int getCourseId() const;
    double getMidtermScore() const;
    double getFinalScore() const;
    double getAssignmentScore() const;
    double getTotalScore() const;
    QString getLetterGrade() const;
    QDateTime getLastUpdated() const;
    QString getComments() const;

    void setMidtermScore(double s);
    void setFinalScore(double s);
    void setAssignmentScore(double s);
    void setComments(const QString& c);

    void calculateTotal(double midW, double finW, double assignW);
    void updateLetterGrade();

    bool isPassing() const;
    QString getStatus() const;
};

#endif

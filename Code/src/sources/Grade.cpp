#include "Grade.h"

int Grade::getGradeId() const { return gradeId; }
int Grade::getStudentId() const { return studentId; }
int Grade::getCourseId() const { return courseId; }
double Grade::getMidtermScore() const { return midtermScore; }
double Grade::getFinalScore() const { return finalScore; }
double Grade::getAssignmentScore() const { return assignmentScore; }
double Grade::getTotalScore() const { return totalScore; }
QString Grade::getLetterGrade() const { return letterGrade; }
QDateTime Grade::getLastUpdated() const { return lastUpdated; }
QString Grade::getComments() const { return comments; }

void Grade::setMidtermScore(double s) {
    if (s >= 0 && s <= 100) {
        midtermScore = s;
        lastUpdated = QDateTime::currentDateTime();
    }
}

void Grade::setFinalScore(double s) {
    if (s >= 0 && s <= 100) {
        finalScore = s;
        lastUpdated = QDateTime::currentDateTime();
    }
}

void Grade::setAssignmentScore(double s) {
    if (s >= 0 && s <= 100) {
        assignmentScore = s;
        lastUpdated = QDateTime::currentDateTime();
    }
}

void Grade::setComments(const QString& c) { comments = c; }

void Grade::calculateTotal(double midW, double finW, double assignW) {
    totalScore = midtermScore * midW + finalScore * finW + assignmentScore * assignW;
    updateLetterGrade();
    lastUpdated = QDateTime::currentDateTime();
}

void Grade::updateLetterGrade() {
    if (totalScore >= 95) letterGrade = "A+";
    else if (totalScore >= 90) letterGrade = "A";
    else if (totalScore >= 85) letterGrade = "A-";
    else if (totalScore >= 80) letterGrade = "B+";
    else if (totalScore >= 75) letterGrade = "B";
    else if (totalScore >= 70) letterGrade = "B-";
    else if (totalScore >= 65) letterGrade = "C+";
    else if (totalScore >= 60) letterGrade = "C";
    else if (totalScore >= 55) letterGrade = "C-";
    else if (totalScore >= 50) letterGrade = "D";
    else letterGrade = "F";
}

bool Grade::isPassing() const { return totalScore >= 50.0; }
QString Grade::getStatus() const { return isPassing() ? "Pass" : "Fail"; }

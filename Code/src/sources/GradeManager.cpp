#include "GradeManager.h"
#include <QStandardPaths>
#include <QDir>
#include <algorithm>

GradeManager* GradeManager::instance = nullptr;

GradeManager::GradeManager() {
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath);
    dataFilePath = appDataPath + "/gradedata.json";
}

GradeManager* GradeManager::getInstance() {
    if (!instance) instance = new GradeManager();
    return instance;
}

QVector<std::shared_ptr<Student>> GradeManager::getAllStudents() const {
    auto vec = students.getAll();
    return QVector<std::shared_ptr<Student>>(vec.begin(), vec.end());
}

QVector<std::shared_ptr<Professor>> GradeManager::getAllProfessors() const {
    auto vec = professors.getAll();
    return QVector<std::shared_ptr<Professor>>(vec.begin(), vec.end());
}

QVector<std::shared_ptr<Course>> GradeManager::getAllCourses() const {
    auto vec = courses.getAll();
    return QVector<std::shared_ptr<Course>>(vec.begin(), vec.end());
}

QVector<std::shared_ptr<Grade>> GradeManager::getAllGrades() const {
    auto vec = grades.getAll();
    return QVector<std::shared_ptr<Grade>>(vec.begin(), vec.end());
}

QVector<std::shared_ptr<Grade>> GradeManager::getStudentGrades(int studentId) const {
    auto vec = grades.filter([studentId](const auto& g) { return g->getStudentId() == studentId; });
    return QVector<std::shared_ptr<Grade>>(vec.begin(), vec.end());
}

QVector<std::shared_ptr<Grade>> GradeManager::getCourseGrades(int courseId) const {
    auto vec = grades.filter([courseId](const auto& g) { return g->getCourseId() == courseId; });
    return QVector<std::shared_ptr<Grade>>(vec.begin(), vec.end());
}

std::shared_ptr<Grade> GradeManager::findGrade(int studentId, int courseId) const {
    auto result = grades.filter([=](const auto& g) {
        return g->getStudentId() == studentId && g->getCourseId() == courseId;
    });
    return result.empty() ? nullptr : result.front();
}

bool GradeManager::enrollStudentInCourse(int studentId, int courseId) {
    auto student = getStudent(studentId);
    auto course = getCourse(courseId);
    if (!student || !course) return false;

    if (course->enrollStudent(studentId)) {
        addGrade(std::make_shared<Grade>(grades.getNextId(), studentId, courseId));
        return true;
    }
    return false;
}

bool GradeManager::assignProfessorToCourse(int professorId, int courseId) {
    auto prof = getProfessor(professorId);
    auto course = getCourse(courseId);
    if (!prof || !course) return false;

    course->setTeacher(professorId);
    prof->assignCourse(courseId);
    return true;
}

double GradeManager::calculateCourseAverage(int courseId) const {
    auto courseGrades = getCourseGrades(courseId);
    if (courseGrades.isEmpty()) return 0.0;

    double total = 0.0;
    int count = 0;
    for (const auto& g : courseGrades) {
        if (g->getTotalScore() > 0) { total += g->getTotalScore(); count++; }
    }
    return count > 0 ? total / count : 0.0;
}

QVector<std::shared_ptr<Student>> GradeManager::getTopStudents(int count) const {
    auto all = getAllStudents();
    std::sort(all.begin(), all.end(), [](const auto& a, const auto& b) {
        return a->calculateGPA() > b->calculateGPA();
    });
    return all.size() <= count ? all : all.mid(0, count);
}

QMap<QString, int> GradeManager::getGradeDistribution(int courseId) const {
    QMap<QString, int> dist{{"A", 0}, {"B", 0}, {"C", 0}, {"D", 0}, {"F", 0}};
    for (const auto& g : getCourseGrades(courseId)) {
        QString letter = g->getLetterGrade();
        if (letter.startsWith("A")) dist["A"]++;
        else if (letter.startsWith("B")) dist["B"]++;
        else if (letter.startsWith("C")) dist["C"]++;
        else if (letter.startsWith("D")) dist["D"]++;
        else dist["F"]++;
    }
    return dist;
}

bool GradeManager::saveToFile(const QString& filename) {
    QString path = filename.isEmpty() ? dataFilePath : filename;
    QJsonObject root;

    QJsonArray studentsArr;
    for (const auto& s : getAllStudents()) {
        QJsonObject obj;
        obj["id"] = s->getId();
        obj["firstName"] = s->getFirstName();
        obj["lastName"] = s->getLastName();
        obj["email"] = s->getEmail();
        obj["birthDate"] = s->getBirthDate().toString(Qt::ISODate);
        obj["studentNumber"] = s->getStudentNumber();
        obj["major"] = s->getMajor();
        obj["enrollmentYear"] = s->getEnrollmentYear();
        studentsArr.append(obj);
    }
    root["students"] = studentsArr;

    QJsonArray profsArr;
    for (const auto& p : getAllProfessors()) {
        QJsonObject obj;
        obj["id"] = p->getId();
        obj["firstName"] = p->getFirstName();
        obj["lastName"] = p->getLastName();
        obj["email"] = p->getEmail();
        obj["birthDate"] = p->getBirthDate().toString(Qt::ISODate);
        obj["employeeId"] = p->getEmployeeId();
        obj["department"] = p->getDepartment();
        obj["specialization"] = p->getSpecialization();
        profsArr.append(obj);
    }
    root["professors"] = profsArr;

    QJsonArray gradesArr;
    for (const auto& g : getAllGrades()) {
        QJsonObject obj;
        obj["id"] = g->getGradeId();
        obj["studentId"] = g->getStudentId();
        obj["courseId"] = g->getCourseId();
        obj["midterm"] = g->getMidtermScore();
        obj["final"] = g->getFinalScore();
        obj["assignment"] = g->getAssignmentScore();
        obj["total"] = g->getTotalScore();
        obj["letter"] = g->getLetterGrade();
        obj["comments"] = g->getComments();
        gradesArr.append(obj);
    }
    root["grades"] = gradesArr;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(QJsonDocument(root).toJson());
    return true;
}

bool GradeManager::loadFromFile(const QString& filename) {
    QString path = filename.isEmpty() ? dataFilePath : filename;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) return false;

    QJsonObject root = doc.object();

    for (const auto& val : root["students"].toArray()) {
        QJsonObject o = val.toObject();
        addStudent(std::make_shared<Student>(
            o["id"].toInt(), o["firstName"].toString(), o["lastName"].toString(),
            o["email"].toString(), QDate::fromString(o["birthDate"].toString(), Qt::ISODate),
            o["studentNumber"].toString(), o["major"].toString(), o["enrollmentYear"].toInt()
        ));
    }

    for (const auto& val : root["professors"].toArray()) {
        QJsonObject o = val.toObject();
        addProfessor(std::make_shared<Professor>(
            o["id"].toInt(), o["firstName"].toString(), o["lastName"].toString(),
            o["email"].toString(), QDate::fromString(o["birthDate"].toString(), Qt::ISODate),
            o["employeeId"].toString(), o["department"].toString(), o["specialization"].toString()
        ));
    }

    return true;
}

void GradeManager::createSampleData() {
    // Sample Students
    addStudent(std::make_shared<Student>(1, "Mohamed", "Monged", "Mohamed.Monged@ecu.edu.eg",
        QDate(2002, 5, 15), "STU001", "Engineering", 2023));
    addStudent(std::make_shared<Student>(2, "Nicole", "Aziz", "Nicole.Aziz@ecu.edu.eg",
        QDate(2001, 8, 22), "STU002", "Mathematics", 2020));
    addStudent(std::make_shared<Student>(3, "Martin", "Milad", "Martin.Milad@ecu.edu.eg",
        QDate(2003, 1, 10), "STU003", "Computer Science", 2022));
    addStudent(std::make_shared<Student>(4, "Mina", "Ehab", "Mina.Ehab@ecu.edu.eg",
        QDate(2002, 11, 5), "STU004", "Physics", 2021));
    addStudent(std::make_shared<Student>(5, "Seaf", "Waleed", "Seaf.Waleed@ecu.edu.eg",
        QDate(2001, 3, 18), "STU005", "Engineering", 2020));

    // Sample Professors
    addProfessor(std::make_shared<Professor>(1, "Dr. Sherry", "Aly", "Sherry.Aly@ecu.edu.eg",
        QDate(1975, 6, 20), "EMP001", "Computer Science", "Algorithms"));
    addProfessor(std::make_shared<Professor>(2, "Prof. Hussen", "Mohamed", "Hussen.Mohamed@ecu.edu.eg",
        QDate(1980, 9, 12), "EMP002", "Mathematics", "Calculus"));
    addProfessor(std::make_shared<Professor>(3, "Prof. Mohamed", "Hany", "Mohamed.Hany@ecu.edu.eg",
        QDate(1980, 8, 25), "EMP003", "Mathematics", "Calculus"));

    // Sample Courses
    addCourse(std::make_shared<CoreCourse>(1, "CS101", "Introduction to Programming",
        "Fundamentals of programming using C++", 3));
    addCourse(std::make_shared<CoreCourse>(2, "CS201", "Data Structures",
        "Advanced data structures and algorithms", 4));
    addCourse(std::make_shared<ElectiveCourse>(3, "MATH201", "Linear Algebra",
        "Vectors, matrices, and linear transformations", 3, "Mathematics"));
    addCourse(std::make_shared<LabCourse>(4, "CS301L", "Programming Lab",
        "Hands-on programming exercises", 2, 4));

    // Assign professors to courses
    assignProfessorToCourse(1, 1);
    assignProfessorToCourse(1, 2);
    assignProfessorToCourse(2, 3);

    // Enroll students
    enrollStudentInCourse(1, 1); enrollStudentInCourse(1, 2);
    enrollStudentInCourse(2, 1); enrollStudentInCourse(2, 3);
    enrollStudentInCourse(3, 1); enrollStudentInCourse(3, 2);
    enrollStudentInCourse(4, 3);
    enrollStudentInCourse(5, 1); enrollStudentInCourse(5, 2);

    // Update grades
    auto updateGrade = [this](int sId, int cId, double mid, double fin, double assign) {
        if (auto g = findGrade(sId, cId)) {
            g->setMidtermScore(mid);
            g->setFinalScore(fin);
            g->setAssignmentScore(assign);
            g->calculateTotal(0.3, 0.5, 0.2);
            if (auto s = getStudent(sId)) s->addGrade(cId, g->getTotalScore());
        }
    };

    updateGrade(1, 1, 85, 90, 88);
    updateGrade(1, 2, 78, 82, 85);
    updateGrade(2, 1, 92, 95, 90);
    updateGrade(2, 3, 88, 91, 87);
    updateGrade(3, 1, 70, 75, 80);
    updateGrade(3, 2, 65, 70, 72);
    updateGrade(4, 3, 80, 85, 82);
    updateGrade(5, 1, 88, 84, 90);
    updateGrade(5, 2, 75, 80, 78);
}

#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>

class Person {
protected:
    int id;
    QString firstName, lastName, email;
    QDate birthDate;

public:
    Person(int id, const QString& first, const QString& last, const QString& mail, const QDate& birth)
        : id(id), firstName(first), lastName(last), email(mail), birthDate(birth) {}
    virtual ~Person() = default;

    virtual QString getFullName() const;
    virtual QString getRole() const = 0;
    virtual QString getDisplayInfo() const = 0;

    int getId() const;
    QString getFirstName() const;
    QString getLastName() const;
    QString getEmail() const;
    QDate getBirthDate() const;

    void setFirstName(const QString& first);
    void setLastName(const QString& last);
    void setEmail(const QString& mail);

    bool operator==(const Person& o) const;
    bool operator!=(const Person& o) const;
};

#endif

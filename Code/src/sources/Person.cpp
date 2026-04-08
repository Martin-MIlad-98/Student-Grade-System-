#include "Person.h"

QString Person::getFullName() const { return firstName + " " + lastName; }

int Person::getId() const { return id; }
QString Person::getFirstName() const { return firstName; }
QString Person::getLastName() const { return lastName; }
QString Person::getEmail() const { return email; }
QDate Person::getBirthDate() const { return birthDate; }

void Person::setFirstName(const QString& first) { firstName = first; }
void Person::setLastName(const QString& last) { lastName = last; }
void Person::setEmail(const QString& mail) { email = mail; }

bool Person::operator==(const Person& o) const { return id == o.id; }
bool Person::operator!=(const Person& o) const { return id != o.id; }

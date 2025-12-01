#include "person.h"

Person::Person(string n) : name(n) {}

Person::Person(const Person &other) : name(other.name) {}

string Person::getName() const { return name; }

Person &Person::operator=(const Person &other)
{
    if (this != &other)
    {
        name = other.name;
    }
    return *this;
}

bool Person::operator==(const Person &other) const
{
    return name == other.name;
}

bool Person::operator!=(const Person &other) const
{
    return !(*this == other);
}

bool Person::operator<(const Person &other) const
{
    return name < other.name;
}

bool Person::operator>(const Person &other) const
{
    return name > other.name;
}

ostream &operator<<(ostream &out, const Person &person)
{
    out << "Person: " << person.name;
    return out;
}

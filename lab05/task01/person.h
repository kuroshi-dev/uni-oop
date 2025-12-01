#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

class Person
{
protected:
    string name;

public:
    Person(string n = "");
    Person(const Person &other); // copy constructor
    string getName() const;
    virtual void displayInfo() const = 0;
    virtual ~Person() {}

    Person &operator=(const Person &other);
    bool operator==(const Person &other) const;
    bool operator!=(const Person &other) const;
    bool operator<(const Person &other) const;
    bool operator>(const Person &other) const;
    friend ostream &operator<<(ostream &out, const Person &person);
};

#endif // PERSON_H

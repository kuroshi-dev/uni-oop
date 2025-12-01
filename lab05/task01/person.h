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
    Person(Person &other);
    string getName();
    virtual void displayInfo() = 0;
    virtual ~Person() {}

    Person &operator=(Person &other);
    bool operator==(Person &other);
    bool operator!=(Person &other);
    bool operator<(Person &other);
    bool operator>(Person &other);
    friend ostream &operator<<(ostream &out, Person &person);
};

#endif // PERSON_H

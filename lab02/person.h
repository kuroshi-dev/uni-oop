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
    Person(string n);
    string getName();
    virtual void displayInfo() = 0;
    virtual ~Person(){}
};

#endif // PERSON_H

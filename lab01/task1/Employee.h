#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <windows.h>
#include <iostream>

using namespace std;

class Employee{
private:
    short id;
    string name;
    int salary;
public:
    Employee();

    Employee(short newId, string newName, int newSalary) : id(newId), name(newName), salary(newSalary) {};

    ~Employee();

    short getId();
    void setId(short id);


    string getName();
    void setName(string name);

    int getSalary();
    void setSalary(int salary);
};

#endif // EMPLOYEE_H

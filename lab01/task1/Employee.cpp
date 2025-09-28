#include "Employee.h"

Employee::Employee() {
    id = 0;
    name = "User";
    salary = 1000;
}

Employee::~Employee(){ cout << "\nObject Removed\n";};

short Employee::getId() { return id; }
void Employee::setId(short id) { this->id = id; }

string Employee::getName() { return name; }
void Employee::setName(string name) { this->name = name; }

int Employee::getSalary() { return salary; }
void Employee::setSalary(int salary) { this->salary = salary; }


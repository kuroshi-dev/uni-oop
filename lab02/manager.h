#ifndef MANAGER_H
#define MANAGER_H

#include "person.h"

class Manager : public Person {
private:
    string phone;

public:
    Manager(string n, string p);

    string getPhone();
    void displayInfo();
};

#endif // MANAGER_H

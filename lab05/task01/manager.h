#ifndef MANAGER_H
#define MANAGER_H

#include "person.h"

class Manager : public Person
{
protected:
    string phone;

public:
    Manager(string n = "", string p = "");
    Manager(Manager &other);

    string getPhone();
    void displayInfo() override;

    Manager &operator=(Manager &other);
    bool operator==(Manager &other);
    bool operator!=(Manager &other);

    friend ostream &operator<<(ostream &out, Manager &manager);
};

#endif // MANAGER_H

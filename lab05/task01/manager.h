#ifndef MANAGER_H
#define MANAGER_H

#include "person.h"

class Manager : public Person
{
protected:
    string phone;

public:
    Manager(string n = "", string p = "");
    Manager(const Manager &other);

    string getPhone() const;
    void displayInfo() const override;

    Manager &operator=(const Manager &other);
    bool operator==(const Manager &other) const;
    bool operator!=(const Manager &other) const;

    friend ostream &operator<<(ostream &out, const Manager &manager);
};

#endif // MANAGER_H

#ifndef LEADER_H
#define LEADER_H

#include "person.h"

class Leader : public Person {
private:
    int experience;
public:
    Leader(string n, int exp);
    int getExperience();
    void displayInfo();
};

#endif // LEADER_H

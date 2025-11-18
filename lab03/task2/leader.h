#ifndef LEADER_H
#define LEADER_H

#include "musician.h"

class Leader : public Musician {
private:
    int experience;
public:
    Leader(string n, string p, string instrName, int instrYear, int exp);
    void displayInfo();
    int getExperience();
};
#endif // LEADER_H

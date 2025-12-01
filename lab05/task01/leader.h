#ifndef LEADER_H
#define LEADER_H

#include "musician.h"

class Leader : public Musician
{
private:
    int experience;

public:
    Leader(string n = "", string p = "", string instrName = "", int instrYear = 0, int exp = 0);
    Leader(Leader &other);

    void displayInfo() override;
    int getExperience();

    Leader &operator=(Leader &other);
    bool operator==(Leader &other);
    bool operator!=(Leader &other);
    bool operator<(Leader &other);
    bool operator>(Leader &other);
    Leader operator+(int years);
    Leader operator-(int years);
    Leader &operator+=(int years);
    Leader &operator-=(int years);

    friend ostream &operator<<(ostream &out, Leader &leader);
};
#endif // LEADER_H

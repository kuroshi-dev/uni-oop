#ifndef LEADER_H
#define LEADER_H

#include "musician.h"

class Leader : public Musician
{
private:
    int experience;

public:
    Leader(string n = "", string p = "", string instrName = "", int instrYear = 0, int exp = 0);
    Leader(const Leader &other);

    void displayInfo() const override;
    int getExperience() const;

    Leader &operator=(const Leader &other);
    bool operator==(const Leader &other) const;
    bool operator!=(const Leader &other) const;
    bool operator<(const Leader &other) const;
    bool operator>(const Leader &other) const;
    Leader operator+(int years) const;
    Leader operator-(int years) const;
    Leader &operator+=(int years);
    Leader &operator-=(int years);

    friend ostream &operator<<(ostream &out, const Leader &leader);
};
#endif // LEADER_H

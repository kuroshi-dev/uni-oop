#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <iostream>
#include <string>

using namespace std;

class Instrument
{
private:
    string name;
    int yearMade;

public:
    Instrument(string n = "", int y = 0);
    Instrument(const Instrument &other);

    string getName() const;
    int getYearMade() const;
    void displayInfo() const;

    Instrument &operator=(const Instrument &other);
    bool operator==(const Instrument &other) const;
    bool operator!=(const Instrument &other) const;
    bool operator<(const Instrument &other) const;
    bool operator>(const Instrument &other) const;
    Instrument operator+(int years) const;
    Instrument operator-(int years) const;
    Instrument &operator+=(int years);
    Instrument &operator-=(int years);

    friend ostream &operator<<(ostream &out, const Instrument &instr);
    friend istream &operator>>(istream &in, Instrument &instr);
};

#endif // INSTRUMENT_H

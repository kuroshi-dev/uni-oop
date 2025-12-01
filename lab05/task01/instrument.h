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
    Instrument(Instrument &other);

    string getName();
    int getYearMade();
    void displayInfo();

    Instrument &operator=(Instrument &other);
    bool operator==(Instrument &other);
    bool operator!=(Instrument &other);
    bool operator<(Instrument &other);
    bool operator>(Instrument &other);
    Instrument operator+(int years);
    Instrument operator-(int years);
    Instrument &operator+=(int years);
    Instrument &operator-=(int years);

    friend ostream &operator<<(ostream &out, Instrument &instr);
    friend istream &operator>>(istream &in, Instrument &instr);
};

#endif // INSTRUMENT_H

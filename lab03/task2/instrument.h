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
    Instrument(string n, int y);

    string getName();
    int getYearMade();
    void displayInfo();
};

#endif // INSTRUMENT_H

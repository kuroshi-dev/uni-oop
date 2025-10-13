#include "instrument.h"

Instrument::Instrument(string n, int y) : name(n), yearMade(y) {}

string Instrument::getName(){
    return name;
}

int Instrument:: getYearMade(){
    return yearMade;
}

void Instrument::displayInfo(){
    cout << name << " (" << yearMade << " рiк\n";
}

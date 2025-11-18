#include "musician.h"

Musician::Musician(string n, string p, string instrName, int instrYear)
    : Manager(n, p), instrument(instrName, instrYear) {}

void Musician::displayInfo() {
    cout << "[Musician] " << name << endl;
    cout << "   Contact: " << phone << endl;
    cout << "   ";
    instrument.displayInfo();
}

string Musician::getInstrumentName() {
    return instrument.getName();
}

#include "musician.h"

Musician::Musician(string n, string p, string instrName, int instrYear)
    : Manager(n, p), instrument(instrName, instrYear){}

Musician::Musician(Musician &other) : Manager(other), instrument(other.instrument){}

void Musician::displayInfo(){
    cout << "[Musician] " << name << endl;
    cout << "   Contact: " << phone << endl;
    cout << "   ";
    instrument.displayInfo();
}

string Musician::getInstrumentName(){
    return instrument.getName();
}

Instrument &Musician::getInstrument(){
    return instrument;
}

Musician &Musician::operator=(Musician &other){
    if (this != &other){
        Manager::operator=(other);
        instrument = other.instrument;
    }
    return *this;
}

bool Musician::operator==(Musician &other){
    return Manager::operator==(other) && instrument == other.instrument;
}

bool Musician::operator!=(Musician &other){
    return !(*this == other);
}

bool Musician::operator<(Musician &other){
    return instrument < other.instrument;
}

bool Musician::operator>(Musician &other){
    return instrument > other.instrument;
}

ostream &operator<<(ostream &out, Musician &musician){
    out << "[Musician] " << musician.name << " | Phone: " << musician.phone << " | " << musician.instrument;
    return out;
}

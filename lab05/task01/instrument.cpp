#include "instrument.h"

Instrument::Instrument(string n, int y) : name(n), yearMade(y){}

Instrument::Instrument(Instrument &other) : name(other.name), yearMade(other.yearMade){}

string Instrument::getName(){
    return name;
}

int Instrument::getYearMade(){
    return yearMade;
}

void Instrument::displayInfo(){
    cout << "Instrument: " << name << " (" << yearMade << ")" << endl;
}

Instrument &Instrument::operator=(Instrument &other){
    if (this != &other){
        name = other.name;
        yearMade = other.yearMade;
    }
    return *this;
}

bool Instrument::operator==(Instrument &other){
    return (name == other.name && yearMade == other.yearMade);
}

bool Instrument::operator!=(Instrument &other){
    return !(*this == other);
}

bool Instrument::operator<(Instrument &other){
    return yearMade < other.yearMade;
}

bool Instrument::operator>(Instrument &other){
    return yearMade > other.yearMade;
}

Instrument Instrument::operator+(int years){
    return Instrument(name, yearMade + years);
}

Instrument Instrument::operator-(int years){
    int newYear = yearMade - years;
    if (newYear < 0)
        newYear = 0;
    return Instrument(name, newYear);
}

Instrument &Instrument::operator+=(int years){
    yearMade += years;
    return *this;
}

Instrument &Instrument::operator-=(int years){
    yearMade -= years;
    if (yearMade < 0)
        yearMade = 0;
    return *this;
}

ostream &operator<<(ostream &out, Instrument &instr){
    out << instr.name << " (" << instr.yearMade << ")";
    return out;
}

istream &operator>>(istream &in, Instrument &instr){
    cout << "Enter instrument name: ";
    getline(in, instr.name);
    cout << "Enter year made: ";
    in >> instr.yearMade;
    in.ignore();
    return in;
}

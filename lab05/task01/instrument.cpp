#include "instrument.h"

Instrument::Instrument(string n, int y) : name(n), yearMade(y) {}

Instrument::Instrument(const Instrument &other) : name(other.name), yearMade(other.yearMade) {}

string Instrument::getName() const
{
    return name;
}

int Instrument::getYearMade() const
{
    return yearMade;
}

void Instrument::displayInfo() const
{
    cout << "Instrument: " << name << " (" << yearMade << ")" << endl;
}

Instrument &Instrument::operator=(const Instrument &other)
{
    if (this != &other)
    {
        name = other.name;
        yearMade = other.yearMade;
    }
    return *this;
}

bool Instrument::operator==(const Instrument &other) const
{
    return (name == other.name && yearMade == other.yearMade);
}

bool Instrument::operator!=(const Instrument &other) const
{
    return !(*this == other);
}

bool Instrument::operator<(const Instrument &other) const
{
    return yearMade < other.yearMade;
}

bool Instrument::operator>(const Instrument &other) const
{
    return yearMade > other.yearMade;
}

Instrument Instrument::operator+(int years) const
{
    return Instrument(name, yearMade + years);
}

Instrument Instrument::operator-(int years) const
{
    int newYear = yearMade - years;
    if (newYear < 0)
        newYear = 0; // year cannot be negative
    return Instrument(name, newYear);
}

Instrument &Instrument::operator+=(int years)
{
    yearMade += years;
    return *this;
}

Instrument &Instrument::operator-=(int years)
{
    yearMade -= years;
    if (yearMade < 0)
        yearMade = 0;
    return *this;
}

ostream &operator<<(ostream &out, const Instrument &instr)
{
    out << instr.name << " (" << instr.yearMade << ")";
    return out;
}

istream &operator>>(istream &in, Instrument &instr)
{
    cout << "Enter instrument name: ";
    getline(in, instr.name);
    cout << "Enter year made: ";
    in >> instr.yearMade;
    in.ignore(); // Clear buffer
    return in;
}

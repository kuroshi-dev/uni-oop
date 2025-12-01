#include "musician.h"

Musician::Musician(string n, string p, string instrName, int instrYear)
    : Manager(n, p), instrument(instrName, instrYear) {}

Musician::Musician(const Musician &other) : Manager(other), instrument(other.instrument) {}

void Musician::displayInfo() const
{
    cout << "[Musician] " << name << endl;
    cout << "   Contact: " << phone << endl;
    cout << "   ";
    instrument.displayInfo();
}

string Musician::getInstrumentName() const
{
    return instrument.getName();
}

const Instrument &Musician::getInstrument() const
{
    return instrument;
}

Musician &Musician::operator=(const Musician &other)
{
    if (this != &other)
    {
        Manager::operator=(other);
        instrument = other.instrument;
    }
    return *this;
}

bool Musician::operator==(const Musician &other) const
{
    return Manager::operator==(other) && instrument == other.instrument;
}

bool Musician::operator!=(const Musician &other) const
{
    return !(*this == other);
}

bool Musician::operator<(const Musician &other) const
{
    return instrument < other.instrument;
}

bool Musician::operator>(const Musician &other) const
{
    return instrument > other.instrument;
}

ostream &operator<<(ostream &out, const Musician &musician)
{
    out << "[Musician] " << musician.name << " | Phone: " << musician.phone << " | " << musician.instrument;
    return out;
}

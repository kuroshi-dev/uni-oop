#include "leader.h"

Leader::Leader(string n, string p, string instrName, int instrYear, int exp)
    : Musician(n, p, instrName, instrYear), experience(exp) {}

Leader::Leader(const Leader &other) : Musician(other), experience(other.experience) {}

int Leader::getExperience() const { return experience; }

void Leader::displayInfo() const
{
    cout << "[BAND LEADER] " << name << endl;
    cout << "   Experience: " << experience << " years" << endl;
    cout << "   Contact: " << phone << endl;
    cout << "   ";
    instrument.displayInfo();
}

Leader &Leader::operator=(const Leader &other)
{
    if (this != &other)
    {
        Musician::operator=(other);
        experience = other.experience;
    }
    return *this;
}

bool Leader::operator==(const Leader &other) const
{
    return Musician::operator==(other) && experience == other.experience;
}

bool Leader::operator!=(const Leader &other) const
{
    return !(*this == other);
}

bool Leader::operator<(const Leader &other) const
{
    return experience < other.experience;
}

bool Leader::operator>(const Leader &other) const
{
    return experience > other.experience;
}

Leader Leader::operator+(int years) const
{
    Leader newLeader(*this);
    newLeader.experience += years;
    return newLeader;
}

Leader Leader::operator-(int years) const
{
    Leader newLeader(*this);
    newLeader.experience -= years;
    if (newLeader.experience < 0)
        newLeader.experience = 0;
    return newLeader;
}

Leader &Leader::operator+=(int years)
{
    experience += years;
    return *this;
}

Leader &Leader::operator-=(int years)
{
    experience -= years;
    if (experience < 0)
        experience = 0;
    return *this;
}

ostream &operator<<(ostream &out, const Leader &leader)
{
    out << "[BAND LEADER] " << leader.name << " | Phone: " << leader.phone
        << " | Experience: " << leader.experience << " years | " << leader.instrument;
    return out;
}

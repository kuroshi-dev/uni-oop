#include "leader.h"

Leader::Leader(string n, string p, string instrName, int instrYear, int exp)
    : Musician(n, p, instrName, instrYear), experience(exp){}

Leader::Leader(Leader &other) : Musician(other), experience(other.experience){}

int Leader::getExperience(){ return experience; }

void Leader::displayInfo(){
    cout << "[BAND LEADER] " << name << endl;
    cout << "   Experience: " << experience << " years" << endl;
    cout << "   Contact: " << phone << endl;
    cout << "   ";
    instrument.displayInfo();
}

Leader &Leader::operator=(Leader &other){
    if (this != &other){
        Musician::operator=(other);
        experience = other.experience;
    }
    return *this;
}

bool Leader::operator==(Leader &other){
    return Musician::operator==(other) && experience == other.experience;
}

bool Leader::operator!=(Leader &other){
    return !(*this == other);
}

bool Leader::operator<(Leader &other){
    return experience < other.experience;
}

bool Leader::operator>(Leader &other){
    return experience > other.experience;
}

Leader Leader::operator+(int years){
    Leader newLeader(*this);
    newLeader.experience += years;
    return newLeader;
}

Leader Leader::operator-(int years){
    Leader newLeader(*this);
    newLeader.experience -= years;
    if (newLeader.experience < 0)
        newLeader.experience = 0;
    return newLeader;
}

Leader &Leader::operator+=(int years){
    experience += years;
    return *this;
}

Leader &Leader::operator-=(int years){
    experience -= years;
    if (experience < 0)
        experience = 0;
    return *this;
}

ostream &operator<<(ostream &out, Leader &leader){
    out << "[BAND LEADER] " << leader.name << " | Phone: " << leader.phone
        << " | Experience: " << leader.experience << " years | " << leader.instrument;
    return out;
}

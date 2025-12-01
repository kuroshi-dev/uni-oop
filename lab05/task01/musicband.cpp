#include "musicband.h"

MusicBand::MusicBand(string n, string s) : name(n), style(s){}

MusicBand::MusicBand(MusicBand &other) : name(other.name), style(other.style){
    members = other.members;
}

MusicBand::~MusicBand(){
    members.clear();
}

void MusicBand::addMember(Musician *m){
    members.push_back(m);
    cout << ">> " << m->getName() << " added to the band." << endl;
}

void MusicBand::removeMember(int index){
    if (index >= 0 && index < members.size()){
        cout << ">> " << members[index]->getName() << " removed from the band." << endl;
        members.erase(members.begin() + index);
    }
    else{
        cout << "!! Invalid index." << endl;
    }
}

void MusicBand::showBand(){
    cout << "\n--- BAND: " << name << " (" << style << ") ---" << endl;
    cout << "Members (" << members.size() << "):" << endl;
    for (size_t i = 0; i < members.size(); i++){
        cout << i + 1 << ". ";
        members[i]->displayInfo();
        cout << "-------------------------" << endl;
    }
}

int MusicBand::getCount(){
    return members.size();
}

string &MusicBand::getName(){ return name; }
string &MusicBand::getStyle(){ return style; }
vector<Musician *> &MusicBand::getMembers(){ return members; }

MusicBand &MusicBand::operator=(MusicBand &other){
    if (this != &other){
        name = other.name;
        style = other.style;
        members = other.members;
    }
    return *this;
}

bool MusicBand::operator==(MusicBand &other){
    return name == other.name && style == other.style && members.size() == other.members.size();
}

bool MusicBand::operator!=(MusicBand &other){
    return !(*this == other);
}

MusicBand MusicBand::operator+(MusicBand &other){
    MusicBand result(name + " & " + other.name, style + "/" + other.style);
    result.members = members;
    result.members.insert(result.members.end(), other.members.begin(), other.members.end());
    return result;
}

MusicBand &MusicBand::operator+=(Musician *musician){
    addMember(musician);
    return *this;
}

MusicBand &MusicBand::operator-=(int index){
    removeMember(index);
    return *this;
}

Musician *MusicBand::operator[](int index){
    if (index >= 0 && index < members.size()){
        return members[index];
    }
    return nullptr;
}

ostream &operator<<(ostream &out, MusicBand &band){
    out << "BAND: " << band.name << " (" << band.style << ") - Members: " << band.members.size();
    return out;
}

#include "musicband.h"

MusicBand::MusicBand(string n, string s) : name(n), style(s) {}

MusicBand::~MusicBand() {
    members.clear();
}

void MusicBand::addMember(Musician* m) {
    members.push_back(m);
    cout << ">> " << m->getName() << " added to the band." << endl;
}

void MusicBand::removeMember(int index) {
    if (index >= 0 && index < members.size()) {
        cout << ">> " << members[index]->getName() << " removed from the band." << endl;
        members.erase(members.begin() + index);
    } else {
        cout << "!! Invalid index." << endl;
    }
}

void MusicBand::showBand() {
    cout << "\n--- BAND: " << name << " (" << style << ") ---" << endl;
    cout << "Members (" << members.size() << "):" << endl;
    for (size_t i = 0; i < members.size(); i++) {
        cout << i + 1 << ". ";
        members[i]->displayInfo();
        cout << "-------------------------" << endl;
    }
}

int MusicBand::getCount() {
    return members.size();
}

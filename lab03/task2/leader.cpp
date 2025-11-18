#include "leader.h"

Leader::Leader(string n, string p, string instrName, int instrYear, int exp)
    : Musician(n, p, instrName, instrYear), experience(exp) {}

int Leader::getExperience() { return experience; }

void Leader::displayInfo() {
    cout << "[BAND LEADER] " << name << endl;
    cout << "   Experience: " << experience << " years" << endl;
    cout << "   Contact: " << phone << endl;
    cout << "   ";
    instrument.displayInfo();
}

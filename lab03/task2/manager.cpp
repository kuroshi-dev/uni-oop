#include "manager.h"

Manager::Manager(string n, string p) : Person(n), phone(p) {}

string Manager::getPhone() { return phone; }

void Manager::displayInfo() {
    cout << "Manager: " << name << " | Phone: " << phone << endl;
}

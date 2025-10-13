#include "leader.h"

Leader::Leader(string n, int exp) : Person(n), experience(exp) {}

int Leader::getExperience(){ return experience; }

void Leader::displayInfo() {
    cout << "Керівник: " << name << " (досвід: " << experience << " років)\n";
}

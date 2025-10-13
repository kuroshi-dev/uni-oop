#include "musician.h"

Musician::Musician(string n, string instrName, int instrYear) : Person(n), instrument(instrName, instrYear), manager(nullptr) {}

void Musician::setManager(Manager* m){ this->manager = m; }

void Musician::removeManager(){ this->manager = nullptr; }

void Musician::displayInfo(){
    cout << "Музикант: " << name << endl;
    cout << "Iнструмент: ";
    instrument.displayInfo();
    if (manager != nullptr) {
        cout << "Менеджер: " << manager->getName() << endl;
    }
}

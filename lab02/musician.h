#ifndef MUSICIAN_H
#define MUSICIAN_H

#include "person.h"
#include "instrument.h"
#include "manager.h"

class Musician : public Person {
private:
    Instrument instrument; // comp
    Manager* manager; // assoc
public:
    Musician(string n, string instrName, int instrYear);

    void setManager(Manager* m);
    void removeManager();

    void displayInfo();
};

#endif // MUSICIAN_H

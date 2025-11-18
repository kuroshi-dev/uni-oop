#ifndef MUSICIAN_H
#define MUSICIAN_H

#include "person.h"
#include "instrument.h"
#include "manager.h"

class Musician : public Manager {
protected:
    Instrument instrument;
public:
    Musician(string n, string p, string instrName, int instrYear);

    void displayInfo() override;
    string getInstrumentName();
};

#endif // MUSICIAN_H

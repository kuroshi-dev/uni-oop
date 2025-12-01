#ifndef MUSICIAN_H
#define MUSICIAN_H

#include "person.h"
#include "instrument.h"
#include "manager.h"

class Musician : public Manager
{
protected:
    Instrument instrument;

public:
    Musician(string n = "", string p = "", string instrName = "", int instrYear = 0);
    Musician(Musician &other);

    void displayInfo() override;
    string getInstrumentName();
    Instrument &getInstrument();

    Musician &operator=(Musician &other);
    bool operator==(Musician &other);
    bool operator!=(Musician &other);
    bool operator<(Musician &other);
    bool operator>(Musician &other);

    friend ostream &operator<<(ostream &out, Musician &musician);
};

#endif // MUSICIAN_H

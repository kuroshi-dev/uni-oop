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
    Musician(const Musician &other);

    void displayInfo() const override;
    string getInstrumentName() const;
    const Instrument &getInstrument() const;

    Musician &operator=(const Musician &other);
    bool operator==(const Musician &other) const;
    bool operator!=(const Musician &other) const;
    bool operator<(const Musician &other) const;
    bool operator>(const Musician &other) const;

    friend ostream &operator<<(ostream &out, const Musician &musician);
};

#endif // MUSICIAN_H

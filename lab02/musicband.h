#ifndef MUSICBAND_H
#define MUSICBAND_H

#include "Leader.h"
#include "Musician.h"

using namespace std;

class MusicBand {
private:
    string name;
    string musicStyle;
    Leader leader;

    static const int MAX_MUSICIANS = 10;
    Musician* musicians[MAX_MUSICIANS];
    int musicianCount;

public:
    MusicBand(string n, string style, string leaderName, int leaderExp);
    ~MusicBand();

    void addMusician(Musician* m);
    void removeMusician(string musicianName);
    void displayInfo();
    int getMusicianCount();
};

#endif

#include "leader.h"
#include <vector>
#include <limits>
#include <cstdlib>
#include <windows.h>
#include <iostream>
#include <string>

class MusicBand
{
private:
    string name;
    string style;
    vector<Musician *> members;

public:
    MusicBand(string n = "", string s = "");
    MusicBand(MusicBand &other);
    ~MusicBand();

    void addMember(Musician *m);
    void removeMember(int index);
    void showBand();
    int getCount();
    string &getName();
    string &getStyle();
    vector<Musician *> &getMembers();

    MusicBand &operator=(MusicBand &other);
    bool operator==(MusicBand &other);
    bool operator!=(MusicBand &other);
    MusicBand operator+(MusicBand &other);
    MusicBand &operator+=(Musician *musician);
    MusicBand &operator-=(int index);
    Musician *operator[](int index);

    friend ostream &operator<<(ostream &out, MusicBand &band);
};

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
    MusicBand(const MusicBand &other);
    ~MusicBand();

    void addMember(Musician *m);
    void removeMember(int index);
    void showBand() const;
    int getCount() const;
    const string &getName() const;
    const string &getStyle() const;
    const vector<Musician *> &getMembers() const;

    MusicBand &operator=(const MusicBand &other);
    bool operator==(const MusicBand &other) const;
    bool operator!=(const MusicBand &other) const;
    MusicBand operator+(const MusicBand &other) const;
    MusicBand &operator+=(Musician *musician);
    MusicBand &operator-=(int index);
    Musician *operator[](int index) const;

    friend ostream &operator<<(ostream &out, const MusicBand &band);
};

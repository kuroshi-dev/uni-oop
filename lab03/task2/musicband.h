#include "leader.h"
#include <vector>
#include <limits>
#include <cstdlib>

class MusicBand {
private:
    string name;
    string style;
    vector<Musician*> members;

public:
    MusicBand(string n, string s);
    ~MusicBand();

    void addMember(Musician* m);
    void removeMember(int index);
    void showBand();
    int getCount();
};

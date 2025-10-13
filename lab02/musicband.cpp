#include "MusicBand.h"

MusicBand::MusicBand(string n, string style, string leaderName, int leaderExp) : name(n), musicStyle(style), leader(leaderName, leaderExp), musicianCount(0){
    for (int i = 0; i < MAX_MUSICIANS; i++) {
        musicians[i] = nullptr;
    }
}

MusicBand::~MusicBand(){
    cout << "\nГурт \"" << name << "\" розпущено" << endl;
}

void MusicBand::addMusician(Musician* m){
    if (musicianCount >= MAX_MUSICIANS){
        cout << "Гурт повний! Неможливо додати музиканта." << endl;
        return;
    }

    musicians[musicianCount] = m;
    musicianCount++;
    cout << "Музиканта " << m->getName() << " додано до гурту" << endl;
}

void MusicBand::removeMusician(string musicianName) {
    for (int i = 0; i < musicianCount; i++) {
        if (musicians[i]->getName() == musicianName) {
            cout << "Музиканта " << musicianName << " видалено з гурту" << endl;

            for (int j = i; j < musicianCount - 1; j++) {
                musicians[j] = musicians[j + 1];
            }

            musicians[musicianCount - 1] = nullptr;
            musicianCount--;
            return;
        }
    }
    cout << "Музиканта " << musicianName << " не знайдено" << endl;
}

void MusicBand::displayInfo(){
    cout << "\n========================================" << endl;
    cout << "Гурт: " << name << endl;
    cout << "Стиль: " << musicStyle << endl;
    leader.displayInfo();
    cout << "Склад гурту (" << musicianCount << " музикантів):" << endl;
    for (int i = 0; i < musicianCount; i++) {
        musicians[i]->displayInfo();
    }
    cout << "========================================" << endl;
}

int MusicBand::getMusicianCount(){
    return musicianCount;
}

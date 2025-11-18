#include <iostream>

#include "musicband.h"
#include "leader.h"

using namespace std;

string inputString(const string& msg) {
    string s;
    cout << msg;
    getline(cin, s);
    return s;
}

int inputInt(const string& msg) {
    int n;
    cout << msg;
    while (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return n;
}

int main() {
    cout << "--- LAB WORK #3 (Task 2) ---" << endl;

    string bandName = inputString("Enter Band Name: ");
    string bandStyle = inputString("Enter Music Style: ");
    MusicBand band(bandName, bandStyle);

    vector<Musician*> createdMusicians;

    int choice;
    do {
        cout << "\n----------- MENU -----------" << endl;
        cout << "1. Add Musician" << endl;
        cout << "2. Add Leader" << endl;
        cout << "3. Show Band Info" << endl;
        cout << "4. Remove Member" << endl;
        cout << "0. Exit" << endl;
        cout << "------------------------------" << endl;
        choice = inputInt("Your choice: ");

        if (choice == 1 || choice == 2) {
            string name = inputString("Name: ");
            string phone = inputString("Phone: ");
            string instr = inputString("Instrument: ");
            int year = inputInt("Instrument Year: ");

            Musician* newMember = nullptr;

            if (choice == 1) {
                newMember = new Musician(name, phone, instr, year);
            } else {
                int exp = inputInt("Experience (years): ");
                newMember = new Leader(name, phone, instr, year, exp);
            }

            createdMusicians.push_back(newMember);
            band.addMember(newMember);
        }
        else if (choice == 3) {
            system("cls");
            band.showBand();
        }
        else if (choice == 4) {
            band.showBand();
            if (band.getCount() > 0) {
                int idx = inputInt("Enter member number to remove: ");
                band.removeMember(idx - 1);
            } else {
                cout << "Band is empty." << endl;
            }
        }

    } while (choice != 0);


    cout << "Cleaning up resources..." << endl;
    for (Musician* p : createdMusicians) {
        delete p;
    }
    createdMusicians.clear();

    return 0;
}

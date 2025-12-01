#include "musicband.h"
#include "leader.h"

using namespace std;

void demonstrateOperators();

void demonstrateOperators(){
    cout << "\n=== DEMONSTRATION OF OVERLOADED OPERATORS ===" << endl;

    cout << "\n--- Operators for Instrument ---" << endl;
    Instrument guitar1("Guitar", 2020);
    Instrument guitar2("Guitar", 2020);
    Instrument piano("Piano", 2018);

    cout << "Guitar 1: " << guitar1 << endl;
    cout << "Guitar 2: " << guitar2 << endl;
    cout << "Piano: " << piano << endl;

    cout << "Guitar1 == Guitar2: " << (guitar1 == guitar2) << endl;
    cout << "Guitar1 == Piano: " << (guitar1 == piano) << endl;
    cout << "Guitar1 > Piano (by year): " << (guitar1 > piano) << endl;

    Instrument newGuitar = guitar1 + 5;
    cout << "Guitar1 + 5 years: " << newGuitar << endl;

    guitar1 += 2;
    cout << "Guitar1 after += 2: " << guitar1 << endl;

    cout << "\n--- Operators for Musician ---" << endl;
    Musician musician1("John", "+380-12-345-67-89", "Guitar", 2020);
    Musician musician2("Anna", "+380-98-765-43-21", "Piano", 2018);
    Musician musician3("John", "+380-12-345-67-89", "Guitar", 2020);

    cout << "Musician 1: " << musician1 << endl;
    cout << "Musician 2: " << musician2 << endl;
    cout << "Musician 3: " << musician3 << endl;

    cout << "Musician1 == Musician3: " << (musician1 == musician3) << endl;
    cout << "Musician1 == Musician2: " << (musician1 == musician2) << endl;
    cout << "Musician1 > Musician2 (by instrument year): " << (musician1 > musician2) << endl;

    cout << "\n--- Operators for Leader ---" << endl;
    Leader leader1("Mike", "+380-55-123-45-67", "Drums", 2015, 8);
    Leader leader2("Sarah", "+380-44-987-65-43", "Bass", 2019, 5);

    cout << "Leader 1: " << leader1 << endl;
    cout << "Leader 2: " << leader2 << endl;

    cout << "Leader1 > Leader2 (by experience): " << (leader1 > leader2) << endl;

    Leader experiencedLeader = leader2 + 3;
    cout << "Leader2 + 3 years experience: " << experiencedLeader << endl;

    leader1 -= 2;
    cout << "Leader1 after -= 2 years: " << leader1 << endl;

    cout << "\n--- Operators for MusicBand ---" << endl;
    MusicBand band1("Rock Stars", "Rock");
    MusicBand band2("Jazz Masters", "Jazz");

    Musician *m1 = new Musician(musician1);
    Musician *m2 = new Musician(musician2);
    Leader *l1 = new Leader(leader1);

    band1 += m1;
    band1 += l1;
    band2 += m2;

    cout << "Band 1: " << band1 << endl;
    cout << "Band 2: " << band2 << endl;

    cout << "Band1 == Band2: " << (band1 == band2) << endl;

    if (band1[0])
    {
        cout << "First member of Band1: " << *(band1[0]) << endl;
    }

    MusicBand superBand = band1 + band2;
    cout << "Combined band: " << superBand << endl;

    delete m1;
    delete m2;
    delete l1;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "--- LAB WORK #5 (Task 1) ---" << endl;

    vector<MusicBand *> bands;
    vector<Musician *> createdMusicians;
    int currentBand = -1;

    int choice;
    do{
        cout << "\n----------- MAIN MENU -----------" << endl;
        cout << "1. Create New Band" << endl;
        cout << "2. Select Band" << endl;
        cout << "3. Show All Bands" << endl;
        if (currentBand >= 0 && currentBand < bands.size()){
            cout << "\n--- BAND MANAGEMENT (Current: " << bands[currentBand]->getName() << ") ---" << endl;
            cout << "4. Add Musician" << endl;
            cout << "5. Add Leader" << endl;
            cout << "6. Show Band Info" << endl;
            cout << "7. Remove Member" << endl;
        }
        cout << "8. Demo Overloaded Operators" << endl;
        cout << "0. Exit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Your choice: ";
        while (!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1){
            string bandName, bandStyle;
            cout << "Enter Band Name: ";
            getline(cin, bandName);
            cout << "Enter Music Style: ";
            getline(cin, bandStyle);
            bands.push_back(new MusicBand(bandName, bandStyle));
            cout << "Band '" << bandName << "' created successfully!" << endl;
            if (currentBand == -1)
                currentBand = 0;
        }
        else if (choice == 2){
            if (bands.empty()){
                cout << "No bands available. Create a band first." << endl;
                continue;
            }
            cout << "\n--- SELECT BAND ---" << endl;
            for (size_t i = 0; i < bands.size(); i++)
            {
                cout << i + 1 << ". " << bands[i]->getName() << " (" << bands[i]->getStyle() << ")" << endl;
            }
            int bandChoice;
            cout << "Select band (1-" << bands.size() << "): ";
            while (!(cin >> bandChoice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (bandChoice >= 1 && bandChoice <= bands.size())
            {
                currentBand = bandChoice - 1;
                cout << "Selected band: " << bands[currentBand]->getName() << endl;
            }
            else
            {
                cout << "Invalid band selection." << endl;
            }
        }
        else if (choice == 3)
        {
            if (bands.empty())
            {
                cout << "No bands created yet." << endl;
            }
            else
            {
                cout << "\n--- ALL BANDS ---" << endl;
                for (size_t i = 0; i < bands.size(); i++)
                {
                    cout << i + 1 << ". ";
                    bands[i]->showBand();
                    cout << endl;
                }
            }
        }
        else if ((choice == 4 || choice == 5) && currentBand >= 0 && currentBand < bands.size())
        {
            string name, phone, instr;
            int year;

            cout << "Name: ";
            getline(cin, name);
            cout << "Phone: ";
            getline(cin, phone);
            cout << "Instrument: ";
            getline(cin, instr);
            cout << "Instrument Year: ";
            while (!(cin >> year))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Musician *newMember = nullptr;

            if (choice == 4)
            {
                newMember = new Musician(name, phone, instr, year);
            }
            else
            {
                int exp;
                cout << "Experience (years): ";
                while (!(cin >> exp))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                newMember = new Leader(name, phone, instr, year, exp);
            }

            createdMusicians.push_back(newMember);
            bands[currentBand]->addMember(newMember);
        }
        else if (choice == 6 && currentBand >= 0 && currentBand < bands.size())
        {
            system("cls");
            bands[currentBand]->showBand();
        }
        else if (choice == 7 && currentBand >= 0 && currentBand < bands.size())
        {
            bands[currentBand]->showBand();
            if (bands[currentBand]->getCount() > 0)
            {
                int idx;
                cout << "Enter member number to remove: ";
                while (!(cin >> idx))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                bands[currentBand]->removeMember(idx - 1);
            }
            else
            {
                cout << "Band is empty." << endl;
            }
        }
        else if (choice == 8)
        {
            system("cls");
            demonstrateOperators();
        }
        else if (choice >= 4 && choice <= 7 && (currentBand < 0 || currentBand >= bands.size()))
        {
            cout << "Please select a band first." << endl;
        }

    } while (choice != 0);

    cout << "Cleaning up resources..." << endl;
    for (Musician *p : createdMusicians)
    {
        delete p;
    }
    createdMusicians.clear();

    for (MusicBand *band : bands)
    {
        delete band;
    }
    bands.clear();

    return 0;
}

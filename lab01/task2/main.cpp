#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct Employee {
    short id;
    string name;
    int salary;

    Employee() {
        id = 0;
        name = "User";
        salary = 1000;
    }

    short getId(){ return id; }
    void setId(short newId){ id = newId; }

    string getName(){ return name; }
    void setName(string newName){ name = newName; }

    int getSalary(){ return salary; }
    void setSalary(int newSalary){ salary = newSalary; }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Employee user1;

    cout << "User 1: Default\n"
         << "Id: " << user1.getId() << endl
         << "Name: " << user1.getName() << endl
         << "Salary: " << user1.getSalary() << endl;

    short newId;
    string newName;
    int newSalary;

    cout << "\nSet new Id: ";
    cin >> newId;
    user1.setId(newId);

    cout << "Set new Name: ";
    cin >> newName;
    user1.setName(newName);

    cout << "Set new Salary: ";
    cin >> newSalary;
    user1.setSalary(newSalary);

    cout << "\nUpdated User 1:\n"
         << "Id: " << user1.getId() << endl
         << "Name: " << user1.getName() << endl
         << "Salary: " << user1.getSalary() << endl;

    return 0;
}

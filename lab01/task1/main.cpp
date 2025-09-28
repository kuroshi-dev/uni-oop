#include "Employee.h"

using namespace std;

void showEmployee(Employee& emp){
    cout << "Lab01 Buliukin Volodymyr\n\n"
         << "Id: " << emp.getId() << "\n"
         << "Name: " << emp.getName() << "\n"
         << "Salary: " << emp.getSalary() << "\n";
}

void editEmployee(Employee& emp){
    short id;
    string name;
    int salary;

    cout << "\nSet new Id: ";
    cin >> id;
    emp.setId(id);

    cout << "Set new Name: ";
    cin >> name;
    emp.setName(name);

    cout << "Set new Salary: ";
    cin >> salary;
    emp.setSalary(salary);

    cout << "\nUpdated User Info:\n"
         << "Id: " << emp.getId() << endl
         << "Name: " << emp.getName() << endl
         << "Salary: " << emp.getSalary() << endl;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Employee user1, user2(2, "Employee", 9999);

    showEmployee(user1);
    editEmployee(user1);

    showEmployee(user2);

    return 0;
}


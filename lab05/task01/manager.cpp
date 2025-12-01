#include "manager.h"

Manager::Manager(string n, string p) : Person(n), phone(p){}

Manager::Manager(Manager &other) : Person(other), phone(other.phone){}

string Manager::getPhone(){ return phone; }

void Manager::displayInfo(){
    cout << "Manager: " << name << " | Phone: " << phone << endl;
}

Manager &Manager::operator=(Manager &other){
    if (this != &other){
        Person::operator=(other);
        phone = other.phone;
    }
    return *this;
}

bool Manager::operator==(Manager &other){
    return Person::operator==(other) && phone == other.phone;
}

bool Manager::operator!=(Manager &other){
    return !(*this == other);
}

ostream &operator<<(ostream &out, Manager &manager){
    out << "Manager: " << manager.name << " | Phone: " << manager.phone;
    return out;
}

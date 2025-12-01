#include "person.h"

Person::Person(string n) : name(n){}

Person::Person(Person &other) : name(other.name){}

string Person::getName(){ return name; }

Person &Person::operator=(Person &other){
    if (this != &other){
        name = other.name;
    }
    return *this;
}

bool Person::operator==(Person &other){
    return name == other.name;
}

bool Person::operator!=(Person &other){
    return !(*this == other);
}

bool Person::operator<(Person &other){
    return name < other.name;
}

bool Person::operator>(Person &other){
    return name > other.name;
}

ostream &operator<<(ostream &out, Person &person){
    out << "Person: " << person.name;
    return out;
}

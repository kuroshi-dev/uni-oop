#include "manager.h"

Manager::Manager(string n, string p) : Person(n), phone(p) {}

// Copy constructor
Manager::Manager(const Manager &other) : Person(other), phone(other.phone) {}

string Manager::getPhone() const { return phone; }

void Manager::displayInfo() const
{
    cout << "Manager: " << name << " | Phone: " << phone << endl;
}

Manager &Manager::operator=(const Manager &other)
{
    if (this != &other)
    {
        Person::operator=(other);
        phone = other.phone;
    }
    return *this;
}

bool Manager::operator==(const Manager &other) const
{
    return Person::operator==(other) && phone == other.phone;
}

bool Manager::operator!=(const Manager &other) const
{
    return !(*this == other);
}

ostream &operator<<(ostream &out, const Manager &manager)
{
    out << "Manager: " << manager.name << " | Phone: " << manager.phone;
    return out;
}

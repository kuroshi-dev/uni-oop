#ifndef AUTOPART_H
#define AUTOPART_H

#include <string>

using namespace std;

class AutoPart {
private:
    string name;
    string manufacturer;
    double price;
    int quantity;

public:
    AutoPart(string n, string m, double p, int q);

    string getName() const;
    string getManufacturer() const;
    double getPrice() const;
    int getQuantity() const;

    void setName(string n);
    void setManufacturer(string m);
    void setPrice(double p);
    void setQuantity(int q);
};

#endif // AUTOPART_H

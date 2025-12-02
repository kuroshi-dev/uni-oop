#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product {
private:
    string name;
    double price;
    int quantity;

public:
    Product(string n, double p, int q);

    string getName();
    double getPrice();
    int getQuantity();

    void setName(string n);
    void setPrice(double p);
    void setQuantity(int q);
};

#endif // PRODUCT_H

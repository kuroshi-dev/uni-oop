#include "autopart.h"

using namespace std;

AutoPart::AutoPart(string& n, string& m, double p, int q)
    : name(n), manufacturer(m), price(p), quantity(q) {}

string AutoPart::getName(){
    return name;
}

string AutoPart::getManufacturer(){
    return manufacturer;
}

double AutoPart::getPrice(){
    return price;
}

int AutoPart::getQuantity(){
    return quantity;
}

void AutoPart::setName(string& n){
    name = n;
}

void AutoPart::setManufacturer(string& m){
    manufacturer = m;
}

void AutoPart::setPrice(double p){
    price = p;
}

void AutoPart::setQuantity(int q){
    quantity = q;
}

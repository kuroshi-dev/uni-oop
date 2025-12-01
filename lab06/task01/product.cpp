#include "Product.h"

using namespace std;

Product::Product(string& n, double p, int q)
    : name(n), price(p), quantity(q){}

string Product::getName(){
    return name;
}

double Product::getPrice(){
    return price;
}

int Product::getQuantity(){
    return quantity;
}

void Product::setName(string& n){
    name = n;
}

void Product::setPrice(double p){
    price = p;
}

void Product::setQuantity(int q){
    quantity = q;
}

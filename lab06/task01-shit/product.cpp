#include "Product.h"

Product::Product(const std::string& n, double p, int q)
    : name(n), price(p), quantity(q) {}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::setName(const std::string& n) {
    name = n;
}

void Product::setPrice(double p) {
    price = p;
}

void Product::setQuantity(int q) {
    quantity = q;
}

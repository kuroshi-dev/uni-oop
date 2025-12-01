#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string name;
    double price;
    int quantity;

public:
    Product(const std::string& n, double p, int q);

    // Методи доступу
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;

    void setName(const std::string& n);
    void setPrice(double p);
    void setQuantity(int q);
};

#endif // PRODUCT_H

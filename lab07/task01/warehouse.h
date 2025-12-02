#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template <typename T>
class Warehouse {
private:
    vector<T> parts;

public:
    void addPart(T part);

    bool removePart(string name);

    bool updatePart(string name, double newPrice, int newQuantity);

    vector<T> getAllParts();

    vector<T> findByManufacturer(string manufacturer);

    void sortByName();

    void sortByPrice();

    void clear();

    size_t size();
};

template <typename T>
void Warehouse<T>::addPart(T part){
    parts.push_back(part);
}

template <typename T>
bool Warehouse<T>::removePart(string name){
    auto it = find_if(parts.begin(), parts.end(),
                           [&name](T& part) {
                               return part.getName() == name;
                           });

    if (it != parts.end()) {
        parts.erase(it);
        return true;
    }
    return false;
}

template <typename T>
bool Warehouse<T>::updatePart(string name, double newPrice, int newQuantity){
    auto it = find_if(parts.begin(), parts.end(),
                           [&name](T& part) {
                               return part.getName() == name;
                           });

    if (it != parts.end()) {
        it->setPrice(newPrice);
        it->setQuantity(newQuantity);
        return true;
    }
    return false;
}

template <typename T>
vector<T> Warehouse<T>::getAllParts() {
    return parts;
}

template <typename T>
vector<T> Warehouse<T>::findByManufacturer(string manufacturer) {
    vector<T> result;
    for (auto& part : parts) {
        if (part.getManufacturer() == manufacturer) {
            result.push_back(part);
        }
    }
    return result;
}

template <typename T>
void Warehouse<T>::sortByName() {
    sort(parts.begin(), parts.end(),
              [](T& a, T& b) {
                  return a.getName() < b.getName();
              });
}

template <typename T>
void Warehouse<T>::sortByPrice() {
    sort(parts.begin(), parts.end(),
              [](T& a, T& b) {
                  return a.getPrice() < b.getPrice();
              });
}

template <typename T>
void Warehouse<T>::clear() {
    parts.clear();
}

template <typename T>
size_t Warehouse<T>::size() {
    return parts.size();
}

#endif // WAREHOUSE_H

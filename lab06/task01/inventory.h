#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <algorithm>
#include <string>

template <typename T>
class Inventory {
private:
    std::vector<T> items;

public:

    void addItem(const T& item);

    bool removeItem(const std::string& name);

    std::vector<T> getAllItems() const;

    std::vector<T> findByPrice(double price) const;

    void clear();

    size_t size() const;
};

template <typename T>
void Inventory<T>::addItem(const T& item) {
    items.push_back(item);
}

template <typename T>
bool Inventory<T>::removeItem(const std::string& name) {
    auto it = std::find_if(items.begin(), items.end(),
                           [&name](const T& item) {
                               return item.getName() == name;
                           });

    if (it != items.end()) {
        items.erase(it);
        return true;
    }
    return false;
}

template <typename T>
std::vector<T> Inventory<T>::getAllItems() const {
    return items;
}

template <typename T>
std::vector<T> Inventory<T>::findByPrice(double price) const {
    std::vector<T> result;
    for (const auto& item : items) {
        if (item.getPrice() == price) {
            result.push_back(item);
        }
    }
    return result;
}

template <typename T>
void Inventory<T>::clear() {
    items.clear();
}

template <typename T>
size_t Inventory<T>::size() const {
    return items.size();
}

#endif // INVENTORY_H

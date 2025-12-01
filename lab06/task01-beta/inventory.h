#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <algorithm>
#include <string>

// Шаблонний клас Inventory - інвентар магазину
template <typename T>
class Inventory {
private:
    std::vector<T> items;

public:
    // Додавання товару
    void addItem(const T& item);

    // Видалення товару за назвою
    bool removeItem(const std::string& name);

    // Отримання всіх товарів
    std::vector<T> getAllItems() const;

    // Пошук товарів за ціною
    std::vector<T> findByPrice(double price) const;

    // Очистити інвентар
    void clear();

    // Кількість товарів
    size_t size() const;
};

// Реалізація шаблонних методів (має бути в .h файлі)
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

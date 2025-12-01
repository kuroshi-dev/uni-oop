#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template <typename T>
class Inventory {
private:
    vector<T> items;

public:

    void addItem(T& item);

    bool removeItem(string& name);

    vector<T> getAllItems();

    vector<T> findByPrice(double price);

    void clear();

    size_t size();
};

template <typename T>
void Inventory<T>::addItem(T& item){
    items.push_back(item);
}

template <typename T>
bool Inventory<T>::removeItem(string& name){
    auto it = find_if(items.begin(), items.end(),
                           [&name](T& item){
                               return item.getName() == name;
                           });

    if (it != items.end()){
        items.erase(it);
        return true;
    }
    return false;
}

template <typename T>
vector<T> Inventory<T>::getAllItems(){
    return items;
}

template <typename T>
vector<T> Inventory<T>::findByPrice(double price){
    vector<T> result;
    for (auto& item : items){
        if (item.getPrice() == price){
            result.push_back(item);
        }
    }
    return result;
}

template <typename T>
void Inventory<T>::clear(){
    items.clear();
}

template <typename T>
size_t Inventory<T>::size(){
    return items.size();
}

#endif // INVENTORY_H

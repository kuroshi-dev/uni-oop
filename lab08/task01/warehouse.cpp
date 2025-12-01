#include "warehouse.h"
#include <ctime>

string Warehouse::getCurrentTimestamp(){
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
       << setw(2) << (1 + ltm->tm_mon) << "/"
       << (1900 + ltm->tm_year) << " "
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min;

    return ss.str();
}

// ========== MAP OPERATIONS ==========
void Warehouse::addPart(AutoPart part){
    string key = part.getName() + "_" + part.getManufacturer();
    partsMap[key] = part;

    addToMultimap(part);

    uniqueNames.insert(part.getName());

    addToHistory("ADD", part);

    updateLowStockQueue();
}

bool Warehouse::removePart(string name){
    auto it = partsMap.find(name);
    if (it != partsMap.end()){
        AutoPart part = it->second;
        partsMap.erase(it);

        auto range = partsByName.equal_range(part.getName());
        for (auto i = range.first; i != range.second; ){
            if (i->second == part){
                i = partsByName.erase(i);
            } else {
                ++i;
            }
        }

        if (partsByName.count(part.getName()) == 0){
            uniqueNames.erase(part.getName());
        }

        addToHistory("DELETE", part);

        updateLowStockQueue();

        return true;
    }
    return false;
}

bool Warehouse::updatePart(string name, double newPrice, int newQuantity){
    auto it = partsMap.find(name);
    if (it != partsMap.end()){
        AutoPart oldPart = it->second;
        it->second.setPrice(newPrice);
        it->second.setQuantity(newQuantity);

        auto range = partsByName.equal_range(oldPart.getName());
        for (auto i = range.first; i != range.second; ++i){
            if (i->second == oldPart){
                AutoPart updated = i->second;
                updated.setPrice(newPrice);
                updated.setQuantity(newQuantity);
                partsByName.erase(i);
                partsByName.insert({updated.getName(), updated});
                break;
            }
        }

        addToHistory("UPDATE", it->second);

        updateLowStockQueue();

        return true;
    }
    return false;
}

AutoPart* Warehouse::findPart(string name){
    auto it = partsMap.find(name);
    if (it != partsMap.end()){
        return &(it->second);
    }
    return nullptr;
}

// ========== MULTIMAP OPERATIONS ==========
void Warehouse::addToMultimap(AutoPart part){
    partsByName.insert({part.getName(), part});
}

vector<AutoPart> Warehouse::findAllByName(string name){
    vector<AutoPart> result;
    auto range = partsByName.equal_range(name);
    for (auto it = range.first; it != range.second; ++it){
        result.push_back(it->second);
    }
    return result;
}

vector<AutoPart> Warehouse::findByManufacturer(string manufacturer){
    vector<AutoPart> result;
    for (const auto& pair : partsMap){
        if (pair.second.getManufacturer() == manufacturer){
            result.push_back(pair.second);
        }
    }
    return result;
}

// ========== SET OPERATIONS ==========
set<string> Warehouse::getUniqueNames(){
    return uniqueNames;
}

int Warehouse::getUniqueNamesCount(){
    return uniqueNames.size();
}

// ========== QUEUE OPERATIONS ==========
void Warehouse::addSupplyOrder(AutoPart part, bool isUrgent){
    SupplyOrder order(part, getCurrentTimestamp(), isUrgent);
    supplyQueue.push(order);
}

bool Warehouse::processNextSupply(){
    if (supplyQueue.empty()){
        return false;
    }

    SupplyOrder order = supplyQueue.front();
    supplyQueue.pop();

    string key = order.part.getName() + "_" + order.part.getManufacturer();
    auto it = partsMap.find(key);

    if (it != partsMap.end()){
        int newQuantity = it->second.getQuantity() + order.part.getQuantity();
        it->second.setQuantity(newQuantity);
        addToHistory("SUPPLY", it->second);
    } else {
        addPart(order.part);
    }

    updateLowStockQueue();
    return true;
}

int Warehouse::getSupplyQueueSize(){
    return supplyQueue.size();
}

vector<SupplyOrder> Warehouse::getAllSupplyOrders(){
    vector<SupplyOrder> result;
    queue<SupplyOrder> temp = supplyQueue;

    while (!temp.empty()){
        result.push_back(temp.front());
        temp.pop();
    }

    return result;
}

// ========== PRIORITY_QUEUE OPERATIONS ==========
void Warehouse::updateLowStockQueue(){
    while (!lowStockQueue.empty()){
        lowStockQueue.pop();
    }

    for (const auto& pair : partsMap){
        lowStockQueue.push(pair.second);
    }
}

vector<AutoPart> Warehouse::getLowStockParts(int count){
    vector<AutoPart> result;
    priority_queue<AutoPart, vector<AutoPart>, LowStockComparator> temp = lowStockQueue;

    while (!temp.empty() && count > 0){
        result.push_back(temp.top());
        temp.pop();
        count--;
    }

    return result;
}

// ========== STACK OPERATIONS ==========
void Warehouse::addToHistory(string action, AutoPart part){
    HistoryEntry entry(action, part, getCurrentTimestamp());
    history.push(entry);
}

vector<HistoryEntry> Warehouse::getHistory(int count){
    vector<HistoryEntry> result;
    stack<HistoryEntry> temp = history;

    while (!temp.empty() && count > 0){
        result.push_back(temp.top());
        temp.pop();
        count--;
    }

    return result;
}

HistoryEntry Warehouse::getLastHistoryEntry(){
    if (!history.empty()){
        return history.top();
    }
    return HistoryEntry("NONE", AutoPart(), "");
}

bool Warehouse::hasHistory(){
    return !history.empty();
}

// ========== GENERAL OPERATIONS ==========
vector<AutoPart> Warehouse::getAllParts(){
    vector<AutoPart> result;
    for (const auto& pair : partsMap){
        result.push_back(pair.second);
    }
    return result;
}

void Warehouse::sortByName(vector<AutoPart>& parts){
    sort(parts.begin(), parts.end(),
         [](AutoPart& a, AutoPart& b){
             return a.getName() < b.getName();
         });
}

void Warehouse::sortByPrice(vector<AutoPart>& parts){
    sort(parts.begin(), parts.end(),
         [](AutoPart& a, AutoPart& b){
             return a.getPrice() < b.getPrice();
         });
}

void Warehouse::clear(){
    partsMap.clear();
    partsByName.clear();
    uniqueNames.clear();
    while (!supplyQueue.empty()) supplyQueue.pop();
    while (!lowStockQueue.empty()) lowStockQueue.pop();
    while (!history.empty()) history.pop();
}

size_t Warehouse::size(){
    return partsMap.size();
}

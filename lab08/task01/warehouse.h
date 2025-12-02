#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "autopart.h"
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

class Warehouse {
private:
    map<string, AutoPart> partsMap;

    multimap<string, AutoPart> partsByName;

    set<string> uniqueNames;

    priority_queue<SupplyOrder, vector<SupplyOrder>, SupplyOrderComparator> supplyQueue;

    priority_queue<AutoPart, vector<AutoPart>, LowStockComparator> lowStockQueue;

    stack<HistoryEntry> history;

    string getCurrentTimestamp();

public:
    void addPart(AutoPart part);
    bool removePart(string name);
    bool updatePart(string name, double newPrice, int newQuantity);
    AutoPart* findPart(string name);

    void addToMultimap(AutoPart part);
    vector<AutoPart> findAllByName(string name);
    vector<AutoPart> findByManufacturer(string manufacturer);

    set<string> getUniqueNames();
    int getUniqueNamesCount();

    void addSupplyOrder(AutoPart part, bool isUrgent = false);
    bool processNextSupply();
    int getSupplyQueueSize();
    vector<SupplyOrder> getAllSupplyOrders();

    void updateLowStockQueue();
    vector<AutoPart> getLowStockParts(int count = 5);

    void addToHistory(string action, AutoPart part);
    vector<HistoryEntry> getHistory(int count = 10);
    HistoryEntry getLastHistoryEntry();
    bool hasHistory();

    vector<AutoPart> getAllParts();
    void sortByName(vector<AutoPart>& parts);
    void sortByPrice(vector<AutoPart>& parts);
    void clear();
    size_t size();
};

#endif // WAREHOUSE_H

#ifndef AUTOPART_H
#define AUTOPART_H

#include <string>
#include <ctime>

using namespace std;

class AutoPart {
private:
    string name;
    string manufacturer;
    double price;
    int quantity;

public:
    AutoPart(string n, string m, double p, int q);
    AutoPart() : name(""), manufacturer(""), price(0), quantity(0){}

    string getName() const;
    string getManufacturer() const;
    double getPrice() const;
    int getQuantity() const;

    void setName(string n);
    void setManufacturer(string m);
    void setPrice(double p);
    void setQuantity(int q);

    bool operator<(AutoPart& other){
        if (name != other.name) return name < other.name;
        return manufacturer < other.manufacturer;
    }

    bool operator==(AutoPart& other){
        return name == other.name && manufacturer == other.manufacturer;
    }
};

struct HistoryEntry{
    string action;
    AutoPart part;
    string timestamp;

    HistoryEntry(string act, AutoPart p, string ts)
        : action(act), part(p), timestamp(ts){}
};

struct SupplyOrder{
    AutoPart part;
    string orderDate;
    bool isUrgent;

    SupplyOrder(AutoPart p, string date, bool urgent = false)
        : part(p), orderDate(date), isUrgent(urgent){}
};

struct LowStockComparator{
    bool operator()(AutoPart& a, AutoPart& b){
        return a.getQuantity() > b.getQuantity();
    }
};

struct SupplyOrderComparator{
    bool operator()(const SupplyOrder& a, const SupplyOrder& b){

        if (a.isUrgent != b.isUrgent){
            return !a.isUrgent; // urgent has more priority
        }
        return false;
    }
};

#endif // AUTOPART_H

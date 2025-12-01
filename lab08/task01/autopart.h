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

    // Оператор порівняння для set
    bool operator<(AutoPart& other){
        if (name != other.name) return name < other.name;
        return manufacturer < other.manufacturer;
    }

    // Оператор рівності
    bool operator==(AutoPart& other){
        return name == other.name && manufacturer == other.manufacturer;
    }
};

// Структура для зберігання історії змін
struct HistoryEntry{
    string action;
    AutoPart part;
    string timestamp;

    HistoryEntry(string act, AutoPart p, string ts)
        : action(act), part(p), timestamp(ts){}
};

// Структура для черги постачання
struct SupplyOrder{
    AutoPart part;
    string orderDate;
    bool isUrgent;

    SupplyOrder(AutoPart p, string date, bool urgent = false)
        : part(p), orderDate(date), isUrgent(urgent){}
};

// Компаратор для priority_queue (найменша кількість = найвищий пріоритет)
struct LowStockComparator{
    bool operator()(AutoPart& a, AutoPart& b){
        return a.getQuantity() > b.getQuantity();
    }
};

#endif // AUTOPART_H

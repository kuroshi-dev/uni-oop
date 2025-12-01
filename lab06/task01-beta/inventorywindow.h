#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QTableWidget>
#include <vector>
#include "Product.h"
#include "Inventory.h"

class InventoryWindow : public QMainWindow {
    Q_OBJECT

private:
    Inventory<Product> inventory;

    QLineEdit* nameEdit;
    QDoubleSpinBox* priceSpinBox;
    QSpinBox* quantitySpinBox;
    QDoubleSpinBox* searchPriceSpinBox;
    QTableWidget* tableWidget;

public:
    InventoryWindow(QWidget* parent = nullptr);

private slots:
    void addProduct();
    void showAllProducts();
    void searchByPrice();
    void removeProduct(const std::string& name);

private:
    void displayProducts(const std::vector<Product>& products);
    void addSampleProducts();
};

#endif // INVENTORYWINDOW_H

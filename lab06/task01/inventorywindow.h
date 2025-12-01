#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H

#include <QMainWindow>
#include <vector>
#include "Product.h"
#include "Inventory.h"
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

namespace Ui {
class InventoryWindow;
}

class InventoryWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit InventoryWindow(QWidget *parent = nullptr);
    ~InventoryWindow();

private slots:
    void on_addButton_clicked();
    void on_searchButton_clicked();
    void on_showAllButton_clicked();
    void removeProduct(const std::string& name);

private:
    Ui::InventoryWindow *ui;
    Inventory<Product> inventory;

    void displayProducts(const std::vector<Product>& products);
    void addSampleProducts();
};

#endif // INVENTORYWINDOW_H

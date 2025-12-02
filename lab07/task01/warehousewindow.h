#ifndef WAREHOUSEWINDOW_H
#define WAREHOUSEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QInputDialog>
#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <vector>
#include "autopart.h"
#include "warehouse.h"

using namespace std;

namespace Ui
{
    class WarehouseWindow;
}

class WarehouseWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit WarehouseWindow(QWidget *parent = nullptr);
    ~WarehouseWindow();

private slots:
    void on_addButton_clicked();
    void on_showAllButton_clicked();
    void on_searchButton_clicked();
    void on_sortNameButton_clicked();
    void on_sortPriceButton_clicked();
    void removePart(string name);
    void updatePart(string name);
    void on_addMultipleButton_clicked();
    void on_removeMultipleButton_clicked();

private:
    Ui::WarehouseWindow *ui;
    Warehouse<AutoPart> warehouse;
    bool nameSortAscending = true;
    bool priceSortAscending = true;

    void displayParts(vector<AutoPart> parts);
    void addSampleParts();
};

#endif // WAREHOUSEWINDOW_H

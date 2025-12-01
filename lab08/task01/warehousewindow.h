#ifndef WAREHOUSEWINDOW_H
#define WAREHOUSEWINDOW_H

#include "warehouse.h"
#include "autopart.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextEdit>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QDialogButtonBox>

QT_BEGIN_NAMESPACE
namespace Ui{
class WarehouseWindow;
}
QT_END_NAMESPACE

class WarehouseWindow : public QMainWindow{
    Q_OBJECT

public:
    WarehouseWindow(QWidget *parent = nullptr);
    ~WarehouseWindow();

private slots:
    void on_searchButton_clicked();
    void on_showAllButton_clicked();
    void on_sortNameButton_clicked();
    void on_sortPriceButton_clicked();

    void on_showUniqueNamesButton_clicked();
    void on_addSupplyButton_clicked();
    void on_processSupplyButton_clicked();
    void on_showMultimapButton_clicked();
    void on_showSupplyQueueButton_clicked();
    void on_showLowStockButton_clicked();
    void on_showHistoryButton_clicked();

    void onTableCellDoubleClicked(int row, int column);

private:
    Ui::WarehouseWindow *ui;
    Warehouse warehouse;
    bool nameSortAscending = true;
    bool priceSortAscending = true;

    void displayParts(vector<AutoPart> parts);
    void updateStats();
    void removePart(string name);
    void updatePart(string name);
    void addSampleParts();
};

#endif // WAREHOUSEWINDOW_H

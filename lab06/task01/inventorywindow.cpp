#include "InventoryWindow.h"
#include "ui_InventoryWindow.h"

using namespace std;

InventoryWindow::InventoryWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::InventoryWindow){
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"Назва", "Ціна (грн)", "Кількість", "Дії"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    addSampleProducts();
}

InventoryWindow::~InventoryWindow(){
    delete ui;
}

void InventoryWindow::on_addButton_clicked(){
    QString name = ui->nameLineEdit->text().trimmed();
    double price = ui->priceSpinBox->value();
    int quantity = ui->quantitySpinBox->value();

    if (name.isEmpty()){
        QMessageBox::warning(this, "Pomilka", "Введіть назву товару!");
        return;
    }

    Product product(name.toStdString(), price, quantity);
    inventory.addItem(product);

    ui->nameLineEdit->clear();
    ui->priceSpinBox->setValue(0);
    ui->quantitySpinBox->setValue(0);

    on_showAllButton_clicked();
    QMessageBox::information(this, "Успіх", "Товар успішно додано!");
}

void InventoryWindow::on_showAllButton_clicked(){
    displayProducts(inventory.getAllItems());
}

void InventoryWindow::on_searchButton_clicked(){
    double price = ui->searchPriceSpinBox->value();
    auto found = inventory.findByPrice(price);

    if (found.empty()){
        QMessageBox::information(this, "Результат пошуку",
                                 "Товарів з такою ціною не знайдено!");
    }

    displayProducts(found);
}

void InventoryWindow::removeProduct(string &name){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження",
                                  QString("Видалити товар '%1'?").arg(QString::fromStdString(name)),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes){
        if (inventory.removeItem(name)){
            on_showAllButton_clicked();
            QMessageBox::information(this, "Успіх", "Товар видалено!");
        }
        else{
            QMessageBox::warning(this, "Помилка", "Не вдалося видалити товар!");
        }
    }
}

void InventoryWindow::displayProducts(vector<Product> &products){
    ui->tableWidget->setRowCount(0);

    for (size_t i = 0; i < products.size(); ++i){
        Product &product = products[i];

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0,
                                 new QTableWidgetItem(QString::fromStdString(product.getName())));
        ui->tableWidget->setItem(row, 1,
                                 new QTableWidgetItem(QString::number(product.getPrice(), 'f', 2)));
        ui->tableWidget->setItem(row, 2,
                                 new QTableWidgetItem(QString::number(product.getQuantity())));

        QPushButton *deleteButton = new QPushButton("Видалити");
        deleteButton->setMaximumWidth(100);
        string name = product.getName();
        connect(deleteButton, &QPushButton::clicked,
                [this, name](){
                    removeProduct(name);
                });

        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->addWidget(deleteButton);
        layout->setAlignment(Qt::AlignRight);
        layout->setContentsMargins(5, 2, 5, 2);

        ui->tableWidget->setCellWidget(row, 3, widget);
        ui->tableWidget->setRowHeight(row, 40);
    }

    for (int i = 0; i < 3; ++i){
        ui->tableWidget->resizeColumnToContents(i);
    }
}

void InventoryWindow::addSampleProducts(){
    inventory.addItem(Product("Ноутбук HP", 25000.00, 5));
    inventory.addItem(Product("Миша Logitech", 500.00, 20));
    inventory.addItem(Product("Клавіатура", 1200.00, 15));
    inventory.addItem(Product("Монітор Samsung", 8000.00, 8));
    inventory.addItem(Product("Навушники", 500.00, 30));

    on_showAllButton_clicked();
}

#include "InventoryWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>

InventoryWindow::InventoryWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Система керування складом");
    setMinimumSize(800, 600);

    // Центральний віджет
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Секція додавання товару
    QLabel* addLabel = new QLabel("<h3>Додати товар</h3>");
    mainLayout->addWidget(addLabel);

    QHBoxLayout* inputLayout = new QHBoxLayout();

    inputLayout->addWidget(new QLabel("Назва:"));
    nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Введіть назву товару");
    inputLayout->addWidget(nameEdit);

    inputLayout->addWidget(new QLabel("Ціна:"));
    priceSpinBox = new QDoubleSpinBox();
    priceSpinBox->setRange(0, 1000000);
    priceSpinBox->setDecimals(2);
    priceSpinBox->setSuffix(" грн");
    inputLayout->addWidget(priceSpinBox);

    inputLayout->addWidget(new QLabel("Кількість:"));
    quantitySpinBox = new QSpinBox();
    quantitySpinBox->setRange(0, 10000);
    inputLayout->addWidget(quantitySpinBox);

    QPushButton* addButton = new QPushButton("Додати");
    connect(addButton, &QPushButton::clicked, this, &InventoryWindow::addProduct);
    inputLayout->addWidget(addButton);

    mainLayout->addLayout(inputLayout);

    // Секція пошуку за ціною
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(new QLabel("Знайти за ціною:"));

    searchPriceSpinBox = new QDoubleSpinBox();
    searchPriceSpinBox->setRange(0, 1000000);
    searchPriceSpinBox->setDecimals(2);
    searchPriceSpinBox->setSuffix(" грн");
    searchLayout->addWidget(searchPriceSpinBox);

    QPushButton* searchButton = new QPushButton("Пошук");
    connect(searchButton, &QPushButton::clicked, this, &InventoryWindow::searchByPrice);
    searchLayout->addWidget(searchButton);

    QPushButton* showAllButton = new QPushButton("Показати всі");
    connect(showAllButton, &QPushButton::clicked, this, &InventoryWindow::showAllProducts);
    searchLayout->addWidget(showAllButton);

    searchLayout->addStretch();
    mainLayout->addLayout(searchLayout);

    // Таблиця товарів
    QLabel* tableLabel = new QLabel("<h3>Список товарів на складі</h3>");
    mainLayout->addWidget(tableLabel);

    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({"Назва", "Ціна (грн)", "Кількість", "Дії"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(tableWidget);

    // Додамо кілька прикладів товарів
    addSampleProducts();
}

void InventoryWindow::addProduct() {
    QString name = nameEdit->text().trimmed();
    double price = priceSpinBox->value();
    int quantity = quantitySpinBox->value();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Введіть назву товару!");
        return;
    }

    Product product(name.toStdString(), price, quantity);
    inventory.addItem(product);

    // Очистити поля вводу
    nameEdit->clear();
    priceSpinBox->setValue(0);
    quantitySpinBox->setValue(0);

    showAllProducts();
    QMessageBox::information(this, "Успіх", "Товар успішно додано!");
}

void InventoryWindow::showAllProducts() {
    displayProducts(inventory.getAllItems());
}

void InventoryWindow::searchByPrice() {
    double price = searchPriceSpinBox->value();
    auto found = inventory.findByPrice(price);

    if (found.empty()) {
        QMessageBox::information(this, "Результат пошуку",
                                 "Товарів з такою ціною не знайдено!");
    }

    displayProducts(found);
}

void InventoryWindow::removeProduct(const std::string& name) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження",
                                  QString("Видалити товар '%1'?").arg(QString::fromStdString(name)),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (inventory.removeItem(name)) {
            showAllProducts();
            QMessageBox::information(this, "Успіх", "Товар видалено!");
        } else {
            QMessageBox::warning(this, "Помилка", "Не вдалося видалити товар!");
        }
    }
}

void InventoryWindow::displayProducts(const std::vector<Product>& products) {
    tableWidget->setRowCount(0);

    for (size_t i = 0; i < products.size(); ++i) {
        const Product& product = products[i];

        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0,
                             new QTableWidgetItem(QString::fromStdString(product.getName())));
        tableWidget->setItem(row, 1,
                             new QTableWidgetItem(QString::number(product.getPrice(), 'f', 2)));
        tableWidget->setItem(row, 2,
                             new QTableWidgetItem(QString::number(product.getQuantity())));

        QPushButton* deleteButton = new QPushButton("Видалити");
        std::string name = product.getName();
        connect(deleteButton, &QPushButton::clicked,
                [this, name]() { removeProduct(name); });
        tableWidget->setCellWidget(row, 3, deleteButton);
    }

    tableWidget->resizeColumnsToContents();
}

void InventoryWindow::addSampleProducts() {
    // Додаємо приклади товарів
    inventory.addItem(Product("Ноутбук HP", 25000.00, 5));
    inventory.addItem(Product("Миша Logitech", 500.00, 20));
    inventory.addItem(Product("Клавіатура", 1200.00, 15));
    inventory.addItem(Product("Монітор Samsung", 8000.00, 8));
    inventory.addItem(Product("Навушники", 500.00, 30));

    showAllProducts();
}

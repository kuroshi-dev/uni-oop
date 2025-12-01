#include "warehousewindow.h"
#include "ui_warehousewindow.h"

using namespace std;

WarehouseWindow::WarehouseWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WarehouseWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"Назва", "Виробник", "Ціна (грн)", "Кількість", "Дії"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    addSampleParts();
}

WarehouseWindow::~WarehouseWindow()
{
    delete ui;
}

void WarehouseWindow::on_addButton_clicked(){
    QString name = ui->nameLineEdit->text().trimmed();
    QString manufacturer = ui->manufacturerLineEdit->text().trimmed();
    double price = ui->priceSpinBox->value();
    int quantity = ui->quantitySpinBox->value();

    if (name.isEmpty()){
        QMessageBox::warning(this, "Помилка", "Введіть назву запчастини!");
        return;
    }

    if (manufacturer.isEmpty()){
        QMessageBox::warning(this, "Помилка", "Введіть виробника!");
        return;
    }

    AutoPart part(name.toStdString(), manufacturer.toStdString(), price, quantity);
    warehouse.addPart(part);

    ui->nameLineEdit->clear();
    ui->manufacturerLineEdit->clear();
    ui->priceSpinBox->setValue(0);
    ui->quantitySpinBox->setValue(0);

    on_showAllButton_clicked();
    QMessageBox::information(this, "Успіх", "Запчастину успішно додано!");
}

void WarehouseWindow::on_showAllButton_clicked(){
    displayParts(warehouse.getAllParts());
}

void WarehouseWindow::on_searchButton_clicked(){
    QString manufacturer = ui->searchLineEdit->text().trimmed();

    if (manufacturer.isEmpty()){
        QMessageBox::warning(this, "Помилка", "Введіть виробника для пошуку!");
        return;
    }

    auto found = warehouse.findByManufacturer(manufacturer.toStdString());

    if (found.empty()){
        QMessageBox::information(this, "Результат пошуку",
                                 "Запчастин від цього виробника не знайдено!");
    }

    displayParts(found);
}

void WarehouseWindow::on_sortNameButton_clicked(){
    warehouse.sortByName();
    if (!nameSortAscending){
        auto parts = warehouse.getAllParts();
        reverse(parts.begin(), parts.end());
        ui->tableWidget->setRowCount(0);
        displayParts(parts);
    }
    else{
        on_showAllButton_clicked();
    }
    nameSortAscending = !nameSortAscending;
}

void WarehouseWindow::on_sortPriceButton_clicked(){
    warehouse.sortByPrice();
    if (!priceSortAscending){
        auto parts = warehouse.getAllParts();
        reverse(parts.begin(), parts.end());
        ui->tableWidget->setRowCount(0);
        displayParts(parts);
    }
    else{
        on_showAllButton_clicked();
    }
    priceSortAscending = !priceSortAscending;
}

void WarehouseWindow::removePart(string &name) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження",
                                  QString("Видалити запчастину '%1'?").arg(QString::fromStdString(name)),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes){
        if (warehouse.removePart(name)){
            on_showAllButton_clicked();
            QMessageBox::information(this, "Успіх", "Запчастину видалено!");
        }
        
        else{
            QMessageBox::warning(this, "Помилка", "Не вдалося видалити запчастину!");
        }
    }
}

void WarehouseWindow::updatePart(string &name){
    auto parts = warehouse.getAllParts();
    auto it = find_if(parts.begin(), parts.end(),
                      [&name](AutoPart &part)
                      {
                          return part.getName() == name;
                      });

    if (it == parts.end())
    {
        QMessageBox::warning(this, "Помилка", "Запчастину не знайдено!");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Оновлення запчастини");
    dialog.setMinimumWidth(400);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *titleLabel = new QLabel(QString("Оновлення: %1").arg(QString::fromStdString(name)));
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    QFormLayout *formLayout = new QFormLayout();

    QLineEdit *nameEdit = new QLineEdit(QString::fromStdString(it->getName()));
    QLineEdit *manufacturerEdit = new QLineEdit(QString::fromStdString(it->getManufacturer()));
    QDoubleSpinBox *priceSpinBox = new QDoubleSpinBox();
    priceSpinBox->setRange(0, 1000000);
    priceSpinBox->setDecimals(2);
    priceSpinBox->setSuffix(" грн");
    priceSpinBox->setValue(it->getPrice());

    QSpinBox *quantitySpinBox = new QSpinBox();
    quantitySpinBox->setRange(0, 10000);
    quantitySpinBox->setValue(it->getQuantity());

    formLayout->addRow("Назва:", nameEdit);
    formLayout->addRow("Виробник:", manufacturerEdit);
    formLayout->addRow("Ціна:", priceSpinBox);
    formLayout->addRow("Кількість:", quantitySpinBox);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted){
        QString newName = nameEdit->text().trimmed();
        QString newManufacturer = manufacturerEdit->text().trimmed();

        if (newName.isEmpty()){
            QMessageBox::warning(this, "Помилка", "Назва не може бути порожньою!");
            return;
        }

        if (newManufacturer.isEmpty()){
            QMessageBox::warning(this, "Помилка", "Виробник не може бути порожнім!");
            return;
        }

        warehouse.removePart(name);
        AutoPart updatedPart(newName.toStdString(), newManufacturer.toStdString(),
                             priceSpinBox->value(), quantitySpinBox->value());
        warehouse.addPart(updatedPart);

        on_showAllButton_clicked();
        QMessageBox::information(this, "Успіх", "Запчастину оновлено!");
    }
}

void WarehouseWindow::displayParts(vector<AutoPart> &parts){
    ui->tableWidget->setRowCount(0);

    for (size_t i = 0; i < parts.size(); ++i){
        AutoPart &part = parts[i];

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0,
                                 new QTableWidgetItem(QString::fromStdString(part.getName())));
        ui->tableWidget->setItem(row, 1,
                                 new QTableWidgetItem(QString::fromStdString(part.getManufacturer())));
        ui->tableWidget->setItem(row, 2,
                                 new QTableWidgetItem(QString::number(part.getPrice(), 'f', 2)));
        ui->tableWidget->setItem(row, 3,
                                 new QTableWidgetItem(QString::number(part.getQuantity())));

        QPushButton *updateButton = new QPushButton("Оновити");
        updateButton->setMaximumWidth(90);
        updateButton->setMinimumHeight(36);
        QPushButton *deleteButton = new QPushButton("Видалити");
        deleteButton->setMaximumWidth(90);
        deleteButton->setMinimumHeight(36);

        string name = part.getName();
        connect(updateButton, &QPushButton::clicked,
                [this, name]()
                { updatePart(name); });
        connect(deleteButton, &QPushButton::clicked,
                [this, name]()
                { removePart(name); });

        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);

        layout->addWidget(updateButton);
        layout->addWidget(deleteButton);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(5, 2, 5, 2);

        ui->tableWidget->setCellWidget(row, 4, widget);
        ui->tableWidget->setRowHeight(row, 50);
    }

    for (int i = 0; i < 4; ++i){
        ui->tableWidget->resizeColumnToContents(i);
    }
}

void WarehouseWindow::addSampleParts(){
    warehouse.addPart(AutoPart("Масляний фільтр", "Bosch", 250.00, 15));
    warehouse.addPart(AutoPart("Свічки запалювання", "NGK", 120.00, 40));
    warehouse.addPart(AutoPart("Гальмівні колодки", "Brembo", 1800.00, 10));
    warehouse.addPart(AutoPart("Повітряний фільтр", "Mann", 350.00, 20));
    warehouse.addPart(AutoPart("Акумулятор", "Varta", 3500.00, 5));
    warehouse.addPart(AutoPart("Ремінь ГРМ", "Gates", 890.00, 12));
    warehouse.addPart(AutoPart("Амортизатор", "Bilstein", 2200.00, 8));

    on_showAllButton_clicked();
}

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

void WarehouseWindow::removePart(string name) {
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

void WarehouseWindow::updatePart(string name){
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

void WarehouseWindow::displayParts(vector<AutoPart> parts){
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

void WarehouseWindow::on_addMultipleButton_clicked(){
    QDialog dialog(this);
    dialog.setWindowTitle("Додавання кількох запчастин");
    dialog.setMinimumWidth(500);
    dialog.setMinimumHeight(400);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *titleLabel = new QLabel("Додайте запчастини (одна на рядок)");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(11);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    QLabel *instructionLabel = new QLabel(
        "Формат: Назва | Виробник | Ціна | Кількість\n"
        "Приклад: Фільтр салону | Bosch | 450.50 | 10");
    instructionLabel->setStyleSheet("color: gray; font-size: 9pt;");
    mainLayout->addWidget(instructionLabel);

    QTextEdit *textEdit = new QTextEdit();
    textEdit->setPlaceholderText("Введіть запчастини...");
    mainLayout->addWidget(textEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted){
        QString text = textEdit->toPlainText().trimmed();
        if (text.isEmpty()){
            QMessageBox::warning(this, "Помилка", "Введіть хоча б одну запчастину!");
            return;
        }

        QStringList lines = text.split('\n', Qt::SkipEmptyParts);
        vector<AutoPart> newParts;
        QStringList errors;

        for (int i = 0; i < lines.size(); ++i){
            QString line = lines[i].trimmed();
            QStringList parts = line.split('|');

            if (parts.size() != 4){
                errors.append(QString("Рядок %1: неправильний формат").arg(i + 1));
                continue;
            }

            QString name = parts[0].trimmed();
            QString manufacturer = parts[1].trimmed();
            QString priceStr = parts[2].trimmed();
            QString quantityStr = parts[3].trimmed();

            if (name.isEmpty() || manufacturer.isEmpty()){
                errors.append(QString("Рядок %1: назва або виробник порожні").arg(i + 1));
                continue;
            }

            bool priceOk, quantityOk;
            double price = priceStr.toDouble(&priceOk);
            int quantity = quantityStr.toInt(&quantityOk);

            if (!priceOk || !quantityOk || price < 0 || quantity < 0){
                errors.append(QString("Рядок %1: неправильна ціна або кількість").arg(i + 1));
                continue;
            }

            newParts.push_back(AutoPart(name.toStdString(), manufacturer.toStdString(), price, quantity));
        }

        if (!errors.isEmpty()){
            QMessageBox::warning(this, "Помилки при додаванні",
                                 "Деякі запчастини не додані:\n" + errors.join("\n"));
        }

        if (!newParts.empty()){
            warehouse.addMultipleParts(newParts);
            on_showAllButton_clicked();
            QMessageBox::information(this, "Успіх",
                                     QString("Успішно додано %1 запчастин!").arg(newParts.size()));
        }
    }
}

void WarehouseWindow::on_removeMultipleButton_clicked(){
    QDialog dialog(this);
    dialog.setWindowTitle("Видалення кількох запчастин");
    dialog.setMinimumWidth(500);
    dialog.setMinimumHeight(400);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *titleLabel = new QLabel("Виберіть запчастини для видалення");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(11);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    QListWidget *listWidget = new QListWidget();
    auto allParts = warehouse.getAllParts();
    
    if (allParts.empty()){
        QMessageBox::information(this, "Інформація", "Склад порожній!");
        return;
    }

    for (const auto& part : allParts){
        QString itemText = QString("%1 (%2) - %3 грн, к-сть: %4")
            .arg(QString::fromStdString(part.getName()))
            .arg(QString::fromStdString(part.getManufacturer()))
            .arg(part.getPrice(), 0, 'f', 2)
            .arg(part.getQuantity());
        
        QListWidgetItem *item = new QListWidgetItem(itemText);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, QString::fromStdString(part.getName()));
        listWidget->addItem(item);
    }

    mainLayout->addWidget(listWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *selectAllButton = new QPushButton("Вибрати всі");
    QPushButton *deselectAllButton = new QPushButton("Зняти всі");
    buttonLayout->addWidget(selectAllButton);
    buttonLayout->addWidget(deselectAllButton);
    mainLayout->addLayout(buttonLayout);

    connect(selectAllButton, &QPushButton::clicked, [listWidget](){
        for (int i = 0; i < listWidget->count(); ++i){
            listWidget->item(i)->setCheckState(Qt::Checked);
        }
    });

    connect(deselectAllButton, &QPushButton::clicked, [listWidget](){
        for (int i = 0; i < listWidget->count(); ++i){
            listWidget->item(i)->setCheckState(Qt::Unchecked);
        }
    });

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted){
        vector<string> namesToRemove;
        
        for (int i = 0; i < listWidget->count(); ++i){
            QListWidgetItem *item = listWidget->item(i);
            if (item->checkState() == Qt::Checked){
                namesToRemove.push_back(item->data(Qt::UserRole).toString().toStdString());
            }
        }

        if (namesToRemove.empty()){
            QMessageBox::information(this, "Інформація", "Не вибрано жодної запчастини!");
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Підтвердження",
                                      QString("Видалити %1 запчастин?").arg(namesToRemove.size()),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes){
            int removed = warehouse.removeMultipleParts(namesToRemove);
            on_showAllButton_clicked();
            QMessageBox::information(this, "Успіх",
                                     QString("Видалено %1 з %2 запчастин!").arg(removed).arg(namesToRemove.size()));
        }
    }
}

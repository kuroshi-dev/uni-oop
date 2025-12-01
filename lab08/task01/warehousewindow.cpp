#include "warehousewindow.h"
#include "ui_warehousewindow.h"


WarehouseWindow::WarehouseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WarehouseWindow){
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"Назва", "Виробник", "Ціна (грн)", "Кількість"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &WarehouseWindow::onTableCellDoubleClicked);

    addSampleParts();
    displayParts(warehouse.getAllParts());
    updateStats();
}

WarehouseWindow::~WarehouseWindow(){
    delete ui;
}

void WarehouseWindow::on_searchButton_clicked(){
    string manufacturer = ui->searchLineEdit->text().trimmed().toStdString();

    if (manufacturer.empty()){
        QMessageBox::warning(this, "Помилка", "Введіть виробника для пошуку!");
        return;
    }

    vector<AutoPart> results = warehouse.findByManufacturer(manufacturer);

    if (results.empty()){
        QMessageBox::information(this, "Результати пошуку",
                                 QString("Запчастин від виробника '%1' не знайдено.")
                                 .arg(QString::fromStdString(manufacturer)));
    }

    displayParts(results);
}

void WarehouseWindow::on_showAllButton_clicked(){
    displayParts(warehouse.getAllParts());
}

void WarehouseWindow::on_sortNameButton_clicked(){
    vector<AutoPart> parts = warehouse.getAllParts();
    warehouse.sortByName(parts);

    if (!nameSortAscending){
        reverse(parts.begin(), parts.end());
    }

    displayParts(parts);
    nameSortAscending = !nameSortAscending;
}

void WarehouseWindow::on_sortPriceButton_clicked(){
    vector<AutoPart> parts = warehouse.getAllParts();
    warehouse.sortByPrice(parts);

    if (!priceSortAscending){
        reverse(parts.begin(), parts.end());
    }

    displayParts(parts);
    priceSortAscending = !priceSortAscending;
}

// ========== НОВІ ФУНКЦІЇ LAB 8 ==========

void WarehouseWindow::on_addSupplyButton_clicked(){
    QDialog dialog(this);
    dialog.setWindowTitle("Додати постачання (QUEUE)");
    dialog.setMinimumWidth(450);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();

    QLineEdit *nameEdit = new QLineEdit();
    QLineEdit *manufacturerEdit = new QLineEdit();
    QDoubleSpinBox *priceSpinBox = new QDoubleSpinBox();
    priceSpinBox->setRange(0, 1000000);
    priceSpinBox->setDecimals(2);
    priceSpinBox->setSuffix(" грн");

    QSpinBox *quantitySpinBox = new QSpinBox();
    quantitySpinBox->setRange(1, 10000);
    quantitySpinBox->setValue(10);

    QCheckBox *urgentCheckBox = new QCheckBox("Термінове постачання");

    formLayout->addRow("Назва:", nameEdit);
    formLayout->addRow("Виробник:", manufacturerEdit);
    formLayout->addRow("Ціна:", priceSpinBox);
    formLayout->addRow("Кількість:", quantitySpinBox);
    formLayout->addRow("", urgentCheckBox);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    
    QPushButton *cancelBtn = buttonBox->button(QDialogButtonBox::Cancel);
    if (cancelBtn) cancelBtn->setProperty("class", "secondary");
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted){
        QString name = nameEdit->text().trimmed();
        QString manufacturer = manufacturerEdit->text().trimmed();

        if (name.isEmpty() || manufacturer.isEmpty()){
            QMessageBox::warning(this, "Помилка", "Заповніть всі поля!");
            return;
        }

        AutoPart part(name.toStdString(), manufacturer.toStdString(),
                      priceSpinBox->value(), quantitySpinBox->value());

        warehouse.addSupplyOrder(part, urgentCheckBox->isChecked());
        updateStats();

        QMessageBox::information(this, "Успіх",
                                 QString("Постачання додано в чергу!\nВсього в черзі: %1")
                                     .arg(warehouse.getSupplyQueueSize()));
    }
}

void WarehouseWindow::on_processSupplyButton_clicked(){
    if (warehouse.getSupplyQueueSize() == 0){
        QMessageBox::information(this, "Інформація", "Черга постачань порожня!");
        return;
    }

    if (warehouse.processNextSupply()){
        updateStats();
        on_showAllButton_clicked();
        QMessageBox::information(this, "Успіх",
                                 QString("Постачання оброблено!\nЗалишилось в черзі: %1")
                                     .arg(warehouse.getSupplyQueueSize()));
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалося обробити постачання!");
    }
}

void WarehouseWindow::on_showUniqueNamesButton_clicked(){
    auto uniqueNames = warehouse.getUniqueNames();

    QString message = "<b>SET - Унікальні назви запчастин:</b><br><br>";
    message += QString("Всього унікальних назв: %1<br><br>").arg(uniqueNames.size());

    int count = 1;
    for (const auto& name : uniqueNames){
        message += QString("%1. %2<br>").arg(count++).arg(QString::fromStdString(name));
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Унікальні назви (SET)");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void WarehouseWindow::on_showSupplyQueueButton_clicked() {
    auto orders = warehouse.getAllSupplyOrders();

    if (orders.empty()) {
        QMessageBox::information(this, "Черга постачань", "Черга порожня!");
        return;
    }

    QString message = "<b>QUEUE - Черга постачань:</b><br><br>";
    message += QString("Всього в черзі: %1<br><br>").arg(orders.size());

    int count = 1;
    for (const auto& order : orders) {
        message += QString("<b>%1.</b> %2 (%3)<br>")
        .arg(count++)
            .arg(QString::fromStdString(order.part.getName()))
            .arg(QString::fromStdString(order.part.getManufacturer()));
        message += QString("   Кількість: %1, Дата: %2%3<br>")
                       .arg(order.part.getQuantity())
                       .arg(QString::fromStdString(order.orderDate))
                       .arg(order.isUrgent ? " <b>[ТЕРМІНОВЕ]</b>" : "");
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Черга постачань (QUEUE)");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void WarehouseWindow::on_showLowStockButton_clicked(){
    auto lowStock = warehouse.getLowStockParts(10);

    if (lowStock.empty()){
        QMessageBox::information(this, "Низькі запаси", "Немає запчастин на складі!");
        return;
    }

    QString message = "<b>PRIORITY_QUEUE - Запчастини з найменшими запасами:</b><br><br>";
    message += "Рекомендовано пріоритетне поповнення:<br><br>";

    int count = 1;
    for (const auto& part : lowStock){
        QString priority = "";
        if (part.getQuantity() < 5) priority = " <span style='color:red;'>[КРИТИЧНО]</span>";
        else if (part.getQuantity() < 10) priority = " <span style='color:orange;'>[НИЗЬКО]</span>";

        message += QString("<b>%1.</b> %2 (%3)%4<br>")
                       .arg(count++)
                       .arg(QString::fromStdString(part.getName()))
                       .arg(QString::fromStdString(part.getManufacturer()))
                       .arg(priority);
        message += QString("   Залишок: <b>%1 шт.</b>, Ціна: %2 грн<br>")
                       .arg(part.getQuantity())
                       .arg(part.getPrice(), 0, 'f', 2);
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Низькі запаси (PRIORITY_QUEUE)");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void WarehouseWindow::on_showHistoryButton_clicked(){
    if (!warehouse.hasHistory()){
        QMessageBox::information(this, "Історія", "Історія змін порожня!");
        return;
    }

    auto history = warehouse.getHistory(20);

    QString message = "<b>STACK - Історія змін (останні дії):</b><br><br>";
    message += QString("Всього записів: показано останні %1<br><br>").arg(history.size());

    int count = 1;
    for (const auto& entry : history){
        QString actionColor;
        if (entry.action == "ADD") actionColor = "green";
        else if (entry.action == "DELETE") actionColor = "red";
        else if (entry.action == "UPDATE") actionColor = "blue";
        else actionColor = "orange";

        message += QString("<b>%1.</b> <span style='color:%2;'>[%3]</span> %4 (%5)<br>")
                       .arg(count++)
                       .arg(actionColor)
                       .arg(QString::fromStdString(entry.action))
                       .arg(QString::fromStdString(entry.part.getName()))
                       .arg(QString::fromStdString(entry.part.getManufacturer()));
        message += QString("   Час: %1, Ціна: %2 грн, Кількість: %3<br>")
                       .arg(QString::fromStdString(entry.timestamp))
                       .arg(entry.part.getPrice(), 0, 'f', 2)
                       .arg(entry.part.getQuantity());
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Історія змін (STACK)");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void WarehouseWindow::on_showMultimapButton_clicked(){
    QDialog dialog(this);
    dialog.setWindowTitle("Пошук дубльованих запчастин (MULTIMAP)");
    dialog.setMinimumWidth(400);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("Введіть назву запчастини для пошуку всіх варіантів:");
    layout->addWidget(label);

    QLineEdit *searchEdit = new QLineEdit();
    layout->addWidget(searchEdit);

    QTextEdit *resultText = new QTextEdit();
    resultText->setReadOnly(true);
    layout->addWidget(resultText);

    QPushButton *searchBtn = new QPushButton("Пошук");
    layout->addWidget(searchBtn);

    connect(searchBtn, &QPushButton::clicked, [&](){
        QString name = searchEdit->text().trimmed();
        if (name.isEmpty()){
            resultText->setHtml("<span style='color:red;'>Введіть назву!</span>");
            return;
        }

        auto parts = warehouse.findAllByName(name.toStdString());

        if (parts.empty()){
            resultText->setHtml(QString("<span style='color:orange;'>Запчастин з назвою '%1' не знайдено!</span>")
                                    .arg(name));
            return;
        }

        QString html = QString("<b>MULTIMAP - Знайдено %1 варіант(ів) '%2':</b><br><br>")
                           .arg(parts.size())
                           .arg(name);

        int count = 1;
        for (const auto& part : parts){
            html += QString("<b>%1.</b> Виробник: %2<br>")
                        .arg(count++)
                        .arg(QString::fromStdString(part.getManufacturer()));
            html += QString("   Ціна: %1 грн, Кількість: %2 шт.<br><br>")
                        .arg(part.getPrice(), 0, 'f', 2)
                        .arg(part.getQuantity());
        }

        resultText->setHtml(html);
    });

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    QPushButton *closeBtn = buttonBox->button(QDialogButtonBox::Close);
    if (closeBtn) closeBtn->setProperty("class", "secondary");
    
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    dialog.exec();
}

void WarehouseWindow::removePart(string name){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження",
                                  QString("Видалити запчастину '%1'?")
                                      .arg(QString::fromStdString(name)),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes){
        if (warehouse.removePart(name)){
            updateStats();
            on_showAllButton_clicked();
            QMessageBox::information(this, "Успіх", "Запчастину видалено!");
        } else {
            QMessageBox::warning(this, "Помилка", "Не вдалося видалити запчастину!");
        }
    }
}

void WarehouseWindow::updatePart(string name){
    AutoPart* part = warehouse.findPart(name);

    if (!part){
        QMessageBox::warning(this, "Помилка", "Запчастину не знайдено!");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Оновлення запчастини");
    dialog.setMinimumWidth(400);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *titleLabel = new QLabel(QString("Оновлення: %1")
                                        .arg(QString::fromStdString(name)));
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    QFormLayout *formLayout = new QFormLayout();

    QDoubleSpinBox *priceSpinBox = new QDoubleSpinBox();
    priceSpinBox->setRange(0, 1000000);
    priceSpinBox->setDecimals(2);
    priceSpinBox->setSuffix(" грн");
    priceSpinBox->setValue(part->getPrice());

    QSpinBox *quantitySpinBox = new QSpinBox();
    quantitySpinBox->setRange(0, 10000);
    quantitySpinBox->setValue(part->getQuantity());

    formLayout->addRow("Ціна:", priceSpinBox);
    formLayout->addRow("Кількість:", quantitySpinBox);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    QPushButton *updateButton = buttonBox->addButton("Оновити", QDialogButtonBox::AcceptRole);
    QPushButton *deleteButton = buttonBox->addButton("Видалити", QDialogButtonBox::DestructiveRole);
    deleteButton->setProperty("class", "destructive");
    QPushButton *cancelButton = buttonBox->addButton("Скасувати", QDialogButtonBox::RejectRole);
    cancelButton->setProperty("class", "secondary");
    
    connect(updateButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    connect(deleteButton, &QPushButton::clicked, [&](){
        dialog.done(2);
    });
    
    mainLayout->addWidget(buttonBox);

    int result = dialog.exec();
    
    if (result == QDialog::Accepted){
        warehouse.updatePart(name, priceSpinBox->value(), quantitySpinBox->value());
        updateStats();
        on_showAllButton_clicked();
        QMessageBox::information(this, "Успіх", "Запчастину оновлено!");
    } else if (result == 2){
        removePart(name);
    }
}

void WarehouseWindow::displayParts(vector<AutoPart> parts){
    ui->tableWidget->setRowCount(0);

    for (size_t i = 0; i < parts.size(); ++i){
        const AutoPart& part = parts[i];

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

        string key = part.getName() + "_" + part.getManufacturer();
        connect(updateButton, &QPushButton::clicked,
                [this, key](){ updatePart(key); });
        connect(deleteButton, &QPushButton::clicked,
                [this, key](){ removePart(key); });

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
    warehouse.addPart(AutoPart("Масляний фільтр", "Bosch", 250.00, 3));
    warehouse.addPart(AutoPart("Масляний фільтр", "Mann", 220.00, 15));
    warehouse.addPart(AutoPart("Свічки запалювання", "NGK", 120.00, 2));
    warehouse.addPart(AutoPart("Гальмівні колодки", "Brembo", 1800.00, 10));
    warehouse.addPart(AutoPart("Повітряний фільтр", "Mann", 350.00, 20));
    warehouse.addPart(AutoPart("Акумулятор", "Varta", 3500.00, 1));
    warehouse.addPart(AutoPart("Ремінь ГРМ", "Gates", 890.00, 12));
    warehouse.addPart(AutoPart("Амортизатор", "Bilstein", 2200.00, 8));

    // Додаємо кілька постачань в чергу
    warehouse.addSupplyOrder(AutoPart("Свічки запалювання", "NGK", 120.00, 50), true);
    warehouse.addSupplyOrder(AutoPart("Акумулятор", "Varta", 3500.00, 5), true);
    warehouse.addSupplyOrder(AutoPart("Гальмівні колодки", "Brembo", 1800.00, 20), false);

    on_showAllButton_clicked();
}

void WarehouseWindow::updateStats(){
    ui->statsLabel->setText(QString(
        "📊 Статистика: Всього запчастин: %1 | Унікальних назв: %2 | "
        "Постачань в черзі: %3 | Історія: %4 записів")
        .arg(warehouse.size())
        .arg(warehouse.getUniqueNamesCount())
        .arg(warehouse.getSupplyQueueSize())
        .arg(warehouse.hasHistory() ? "є" : "немає"));
}

void WarehouseWindow::onTableCellDoubleClicked(int row, int column){
    Q_UNUSED(column);
    if (row < 0 || row >= ui->tableWidget->rowCount()) return;
    
    QString name = ui->tableWidget->item(row, 0)->text();
    QString manufacturer = ui->tableWidget->item(row, 1)->text();
    string key = name.toStdString() + "_" + manufacturer.toStdString();
    
    updatePart(key);
}

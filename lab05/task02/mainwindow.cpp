#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), trapSize(100), windowSize(80), gameRunning(false), score(0), level(1), fliesCaught(0){
    ui->setupUi(this);

    setFixedSize(800, 600);
    setWindowTitle("Гра: Піймай муху - Рівневе навчання");

    setStyleSheet("QMainWindow { background-color: #FFF8DC; }");

    trapLabel = new QLabel(this);
    trapLabel->setFixedSize(trapSize, trapSize);
    trapLabel->setScaledContents(true);

    windowLabel = new QLabel(this);
    windowLabel->setFixedSize(windowSize, windowSize);
    windowLabel->setScaledContents(true);

    windowLabel->setVisible(false); // show from second level

    scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(10, 10, 200, 30);
    scoreLabel->setStyleSheet("QLabel { color: black; font-size: 14pt; font-weight: bold; }");

    levelLabel = new QLabel(this);
    levelLabel->setGeometry(220, 10, 200, 30);
    levelLabel->setStyleSheet("QLabel { color: blue; font-size: 14pt; font-weight: bold; }");

    instructionLabel = new QLabel(this);
    instructionLabel->setGeometry(10, height() - 40, width() - 20, 30);
    instructionLabel->setStyleSheet("QLabel { color: black; font-size: 10pt; }");
    instructionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    createPixmaps();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGame);

    initializeGame();
    setMouseTracking(true);
    startGame();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::createPixmaps(){
    QPixmap trapPixmap(":/images/flytrap.png");
    if (!trapPixmap.isNull()){
        trapLabel->setPixmap(trapPixmap.scaled(trapSize, trapSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    QPixmap windowPixmap(":/images/window.png");
    if (windowPixmap.isNull()){
        windowPixmap = QPixmap(windowSize, windowSize);
        windowPixmap.fill(Qt::lightGray);
    }
    windowLabel->setPixmap(windowPixmap.scaled(windowSize, windowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap flyPixmap(":/images/fly.png");

    QPixmap fastflyPixmap(":/images/fastfly.png");
    QPixmap smartflyPixmap(":/images/smartfly.png");
}

void MainWindow::initializeGame(){
    level = 1;
    score = 0;
    fliesCaught = 0;
    gameRunning = true;
    initializeLevel();
}

void MainWindow::initializeLevel(){
    flies.clear();

    switch (level){
    case 1:
        flies.push_back(std::make_unique<Fly>(this, 1.5, 40));
        instructionLabel->setText("Рівень 1: Наведіть курсор на муху, щоб загнати її в пастку!");
        windowLabel->setVisible(false);
        break;
    case 2:
        flies.push_back(std::make_unique<Fly>(this, 1.5, 40));
        flies.push_back(std::make_unique<FastFly>(this));
        instructionLabel->setText("Рівень 2: Не дозволяйте мухам вилетіти у вікно!");
        windowLabel->setVisible(true);
        break;
    case 3:
        flies.push_back(std::make_unique<Fly>(this, 1.5, 40));
        flies.push_back(std::make_unique<FastFly>(this));
        flies.push_back(std::make_unique<SmartFly>(this));
        instructionLabel->setText("Рівень 3: Розумна муха прагне до вікна! Будьте обережні!");
        break;
    default:
        int flyCount = 2 + level;
        for (int i = 0; i < flyCount; i++)
        {
            if (i % 3 == 0)
                flies.push_back(std::make_unique<SmartFly>(this));
            else if (i % 2 == 0)
                flies.push_back(std::make_unique<FastFly>(this));
            else
                flies.push_back(std::make_unique<Fly>(this, 1.5, 40));
        }
        instructionLabel->setText(QString("Рівень %1: Зловіть всіх мух!").arg(level));
        break;
    }

    for (auto &fly : flies)
    {
        fly->getLabel()->show();
        fly->getLabel()->raise();
    }

    // Position trap
    trapPos = QPointF(
        QRandomGenerator::global()->bounded(trapSize, width() - trapSize),
        QRandomGenerator::global()->bounded(trapSize + 50, height() - trapSize - 50));
    trapLabel->move(trapPos.x() - trapSize / 2, trapPos.y() - trapSize / 2);

    // Position window (from level 2)
    if (level >= 2)
    {
        windowPos = QPointF(
            QRandomGenerator::global()->bounded(windowSize, width() - windowSize),
            QRandomGenerator::global()->bounded(windowSize + 50, height() - windowSize - 50));
        windowLabel->move(windowPos.x() - windowSize / 2, windowPos.y() - windowSize / 2);
    }

    // Set initial fly positions
    for (auto &fly : flies)
    {
        QPointF pos = getSafeSpawnPosition(fly->getSize());
        fly->setPosition(pos);
    }

    scoreLabel->setText(QString("Очки: %1").arg(score));
    levelLabel->setText(QString("Рівень: %1").arg(level));
}

bool MainWindow::event(QEvent *e){
    if (e->type() == QEvent::MouseMove && gameRunning){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
        for (auto &fly : flies){
            fly->update(mouseEvent->pos(), windowPos);
        }
    }
    return QMainWindow::event(e);
}

void MainWindow::updateGame(){
    if (!gameRunning)
        return;

    QPointF cursorPos = mapFromGlobal(QCursor::pos());

    // Update all flies
    for (auto &fly : flies){
        fly->update(cursorPos, windowPos);
        fly->checkBounds(width(), height());
    }

    if (checkCollisionWithTrap()){
        return;
    }

    if (level >= 2 && checkCollisionWithWindow()){
        flyEscaped();
        return;
    }

    score++;
    scoreLabel->setText(QString("Очки: %1").arg(score));
}

bool MainWindow::checkCollisionWithTrap(){
    for (auto it = flies.begin(); it != flies.end(); ++it){
        double dist = distance((*it)->getPosition(), trapPos);
        if (dist < ((*it)->getSize() / 2.0 + trapSize / 3.0)){
            flies.erase(it);
            fliesCaught++;

            if (flies.empty()){
                nextLevel();
            }
            return true;
        }
    }
    return false;
}

bool MainWindow::checkCollisionWithWindow(){
    if (level < 2)
        return false;

    for (auto it = flies.begin(); it != flies.end(); ++it){
        double dist = distance((*it)->getPosition(), windowPos);
        if (dist < ((*it)->getSize() / 2.0 + windowSize / 2.0)){
            return true;
        }
    }
    return false;
}

double MainWindow::distance(QPointF &p1, QPointF &p2){
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();
    return std::sqrt(dx * dx + dy * dy);
}

void MainWindow::nextLevel(){
    level++;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Рівень пройдено!");
    msgBox.setText(QString("Відмінно! Ви пройшли рівень %1!\n\nПереходимо до рівня %2")
                       .arg(level - 1)
                       .arg(level));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    initializeLevel();
}

void MainWindow::flyEscaped(){
    gameOver();
}

void MainWindow::gameOver(){
    gameRunning = false;
    gameTimer->stop();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Гра закінчена!");

    QString message;
    if (level >= 2){
        message = QString("Муха втекла через вікно!\n\nВи дісталися до рівня: %1\nВаш рахунок: %2 points\n\nБажаєте зіграти ще раз?")
                      .arg(level)
                      .arg(score);
    }
    else{
        message = QString("Муха попалась у пастку!\n\nВаш рахунок: %1 points\n\nБажаєте зіграти ще раз?").arg(score);
    }

    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int result = msgBox.exec();

    if (result == QMessageBox::Yes){
        initializeGame();
        startGame();
    }
    else{
        close();
    }
}

void MainWindow::startGame(){
    gameTimer->start(16); // ~60 FPS
}

QPointF MainWindow::getSafeSpawnPosition(int flySize){
    int maxAttempts = 50;
    double minDistanceFromTrap = trapSize + flySize + 50;
    double minDistanceFromWindow = windowSize + flySize + 50;

    for (int attempt = 0; attempt < maxAttempts; attempt++){
        QPointF pos(
            QRandomGenerator::global()->bounded(flySize + 50, width() - flySize - 50),
            QRandomGenerator::global()->bounded(flySize + 100, height() - flySize - 100));

        double distToTrap = distance(pos, trapPos);
        if (distToTrap < minDistanceFromTrap){
            continue;
        }

        if (level >= 2){
            double distToWindow = distance(pos, windowPos);
            if (distToWindow < minDistanceFromWindow){
                continue;
            }
        }

        // Check collision with other flies
        bool tooCloseToOtherFly = false;
        for (auto &otherFly : flies){
            if (otherFly->getPosition() != QPointF(0, 0)){
                double distToOtherFly = distance(pos, otherFly->getPosition());
                if (distToOtherFly < flySize + otherFly->getSize() + 30){
                    tooCloseToOtherFly = true;
                    break;
                }
            }
        }

        if (!tooCloseToOtherFly){
            return pos;
        }
    }

    // Fallback position
    return QPointF(flySize + 50, flySize + 100);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QCursor>
#include <QApplication>
#include <cmath>
#include <vector>
#include <memory>
#include <QDebug>

#include "fly.h"
#include "fastfly.h"
#include "smartfly.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool event(QEvent *e) override;

private slots:
    void updateGame();
    void startGame();

private:
    Ui::MainWindow *ui;

    std::vector<std::unique_ptr<Fly>> flies;
    QLabel *trapLabel;
    QLabel *windowLabel; // Represents the second window
    QLabel *scoreLabel;
    QLabel *levelLabel;
    QLabel *instructionLabel;

    QPointF trapPos;
    QPointF windowPos;
    int trapSize;
    int windowSize;

    QTimer *gameTimer;

    bool gameRunning;
    int score;
    int level;
    int fliesCaught;

    void initializeGame();
    void initializeLevel();
    void createPixmaps();
    bool checkCollisionWithTrap();
    bool checkCollisionWithWindow();
    double distance(const QPointF &p1, const QPointF &p2);
    void nextLevel();
    void gameOver();
    void flyEscaped();
    QPointF getSafeSpawnPosition(int flySize);
};

#endif // MAINWINDOW_H

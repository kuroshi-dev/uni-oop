#ifndef FLY_H
#define FLY_H

#include <QPointF>
#include <QRandomGenerator>
#include <QLabel>
#include <QPixmap>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Fly
{
protected:
    QPointF position;
    QPointF velocity;
    double speed;
    int size;
    QLabel *label;

public:
    Fly(QWidget *parent, double flySpeed = 3.0, int flySize = 40);
    virtual ~Fly();

    virtual void update(const QPointF &cursorPos, const QPointF &windowPos = QPointF());
    virtual void moveRandomly();
    virtual void moveAwayFromCursor(const QPointF &cursorPos);
    virtual void checkBounds(int windowWidth, int windowHeight);

    QPointF getPosition() const { return position; }
    void setPosition(const QPointF &pos);
    QLabel *getLabel() { return label; }
    int getSize() { return size; }

protected:
    virtual void createPixmap();
    virtual QString getImagePath() { return ":/images/fly.png"; }
};

#endif // FLY_H
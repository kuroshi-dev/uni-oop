#ifndef SMARTFLY_H
#define SMARTFLY_H

#include <cmath>
#include "fly.h"

class SmartFly : public Fly
{
private:
    QPointF targetWindow;
    bool seekingWindow;

public:
    SmartFly(QWidget *parent);
    void update(QPointF &cursorPos, QPointF &windowPos = QPointF()) override;
    void setWindowTarget(QPointF &windowPos) { targetWindow = windowPos; }

protected:
    QString getImagePath() override { return ":/images/smartfly.png"; }
    void moveTowardsWindow();
};

#endif // SMARTFLY_H

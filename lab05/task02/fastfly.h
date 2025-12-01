#ifndef FASTFLY_H
#define FASTFLY_H

#include "fly.h"

class FastFly : public Fly
{
public:
    FastFly(QWidget *parent);
    void update(QPointF &cursorPos, QPointF &windowPos = QPointF()) override;

protected:
    QString getImagePath() override { return ":/images/fastfly.png"; }
};

#endif // FASTFLY_H
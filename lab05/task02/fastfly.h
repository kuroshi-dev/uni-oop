#ifndef FASTFLY_H
#define FASTFLY_H

#include "fly.h"

class FastFly : public Fly
{
public:
    FastFly(QWidget *parent);
    void update(const QPointF &cursorPos, const QPointF &windowPos = QPointF()) override;

protected:
    QString getImagePath() override { return ":/images/fastfly.png"; }
};

#endif // FASTFLY_H
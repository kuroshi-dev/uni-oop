#include "fastfly.h"

FastFly::FastFly(QWidget *parent) : Fly(parent, 2.5, 35){
    createPixmap();
}

void FastFly::update(const QPointF &cursorPos, const QPointF &windowPos){
    QPointF direction = position - cursorPos;
    double dist = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (dist < 150.0 && dist > 0){
        direction /= dist;
        double panicFactor = (150.0 - dist) / 150.0;
        velocity += direction * speed * (0.7 + panicFactor * 1.5);
    }
    else{
        moveRandomly();
    }

    position += velocity;
    velocity *= 0.96;

    setPosition(position);
}

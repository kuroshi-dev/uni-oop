#include "smartfly.h"

SmartFly::SmartFly(QWidget *parent) : Fly(parent, 2.0, 45), seekingWindow(false){
    createPixmap();
}

void SmartFly::update(QPointF &cursorPos, QPointF &windowPos){
    if (!windowPos.isNull()){
        targetWindow = windowPos;
        seekingWindow = true;
    }

    QPointF direction = position - cursorPos;
    double distToCursor = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (distToCursor < 100.0){
        moveAwayFromCursor(cursorPos);
    }
    else if (seekingWindow){
        moveTowardsWindow();
    }
    else{
        moveRandomly();
    }

    position += velocity;
    velocity *= 0.94;

    setPosition(position);
}

void SmartFly::moveTowardsWindow(){
    QPointF direction = targetWindow - position;
    double dist = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (dist > 10.0){
        direction /= dist;
        velocity += direction * speed * 0.1;
    }
}

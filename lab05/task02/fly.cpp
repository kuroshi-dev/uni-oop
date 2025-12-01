#include "fly.h"
#include <QDebug>

Fly::Fly(QWidget *parent, double flySpeed, int flySize)
    : speed(flySpeed), size(flySize)
{
    label = new QLabel(parent);
    label->setFixedSize(size, size);
    label->setScaledContents(true);
    label->show();

    position = QPointF(parent->width() / 2.0, parent->height() / 2.0);
    velocity = QPointF(0, 0);

    createPixmap();
}

Fly::~Fly()
{
    delete label;
}

void Fly::createPixmap()
{
    QString imagePath = getImagePath();

    QPixmap flyPixmap(imagePath);
    if (flyPixmap.isNull())
    {
        qDebug() << "Failed to load image:" << imagePath;
        qDebug() << "Creating fallback black pixmap";

        flyPixmap = QPixmap(size, size);
        flyPixmap.fill(Qt::black);
    }
    else
    {
        qDebug() << "Successfully loaded image:" << imagePath;
    }

    label->setPixmap(flyPixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label->setVisible(true);
    label->raise();
}

void Fly::update(const QPointF &cursorPos, const QPointF &windowPos)
{
    QPointF direction = position - cursorPos;
    double distToCursor = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (distToCursor < 120.0 && distToCursor > 0)
    {
        moveAwayFromCursor(cursorPos);
    }
    else
    {
        moveRandomly();
    }

    position += velocity;
    velocity *= 0.98; // Apply friction
    setPosition(position);
}

void Fly::moveAwayFromCursor(const QPointF &cursorPos)
{
    QPointF direction = position - cursorPos;
    double dist = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (dist > 0)
    {
        direction /= dist;
        double panicFactor = (120.0 - dist) / 120.0;
        panicFactor = std::max(0.0, std::min(1.0, panicFactor));
        velocity += direction * speed * (0.5 + panicFactor * 0.8);
    }
}

void Fly::moveRandomly()
{
    double randomX = (QRandomGenerator::global()->generateDouble() - 0.5) * 2.0;
    double randomY = (QRandomGenerator::global()->generateDouble() - 0.5) * 2.0;
    velocity += QPointF(randomX * speed * 0.3, randomY * speed * 0.3);

    // Limit maximum speed
    double currentSpeed = std::sqrt(velocity.x() * velocity.x() + velocity.y() * velocity.y());
    if (currentSpeed > speed * 2.0)
    {
        velocity = velocity / currentSpeed * speed * 2.0;
    }
}

void Fly::setPosition(const QPointF &pos)
{
    position = pos;
    label->move(pos.x() - size / 2, pos.y() - size / 2);
    label->setVisible(true);
}

void Fly::checkBounds(int windowWidth, int windowHeight)
{
    bool bounced = false;

    if (position.x() <= size / 2)
    {
        position.setX(size / 2);
        velocity.setX(-velocity.x() * 0.8);
        bounced = true;
    }
    else if (position.x() >= windowWidth - size / 2)
    {
        position.setX(windowWidth - size / 2);
        velocity.setX(-velocity.x() * 0.8);
        bounced = true;
    }

    if (position.y() <= size / 2 + 50) // UI space
    {
        position.setY(size / 2 + 50);
        velocity.setY(-velocity.y() * 0.8);
        bounced = true;
    }
    else if (position.y() >= windowHeight - size / 2 - 50)
    {
        position.setY(windowHeight - size / 2 - 50);
        velocity.setY(-velocity.y() * 0.8);
        bounced = true;
    }

    if (bounced)
    {
        double randomX = (QRandomGenerator::global()->generateDouble() - 0.5) * speed;
        double randomY = (QRandomGenerator::global()->generateDouble() - 0.5) * speed;
        velocity += QPointF(randomX, randomY);
        setPosition(position);
    }
}
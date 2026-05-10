#include "pelota.h"

Pelota::Pelota() {
    velX = 5.0f;
    velY = 5.0f;
    radio = 20.0f;
    sprite = QPixmap(":/assets/pelota.png");
    sprite = sprite.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPos(400, 300);
}

QRectF Pelota::boundingRect() const {
    return QRectF(-radio, -radio, radio * 2, radio * 2);
}

void Pelota::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (!sprite.isNull())
        painter->drawPixmap(-radio, -radio, sprite);
    else {
        painter->setBrush(Qt::yellow);
        painter->drawEllipse(boundingRect());
    }
}

void Pelota::mover() {
    if (velY > 5.0f) velY = 5.0f;
    if (velY < -5.0f) velY = -5.0f;
    setPos(x() + velX, y() + velY);
}

void Pelota::rebotar() {
    velY = -velY;
}

QPainterPath Pelota::shape() const {
    QPainterPath path;
    path.addEllipse(-radio, -radio, radio * 2, radio * 2);
    return path;
}

float Pelota::getVelX() const { return velX; }
float Pelota::getVelY() const { return velY; }
void Pelota::setVelX(float vx) { velX = vx; }
void Pelota::setVelY(float vy) { velY = vy; }

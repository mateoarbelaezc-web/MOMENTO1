#include "pelota.h"

Pelota::Pelota() {
    velX = 5.0f;
    velY = 5.0f;
    radio = 8.0f;
    setPos(400, 300); // centro de la pantalla
}

QRectF Pelota::boundingRect() const {
    return QRectF(-radio, -radio, radio * 2, radio * 2);
}

void Pelota::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
}

void Pelota::mover() {
    setPos(x() + velX, y() + velY);
}

void Pelota::rebotar() {
    velY = -velY;
}

float Pelota::getVelX() const { return velX; }
float Pelota::getVelY() const { return velY; }
void Pelota::setVelX(float vx) { velX = vx; }
void Pelota::setVelY(float vy) { velY = vy; }

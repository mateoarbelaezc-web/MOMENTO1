#include "obstaculo.h"

Obstaculo::Obstaculo(float vel) {
    ancho = 20.0f;
    alto = 250.0f;
    velY = vel;
    limSuperior = 10.0f;
    limInferior = 350.0f;
    esMovil = true;
    setPos(390, 200);
}

QRectF Obstaculo::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void Obstaculo::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::gray);
    painter->drawRect(boundingRect());
}

void Obstaculo::moverVertical() {
    if (!esMovil) return;
    if (y() <= limSuperior || y() >= limInferior)
        velY = -velY;
    setPos(x(), y() + velY);
}

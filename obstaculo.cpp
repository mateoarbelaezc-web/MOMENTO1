#include "obstaculo.h"

Obstaculo::Obstaculo() {
    ancho = 20.0f;
    alto = 150.0f;
    velY = 3.0f;
    limSuperior = 50.0f;
    limInferior = 400.0f;
    esMovil = true;
    setPos(390, 200); // centro de la pantalla
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

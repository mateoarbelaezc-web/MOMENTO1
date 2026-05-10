#include "obstaculo.h"

Obstaculo::Obstaculo(float vel) {
    ancho = 150.0f;
    alto = 400.0f;
    velY = vel;
    limSuperior = 10.0f;
    limInferior = 200.0f;
    esMovil = true;
    sprite = QPixmap(":/assets/asteroides.png");
    sprite = sprite.scaled(80, 400, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPos(370, 100);
}

QRectF Obstaculo::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void Obstaculo::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (!sprite.isNull())
        painter->drawPixmap(0, 0, sprite);
    else {
        painter->setBrush(Qt::gray);
        painter->drawRect(boundingRect());
    }
}

void Obstaculo::moverVertical() {
    if (!esMovil) return;
    if (y() <= limSuperior || y() >= limInferior)
        velY = -velY;
    setPos(x(), y() + velY);
}

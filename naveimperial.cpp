#include "naveimperial.h"
#include <cstdlib>

NaveImperial::NaveImperial(float velocidadIA, float margenError) {
    ancho = 15.0f;
    alto = 80.0f;
    this->velocidadIA = velocidadIA;
    this->margenError = margenError;
    setPos(750, 260); // lado derecho de la pantalla
}

QRectF NaveImperial::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void NaveImperial::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::red);
    painter->drawRect(boundingRect());
}

void NaveImperial::seguirPelota(Pelota* pelota) {
    float error = (rand() % 100) / 100.0f * margenError;
    float objetivo = pelota->y() + error;

    if (y() + alto / 2 < objetivo && y() + alto < 600)
        setPos(x(), y() + velocidadIA);
    else if (y() + alto / 2 > objetivo && y() > 0)
        setPos(x(), y() - velocidadIA);
}

#include "naverebelde.h"

NaveRebelde::NaveRebelde() {
    ancho = 15.0f;
    alto = 80.0f;
    setPos(30, 260); // lado izquierdo de la pantalla
}

QRectF NaveRebelde::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void NaveRebelde::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());
}

void NaveRebelde::moverArriba() {
    if (y() > 0)
        setPos(x(), y() - 6);
}

void NaveRebelde::moverAbajo() {
    if (y() + alto < 600)
        setPos(x(), y() + 6);
}

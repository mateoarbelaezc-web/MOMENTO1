#include "naveimperial.h"
#include <cstdlib>

NaveImperial::NaveImperial(float velocidadIA, float margenError) {
    ancho = 100.0f;
    alto = 125.0f;
    this->velocidadIA = velocidadIA;
    this->margenError = margenError;
    sprite = QPixmap(":/assets/tiefighter.png");
    sprite = sprite.scaled(100, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPos(650, 260);
}

QRectF NaveImperial::boundingRect() const {
    return QRectF(20, 10, ancho - 40, alto - 20);
}

void NaveImperial::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (!sprite.isNull())
        painter->drawPixmap(0, 0, sprite);
    else {
        painter->setBrush(Qt::red);
        painter->drawRect(boundingRect());
    }
}

QPainterPath NaveImperial::shape() const {
    QPainterPath path;
    // Cuerpo central mas grande
    path.addEllipse(ancho * 0.20, alto * 0.20, ancho * 0.60, alto * 0.60);
    // Barra horizontal
    path.addRect(0, alto * 0.38, ancho, alto * 0.24);
    return path;
}

void NaveImperial::seguirPelota(Pelota* pelota) {
    float error = (rand() % 100) / 100.0f * margenError;
    float objetivo = pelota->y() + error;

    if (y() + alto / 2 < objetivo && y() + alto < 600)
        setPos(x(), y() + velocidadIA);
    else if (y() + alto / 2 > objetivo && y() > 0)
        setPos(x(), y() - velocidadIA);
}

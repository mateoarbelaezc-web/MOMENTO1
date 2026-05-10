#include "naverebelde.h"

NaveRebelde::NaveRebelde() {
    ancho = 100.0f;
    alto = 125.0f;
    sprite = QPixmap(":/assets/xwing.png");
    sprite = sprite.scaled(100, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPos(30, 260);
}

QRectF NaveRebelde::boundingRect() const {
    return QRectF(20, 10, ancho - 40, alto - 20);
}

void NaveRebelde::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (!sprite.isNull())
        painter->drawPixmap(0, 0, sprite);
    else {
        painter->setBrush(Qt::blue);
        painter->drawRect(boundingRect());
    }
}

QPainterPath NaveRebelde::shape() const {
    QPainterPath path;
    // Cuerpo central vertical
    path.addRect(ancho * 0.35, 0, ancho * 0.30, alto);
    // Cuerpo horizontal (alas principales)
    path.addRect(0, alto * 0.35, ancho, alto * 0.30);
    return path;
}

void NaveRebelde::moverArriba() {
    if (y() > 0)
        setPos(x(), y() - 6);
}

void NaveRebelde::moverAbajo() {
    if (y() + alto < 595)
        setPos(x(), y() + 6);
}

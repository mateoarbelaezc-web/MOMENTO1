#ifndef NAVEREBELDE_H
#define NAVEREBELDE_H

#include <QGraphicsItem>
#include <QPainter>

class NaveRebelde : public QGraphicsItem {
public:
    NaveRebelde();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void moverArriba();
    void moverAbajo();

private:
    float ancho;
    float alto;
};

#endif

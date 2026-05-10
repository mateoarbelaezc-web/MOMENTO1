#ifndef NAVEREBELDE_H
#define NAVEREBELDE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class NaveRebelde : public QGraphicsItem {
public:
    NaveRebelde();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void moverArriba();
    void moverAbajo();
    QPainterPath shape() const override;

private:
    float ancho;
    float alto;
    QPixmap sprite;
};

#endif

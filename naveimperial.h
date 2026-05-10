#ifndef NAVEIMPERIAL_H
#define NAVEIMPERIAL_H

#include <QGraphicsItem>
#include <QPainter>
#include "pelota.h"
#include <QPixmap>

class NaveImperial : public QGraphicsItem {
public:
    NaveImperial(float velocidadIA, float margenError);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void seguirPelota(Pelota* pelota);
    QPainterPath shape() const override;

private:
    float ancho;
    float alto;
    float velocidadIA;
    float margenError;
    QPixmap sprite;
};

#endif

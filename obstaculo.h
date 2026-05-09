#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QGraphicsItem>
#include <QPainter>

class Obstaculo : public QGraphicsItem {
public:
    Obstaculo();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void moverVertical();

private:
    float ancho;
    float alto;
    float velY;
    float limSuperior;
    float limInferior;
    bool esMovil;
};

#endif

#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Obstaculo : public QGraphicsItem {
public:
    Obstaculo(float vel);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void moverVertical();
private:
    float ancho, alto, velY, limSuperior, limInferior;
    bool esMovil;
    QPixmap sprite;
};
#endif

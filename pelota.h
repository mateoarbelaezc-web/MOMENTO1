#ifndef PELOTA_H
#define PELOTA_H

#include <QGraphicsItem>
#include <QPainter>

class Pelota : public QGraphicsItem {
public:
    Pelota();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mover();
    void rebotar();
    float getVelX() const;
    float getVelY() const;
    void setVelX(float vx);
    void setVelY(float vy);

private:
    float velX;
    float velY;
    float radio;
};

#endif

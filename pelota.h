#ifndef PELOTA_H
#define PELOTA_H

#include <QGraphicsItem>
#include <QPixmap>

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
    QPainterPath shape() const override;

    void setUsarGravedad(bool usar);
    void actualizarConGravedad(float gravedad, float sueloY);
    int getBounceCount() const;
    bool isDead() const;
    void setFrozen(bool congelada);

private:
    float velX, velY, radio;
    QPixmap sprite;
    bool usarGravedad;
    int bounceCount;
    bool dead, frozen;
    float restitution;
};

#endif

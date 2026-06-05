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

    // Cambio 4: solo una bola desviada por el jugador puede dañar al AT-AT
    void setDesviada(bool desviada);
    bool isDesviada() const;

    // Cambio borde: marcar si salió por el borde izquierdo sin ser desviada
    bool salio() const;

private:
    float velX, velY, radio;
    QPixmap sprite;
    bool usarGravedad;
    int bounceCount;
    bool dead, frozen;
    float restitution;
    bool fueDesviada;   // true solo si el jugador la golpeó con el sable
    bool salio_;        // true si tocó el borde izquierdo sin haber sido desviada
};

#endif

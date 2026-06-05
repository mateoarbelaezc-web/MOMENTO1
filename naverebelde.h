#ifndef NAVEREBELDE_H
#define NAVEREBELDE_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainterPath>

class NaveRebelde : public QGraphicsItem {
public:
    NaveRebelde();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void moverArriba();
    void moverAbajo();
    QPainterPath shape() const override;

    void setModoJedi(bool activar);
    void actualizarFisica();
    void saltar();
    void activarSwing();
    bool isSwinging() const;
    void setMultiplicadorVelocidad(float mult);
    void moverIzquierda(bool activo);
    void moverDerecha(bool activo);
    void setLimites(float izquierda, float derecha, float sueloY);

private:
    float ancho, alto;
    QPixmap sprite;
    QPixmap spriteIdle;
    QPixmap spriteWalk1;   // dos frames de caminata
    QPixmap spriteWalk2;
    QPixmap spriteJump;
    QPixmap spriteSwing;
    bool modoJedi;

    float vx, vy;
    bool enSuelo;
    float gravedad, potenciaSalto, velocidadMovimiento, multiplicadorVel;
    float limiteIzquierdo, limiteDerecho, sueloY;
    bool izquierdaPresionada, derechaPresionada;
    bool swingActivo;
    int swingFrames;
    int swingSpriteCounter;
    int walkFrameCounter;
    bool walkToggle;
};

#endif

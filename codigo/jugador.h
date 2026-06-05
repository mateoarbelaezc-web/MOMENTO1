#ifndef JUGADOR_H
#define JUGADOR_H

#include <QPainterPath>
#include "personaje.h"

class Jugador : public Personaje {
public:
    Jugador();
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
    QPixmap spriteIdle;
    QPixmap spriteWalk1;
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

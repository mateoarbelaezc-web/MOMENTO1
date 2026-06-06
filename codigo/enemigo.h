#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include "pelota.h"
#include <QPainterPath>
#include <QVector>

struct ShotRecord { int tipo; float vx, vy; int usos, exitos; float posXJugador; };
class Enemigo : public Personaje {
public:
    Enemigo(float velocidadIA, float margenError);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void seguirPelota(Pelota* pelota);
    QPainterPath shape() const override;
    void setModoJedi(bool activar, float factorAprendizaje);
    void leerPelota(const Pelota* pelota, bool fueGolpeadaPorJugador);
    void procesar();
    Pelota* ejecutar();
    void aprender(bool jugadorPerdioVida, int tipoDisparoUsado);
    void recibirDanio(int puntos);
    int getVida() const;
    void setMultiplicadorDanio(float mult);
    void setPosicionDisparo(float x, float y);
    int getTipoSeleccionado() const;
    void setPosXJugador(float x);
private:
    float velocidadIA, margenError;
    bool modoJedi;
    float percepX, percepY, percepVx, percepVy;
    bool bolaEntrante;
    int ultimaZonaImpacto, tipoSeleccionado;
    QVector<ShotRecord> memoria;
    float dificultadIA;
    int vida;
    float multiplicadorDanio;
    float posDisparoX, posDisparoY;
    int tipoAnterior;
    int contadorRepeticion;
    float posXJugadorActual;
};
#endif

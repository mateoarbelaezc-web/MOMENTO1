#ifndef NAVEIMPERIAL_H
#define NAVEIMPERIAL_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QVector>
#include "pelota.h"

struct ShotRecord { int tipo; float vx, vy; int usos, exitos; };

class NaveImperial : public QGraphicsItem {
public:
    NaveImperial(float velocidadIA, float margenError);
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

private:
    float ancho, alto, velocidadIA, margenError;
    QPixmap sprite;
    bool modoJedi;
    float percepX, percepY, percepVx, percepVy;
    bool bolaEntrante;
    int ultimaZonaImpacto, tipoSeleccionado;
    QVector<ShotRecord> memoria;
    float dificultadIA;
    int vida;
    float multiplicadorDanio;
    float posDisparoX, posDisparoY;

    // Cambio 2: penalizar repetición de mismo disparo sin éxito
    int tipoAnterior;       // tipo usado en el disparo previo
    int contadorRepeticion; // cuántas veces seguidas se usó el mismo tipo sin éxito
};

#endif

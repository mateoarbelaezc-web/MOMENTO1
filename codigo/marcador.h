#ifndef MARCADOR_H
#define MARCADOR_H

#include <QGraphicsTextItem>
#include <QString>

class Marcador : public QGraphicsTextItem {
public:
    Marcador(int gamesParaGanar);
    void anotarJugador();
    void anotarImperio();
    void actualizar();
    bool juegoTerminado();
    QString ganador();
    int getSetsJugador() { return setsJugador; }
    int getSetsImperio() { return setsImperio; }
    bool hayGanador();
    void anotarTieJugador();
    void anotarTieImperio();
    bool getEnTieBreak() { return enTieBreak; }

private:
    int puntosJugador, puntosImperio;
    int gamesJugador, gamesImperio;
    int setsJugador, setsImperio;
    bool enDeuce;
    bool ventajaJugador, ventajaImperio;
    QString puntoATexto(int puntos);
    void ganarJuego(bool jugador);
    void ganarSet(bool jugador);
    bool enTieBreak;
    int puntosTieJugador, puntosTieImperio;
    int gamesParaGanar;
};

#endif

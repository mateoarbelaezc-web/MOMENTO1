#ifndef MARCADOR_H
#define MARCADOR_H

#include <QGraphicsTextItem>
#include <QString>

class Marcador : public QGraphicsTextItem {
public:
    Marcador();
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
    // Puntos del juego actual (0,15,30,40,deuce)
    int puntosJugador;
    int puntosImperio;

    // Games ganados en el set actual
    int gamesJugador;
    int gamesImperio;

    // Sets ganados
    int setsJugador;
    int setsImperio;

    bool enDeuce;
    bool ventajaJugador;
    bool ventajaImperio;

    QString puntoATexto(int puntos);
    void ganarJuego(bool jugador);
    void ganarSet(bool jugador);

    bool enTieBreak;
    int puntosTieJugador;
    int puntosTieImperio;
};

#endif

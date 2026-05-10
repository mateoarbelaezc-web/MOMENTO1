#include "marcador.h"
#include <QDebug>
#include <QFont>

Marcador::Marcador(int gamesParaGanar) {
    this->gamesParaGanar = gamesParaGanar;
    puntosJugador = 0;
    puntosImperio = 0;
    gamesJugador = 0;
    gamesImperio = 0;
    setsJugador = 0;
    setsImperio = 0;
    enDeuce = false;
    ventajaJugador = false;
    ventajaImperio = false;
    enTieBreak = false;
    puntosTieJugador = 0;
    puntosTieImperio = 0;
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("Arial", 14, QFont::Bold));
    setPos(250, 10);
    actualizar();
}

QString Marcador::puntoATexto(int puntos) {
    if (puntos == 0) return "0";
    if (puntos == 1) return "15";
    if (puntos == 2) return "30";
    if (puntos == 3) return "40";
    return "?";
}

void Marcador::anotarJugador() {
    if (enDeuce) {
        if (ventajaImperio) {
            ventajaImperio = false; // vuelve a Deuce
        } else if (ventajaJugador) {
            ganarJuego(true); // tenía Ad, gana el game
            enDeuce = false;
            ventajaJugador = false;
        } else {
            ventajaJugador = true; // obtiene Ad
        }
    } else {
        puntosJugador++;
        if (puntosJugador == 3 && puntosImperio == 3) {
            enDeuce = true;
        } else if (puntosJugador > 3) {
            ganarJuego(true);
        }
    }
    actualizar();
}

void Marcador::anotarImperio() {
    if (enDeuce) {
        if (ventajaJugador) {
            ventajaJugador = false; // vuelve a Deuce
        } else if (ventajaImperio) {
            ganarJuego(false); // tenía Ad, gana el game
            enDeuce = false;
            ventajaImperio = false;
        } else {
            ventajaImperio = true; // obtiene Ad
        }
    } else {
        puntosImperio++;
        if (puntosJugador == 3 && puntosImperio == 3) {
            enDeuce = true;
        } else if (puntosImperio > 3) {
            ganarJuego(false);
        }
    }
    actualizar();
}

void Marcador::ganarJuego(bool jugador) {
    puntosJugador = 0;
    puntosImperio = 0;
    enDeuce = false;
    if (jugador) gamesJugador++;
    else gamesImperio++;

    // verificar tie break
    if (gamesJugador == gamesParaGanar && gamesImperio == gamesParaGanar) {
        enTieBreak = true;
    } else if (gamesJugador >= gamesParaGanar && gamesJugador - gamesImperio >= 2) {
        ganarSet(true);
    } else if (gamesImperio >= gamesParaGanar && gamesImperio - gamesJugador >= 2) {
        ganarSet(false);
    }
}

void Marcador::ganarSet(bool jugador) {
    gamesJugador = 0;
    gamesImperio = 0;
    if (jugador) setsJugador++;
    else setsImperio++;
}

bool Marcador::juegoTerminado() {
    return setsJugador >= 1 || setsImperio >= 1;
}

QString Marcador::ganador() {
    if (setsJugador >= 1) return "¡La Alianza Rebelde ha ganado!";
    if (setsImperio >= 1) return "¡El Imperio Galactico ha ganado!";
    return "";
}

bool Marcador::hayGanador() {
    return setsJugador >= 1 || setsImperio >= 1;
}

void Marcador::anotarTieJugador() {
    puntosTieJugador++;
    if (puntosTieJugador >= 7 && puntosTieJugador - puntosTieImperio >= 2) {
        enTieBreak = false;
        puntosTieJugador = 0;
        puntosTieImperio = 0;
        ganarSet(true);
    }
    actualizar();
}

void Marcador::anotarTieImperio() {
    puntosTieImperio++;
    if (puntosTieImperio >= 7 && puntosTieImperio - puntosTieJugador >= 2) {
        enTieBreak = false;
        puntosTieJugador = 0;
        puntosTieImperio = 0;
        ganarSet(false);
    }
    actualizar();
}

void Marcador::actualizar() {
    QString texto;
    if (enTieBreak) {
        texto += "TIE BREAK: " + QString::number(puntosTieJugador) +
                 " - " + QString::number(puntosTieImperio) + "\n";
        setPlainText(texto);
        return;
    }
    // Sets
    texto += "Sets: " + QString::number(setsJugador) +
             " - " + QString::number(setsImperio) + "\n";

    // Games
    texto += "Games: " + QString::number(gamesJugador) +
             " - " + QString::number(gamesImperio) + "\n";

    // Puntos
    if (enDeuce) {
        if (ventajaJugador) texto += "Ad - Rebelde";
        else if (ventajaImperio) texto += "Ad - Imperio";
        else texto += "Deuce";
    } else {
        texto += "Puntos: " + puntoATexto(puntosJugador) +
                 " - " + puntoATexto(puntosImperio);
    }

    setPlainText(texto);
}

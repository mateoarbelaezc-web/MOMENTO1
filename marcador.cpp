// marcador.cpp
#include "marcador.h"
#include <QFont>

Marcador::Marcador(int gamesParaGanar) {
    this->gamesParaGanar = gamesParaGanar;
    puntosJugador = puntosImperio = 0;
    gamesJugador = gamesImperio = 0;
    setsJugador = setsImperio = 0;
    enDeuce = ventajaJugador = ventajaImperio = false;
    enTieBreak = false;
    puntosTieJugador = puntosTieImperio = 0;
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
        if (ventajaImperio) ventajaImperio = false;
        else if (ventajaJugador) { ganarJuego(true); enDeuce = false; ventajaJugador = false; }
        else ventajaJugador = true;
    } else {
        puntosJugador++;
        if (puntosJugador == 3 && puntosImperio == 3) enDeuce = true;
        else if (puntosJugador > 3) ganarJuego(true);
    }
    actualizar();
}

void Marcador::anotarImperio() {
    if (enDeuce) {
        if (ventajaJugador) ventajaJugador = false;
        else if (ventajaImperio) { ganarJuego(false); enDeuce = false; ventajaImperio = false; }
        else ventajaImperio = true;
    } else {
        puntosImperio++;
        if (puntosJugador == 3 && puntosImperio == 3) enDeuce = true;
        else if (puntosImperio > 3) ganarJuego(false);
    }
    actualizar();
}

void Marcador::ganarJuego(bool jugador) {
    puntosJugador = puntosImperio = 0;
    enDeuce = false;
    if (jugador) gamesJugador++;
    else gamesImperio++;
    if (gamesJugador == gamesParaGanar && gamesImperio == gamesParaGanar) enTieBreak = true;
    else if (gamesJugador >= gamesParaGanar && gamesJugador - gamesImperio >= 2) ganarSet(true);
    else if (gamesImperio >= gamesParaGanar && gamesImperio - gamesJugador >= 2) ganarSet(false);
}

void Marcador::ganarSet(bool jugador) {
    gamesJugador = gamesImperio = 0;
    if (jugador) setsJugador++;
    else setsImperio++;
}

bool Marcador::juegoTerminado() { return setsJugador >= 1 || setsImperio >= 1; }
QString Marcador::ganador() {
    if (setsJugador >= 1) return "¡La Alianza Rebelde ha ganado!";
    if (setsImperio >= 1) return "¡El Imperio Galactico ha ganado!";
    return "";
}
bool Marcador::hayGanador() { return setsJugador >= 1 || setsImperio >= 1; }

void Marcador::anotarTieJugador() {
    puntosTieJugador++;
    if (puntosTieJugador >= 7 && puntosTieJugador - puntosTieImperio >= 2) {
        enTieBreak = false;
        puntosTieJugador = puntosTieImperio = 0;
        ganarSet(true);
    }
    actualizar();
}

void Marcador::anotarTieImperio() {
    puntosTieImperio++;
    if (puntosTieImperio >= 7 && puntosTieImperio - puntosTieJugador >= 2) {
        enTieBreak = false;
        puntosTieJugador = puntosTieImperio = 0;
        ganarSet(false);
    }
    actualizar();
}

void Marcador::actualizar() {
    QString texto;
    if (enTieBreak) {
        texto = "TIE BREAK: " + QString::number(puntosTieJugador) + " - " + QString::number(puntosTieImperio);
        setPlainText(texto);
        return;
    }
    texto = "Sets: " + QString::number(setsJugador) + " - " + QString::number(setsImperio) + "\n";
    texto += "Games: " + QString::number(gamesJugador) + " - " + QString::number(gamesImperio) + "\n";
    if (enDeuce) {
        if (ventajaJugador) texto += "Ad - Rebelde";
        else if (ventajaImperio) texto += "Ad - Imperio";
        else texto += "Deuce";
    } else {
        texto += "Puntos: " + puntoATexto(puntosJugador) + " - " + puntoATexto(puntosImperio);
    }
    setPlainText(texto);
}

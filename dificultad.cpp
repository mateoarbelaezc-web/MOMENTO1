#include "dificultad.h"
#include <stdexcept>

Dificultad::Dificultad(int nivel) {
    if (nivel != 1 && nivel != 2)
        throw std::invalid_argument("Nivel invalido");
    this->nivel = nivel;
    modoJedi = false;
    if (nivel == 1) {
        velBola = 6.5f; velEnemigo = 3.3f; margenError = 80.0f;
        gamesParaGanar = 2; velObstaculo = 4.5f;
    } else {
        velBola = 9.0f; velEnemigo = 4.5f; margenError = 71.0f;
        gamesParaGanar = 3; velObstaculo = 7.0f;
    }
}

Dificultad::Dificultad(int nivelJedi, bool esModoJedi) {
    modoJedi = esModoJedi;
    nivel = nivelJedi;
    if (!modoJedi) return;
    switch (nivelJedi) {
    case 1: // Fácil
        velBolaJedi = 25.0f;
        frecuenciaPowerUps = 0.08f;
        factorAprendizaje = 0.5f;
        tiempoLimite = 120;
        break;
    case 2: // Normal
        velBolaJedi = 32.0f;
        frecuenciaPowerUps = 0.06f;
        factorAprendizaje = 1.0f;
        tiempoLimite = 90;
        break;
    case 3: // Difícil
        velBolaJedi = 40.0f;
        frecuenciaPowerUps = 0.04f;
        factorAprendizaje = 1.5f;
        tiempoLimite = 75;
        break;
    default: throw std::invalid_argument("Nivel Jedi inválido");
    }
}

float Dificultad::getVelObstaculo() const { return velObstaculo; }
float Dificultad::getVelBola() const { return velBola; }
float Dificultad::getVelEnemigo() const { return velEnemigo; }
float Dificultad::getMargenError() const { return margenError; }
int Dificultad::getGamesParaGanar() const { return gamesParaGanar; }
int Dificultad::getNivel() const { return nivel; }

float Dificultad::getVelBolaJedi() const { return velBolaJedi; }
float Dificultad::getFrecuenciaPowerUps() const { return frecuenciaPowerUps; }
float Dificultad::getFactorAprendizaje() const { return factorAprendizaje; }
int Dificultad::getTiempoLimite() const { return tiempoLimite; }

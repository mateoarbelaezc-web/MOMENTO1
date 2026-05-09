#include "dificultad.h"

#include "dificultad.h"
#include <stdexcept>

Dificultad::Dificultad(int nivel) {
    if (nivel != 1 && nivel != 2)
        throw std::invalid_argument("Nivel de dificultad invalido. Use 1 (facil) o 2 (dificil).");

    this->nivel = nivel;

    if (nivel == 1) {
        velBola = 5.0f;
        velEnemigo = 3.0f;
        margenError = 80.0f;
        gamesParaGanar = 3;
        velObstaculo = 3.0f;
    } else {
        velBola = 6.5f;
        velEnemigo = 5.0f;
        margenError = 20.0f;
        gamesParaGanar = 6;
        velObstaculo = 7.0f;
    }
}

float Dificultad::getVelObstaculo() const { return velObstaculo; }
float Dificultad::getVelBola() const { return velBola; }
float Dificultad::getVelEnemigo() const { return velEnemigo; }
float Dificultad::getMargenError() const { return margenError; }
int Dificultad::getGamesParaGanar() const { return gamesParaGanar; }
int Dificultad::getNivel() const { return nivel; }

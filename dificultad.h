#ifndef DIFICULTAD_H
#define DIFICULTAD_H

class Dificultad {
public:
    Dificultad(int nivel);

    float getVelBola() const;
    float getVelEnemigo() const;
    float getMargenError() const;
    float getVelObstaculo() const;
    int getGamesParaGanar() const;
    int getNivel() const;

private:
    int nivel;
    float velBola;
    float velEnemigo;
    float margenError;
    int gamesParaGanar;
    float velObstaculo;
};

#endif

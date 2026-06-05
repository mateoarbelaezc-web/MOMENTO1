#ifndef DIFICULTAD_H
#define DIFICULTAD_H

class Dificultad {
public:
    Dificultad(int nivel);
    Dificultad(int nivelJedi, bool esModoJedi);

    // Tenis
    float getVelBola() const;
    float getVelEnemigo() const;
    float getMargenError() const;
    float getVelObstaculo() const;
    int getGamesParaGanar() const;
    int getNivel() const;

    // Jedi
    float getVelBolaJedi() const;
    float getFrecuenciaPowerUps() const;
    float getFactorAprendizaje() const;
    int getTiempoLimite() const;

private:
    int nivel;
    bool modoJedi;
    // Tenis
    float velBola, velEnemigo, margenError, velObstaculo;
    int gamesParaGanar;
    // Jedi
    float velBolaJedi, frecuenciaPowerUps, factorAprendizaje;
    int tiempoLimite;
};

#endif

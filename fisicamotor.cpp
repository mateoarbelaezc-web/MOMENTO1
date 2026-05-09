#include "fisicamotor.h"
#include <cmath>

FisicaMotor::FisicaMotor() {}

void FisicaMotor::aplicarAnguloImpacto(Pelota* pelota, float yNave, float altoNave) {
    float puntoImpacto = (pelota->y() - yNave) / altoNave;
    puntoImpacto = qBound(-1.0f, puntoImpacto, 1.0f);

    float velocidad = 6.5f; // velocidad fija siempre

    float angulo = puntoImpacto * 60.0f * M_PI / 180.0f;

    float dirX = (pelota->getVelX() > 0) ? 1.0f : -1.0f;
    pelota->setVelX(dirX * velocidad * cos(angulo));
    pelota->setVelY(velocidad * sin(angulo));
}

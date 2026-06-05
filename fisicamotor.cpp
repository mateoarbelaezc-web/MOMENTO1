#include "fisicamotor.h"
#include <cmath>

FisicaMotor::FisicaMotor() {}

void FisicaMotor::aplicarAnguloImpacto(Pelota* pelota, float yNave, float altoNave, float velocidad) {
    float puntoImpacto = (pelota->y() - yNave) / altoNave;
    puntoImpacto = qBound(-0.8f, puntoImpacto, 0.8f);
    float angulo = puntoImpacto * 45.0f * M_PI / 180.0f;
    float dirX = (pelota->getVelX() > 0) ? 1.0f : -1.0f;
    pelota->setVelX(dirX * velocidad * cos(angulo));
    pelota->setVelY(velocidad * sin(angulo));
}

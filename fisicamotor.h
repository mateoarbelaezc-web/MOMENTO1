#ifndef FISICAMOTOR_H
#define FISICAMOTOR_H

#include "pelota.h"

class FisicaMotor {
public:
    FisicaMotor();
    void aplicarAnguloImpacto(Pelota* pelota, float yNave, float altoNave, float velocidad);
};

#endif

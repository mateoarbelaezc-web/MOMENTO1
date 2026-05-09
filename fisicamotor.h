#ifndef FISICAMOTOR_H
#define FISICAMOTOR_H

#include "pelota.h"
#include "naverebelde.h"
#include "naveimperial.h"

class FisicaMotor {
public:
    FisicaMotor();
    void aplicarAnguloImpacto(Pelota* pelota, float yNave, float altoNave);
};

#endif

#ifndef MOTORFISICA_H
#define MOTORFISICA_H

#include "Bola.h"
#include "Vector2D.h"

class MotorFisica
{
public:
    MotorFisica(double gravedad = 9.8);

    void setGravedad(double g);

    // Aplica las leyes del movimiento parabólico
    void actualizarMovimiento(Bola *bola, double dt);

private:
    double gravedad;
};

#endif // MOTORFISICA_H
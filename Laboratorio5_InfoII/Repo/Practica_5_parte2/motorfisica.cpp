#include "MotorFisica.h"

MotorFisica::MotorFisica(double gravedad)
    : gravedad(gravedad)
{
}

void MotorFisica::setGravedad(double g)
{
    gravedad = g;
}

void MotorFisica::actualizarMovimiento(Bola *bola, double dt)
{
    if (!bola) return;

    Vector2D v = bola->obtenerVelocidad();

    // Aceleración debido a la gravedad (apunta hacia abajo, Y positivo)
    // Velocidad final = Velocidad inicial + aceleracion * tiempo
    v.y += gravedad * dt;

    bola->establecerVelocidad(v);

    // Posición final = Posición inicial + velocidad * tiempo
    double nuevaX = bola->getX() + v.x * dt;
    double nuevaY = bola->getY() + v.y * dt;

    bola->setX(nuevaX);
    bola->setY(nuevaY);
}
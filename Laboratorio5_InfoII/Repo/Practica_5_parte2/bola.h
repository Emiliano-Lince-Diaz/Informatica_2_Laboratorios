#ifndef BOLA_H
#define BOLA_H

#include "Entidad.h"
#include "Vector2D.h"

// Representa el proyectil disparado en el juego
class Bola : public Entidad
{
public:
    Bola(double x, double y, double radio, double masa, const QColor &color);

    double getRadio() const;
    double getMasa() const;

    Vector2D obtenerVelocidad() const;
    void establecerVelocidad(const Vector2D &v);

    // Implementación del método virtual puro de Entidad
    void dibujar(QPainter *painter) const override;

private:
    double radio;
    double masa;
    Vector2D velocidad;
};

#endif // BOLA_H
#ifndef CANON_H
#define CANON_H

#include "Entidad.h"

class Canon : public Entidad
{
public:
    Canon(double x, double y, double longitud, const QColor &color);

    void setAngulo(double grados);
    double getAngulo() const;

    void dibujar(QPainter *painter) const override;

private:
    double longitud; // Longitud del cañón
    double angulo;   // Ángulo de inclinación en grados
};

#endif // CANON_H
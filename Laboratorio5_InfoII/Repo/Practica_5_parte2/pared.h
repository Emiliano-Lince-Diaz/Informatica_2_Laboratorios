#ifndef PARED_H
#define PARED_H

#include "Entidad.h"
#include <QRectF>

class Pared : public Entidad
{
public:
    Pared(double x, double y, double ancho, double alto, const QColor &color);

    QRectF obtenerLimites() const;
    void dibujar(QPainter *painter) const override;

private:
    double ancho;
    double alto;
};

#endif // PARED_H
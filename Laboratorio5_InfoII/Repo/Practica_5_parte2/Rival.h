#ifndef RIVAL_H
#define RIVAL_H

#include "Entidad.h"
#include <QRectF>

class Rival : public Entidad
{
public:
    Rival(double x, double y, double ancho, double alto, const QColor &color);

    QRectF obtenerLimites() const;
    void dibujar(QPainter *painter) const override;

private:
    double ancho;
    double alto;
};

#endif // RIVAL_H
#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"
#include <QString>
#include <QRectF>

class Jugador : public Entidad
{
public:
    Jugador(double x, double y, double tamano, const QString &nombre, const QColor &color);

    QString getNombre() const;
    QRectF obtenerLimites() const;

    void dibujar(QPainter *painter) const override;

private:
    double tamano; // Asumiremos que el jugador es un cuadrado simple por ahora
    QString nombre;
};

#endif // JUGADOR_H
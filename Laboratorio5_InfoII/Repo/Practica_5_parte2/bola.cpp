#include "Bola.h"
#include <QPen>
#include <QBrush>
#include <QPointF>

Bola::Bola(double x, double y, double radio, double masa, const QColor &color)
    : Entidad(x, y, color), radio(radio), masa(masa), velocidad(0.0, 0.0)
{
}

double Bola::getRadio() const
{
    return radio;
}

double Bola::getMasa() const
{
    return masa;
}

Vector2D Bola::obtenerVelocidad() const
{
    return velocidad;
}

void Bola::establecerVelocidad(const Vector2D &v)
{
    velocidad = v;
}

void Bola::dibujar(QPainter *painter) const
{
    // Dibuja la bola (proyectil) como un círculo relleno
    painter->setPen(QPen(Qt::black, 1.5)); // Borde negro
    painter->setBrush(QBrush(color));      // Relleno del color de la entidad

    // El método drawEllipse de Qt toma el centro y los radios X e Y
    painter->drawEllipse(QPointF(x, y), radio, radio);
}
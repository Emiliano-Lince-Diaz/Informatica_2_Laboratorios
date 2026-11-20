#include "Canon.h"
#include <QPen>
#include <QBrush>
#include <cmath>

Canon::Canon(double x, double y, double longitud, const QColor &color)
    : Entidad(x, y, color), longitud(longitud), angulo(45.0) // 45 grados por defecto
{
}

void Canon::setAngulo(double grados)
{
    angulo = grados;
}

double Canon::getAngulo() const
{
    return angulo;
}

void Canon::dibujar(QPainter *painter) const
{
    painter->setRenderHint(QPainter::Antialiasing);

    // Guardar el estado del pintor para rotaciones
    painter->save();

    // Mover el origen de coordenadas a la base del cañón
    painter->translate(x, y);

    // Rotar según el ángulo (negativo porque en Qt el eje Y crece hacia abajo)
    painter->rotate(-angulo);

    // 1. Dibujar el tubo del cañón como una línea gruesa (o rectángulo)
    painter->setPen(QPen(Qt::darkGray, 10.0, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, longitud, 0);

    // Restaurar transformación antes de dibujar la base
    painter->restore();

    // 2. Dibujar la base del cañón como un círculo simple
    painter->setPen(QPen(Qt::black, 2.0));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(QPointF(x, y), 15.0, 15.0); // Radio fijo para la base
}
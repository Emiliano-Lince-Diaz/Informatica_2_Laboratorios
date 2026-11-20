#include "Pared.h"
#include <QPen>
#include <QBrush>

Pared::Pared(double x, double y, double ancho, double alto, const QColor &color)
    : Entidad(x, y, color), ancho(ancho), alto(alto)
{
}

QRectF Pared::obtenerLimites() const
{
    return QRectF(x, y, ancho, alto);
}

void Pared::dibujar(QPainter *painter) const
{
    // Dibuja la pared como un rectángulo simple
    painter->setPen(QPen(Qt::black, 2.0));
    painter->setBrush(QBrush(color));
    painter->drawRect(obtenerLimites());
}
#include "Rival.h"
#include <QPen>
#include <QBrush>

Rival::Rival(double x, double y, double ancho, double alto, const QColor &color)
    : Entidad(x, y, color), ancho(ancho), alto(alto)
{
}

QRectF Rival::obtenerLimites() const
{
    return QRectF(x, y, ancho, alto);
}

void Rival::dibujar(QPainter *painter) const
{
    // Dibuja al rival como un bloque (puedes cambiarlo por una imagen o forma más compleja luego)
    painter->setPen(QPen(Qt::black, 2.0));
    painter->setBrush(QBrush(color));
    painter->drawRect(obtenerLimites());
}
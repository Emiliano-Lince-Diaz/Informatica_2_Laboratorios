#include "Jugador.h"
#include <QPen>
#include <QBrush>

Jugador::Jugador(double x, double y, double tamano, const QString &nombre, const QColor &color)
    : Entidad(x, y, color), tamano(tamano), nombre(nombre)
{
}

QString Jugador::getNombre() const
{
    return nombre;
}

QRectF Jugador::obtenerLimites() const
{
    // Centramos el cuadrado en (x,y)
    return QRectF(x - tamano/2.0, y - tamano/2.0, tamano, tamano);
}

void Jugador::dibujar(QPainter *painter) const
{
    // Representamos al jugador como un cuadrado simple
    painter->setPen(QPen(Qt::black, 2.0));
    painter->setBrush(QBrush(color));

    QRectF limites = obtenerLimites();
    painter->drawRect(limites);

    // Dibujar el nombre arriba del jugador
    painter->setPen(Qt::black);
    painter->drawText(QRectF(x - 50, y - tamano/2.0 - 20, 100, 20),
                      Qt::AlignCenter, nombre);
}
#include "Entidad.h"

Entidad::Entidad(double x, double y, const QColor &color)
    : x(x), y(y), color(color)
{
}

double Entidad::getX() const
{
    return x;
}

double Entidad::getY() const
{
    return y;
}

QColor Entidad::getColor() const
{
    return color;
}

void Entidad::setX(double newX)
{
    x = newX;
}

void Entidad::setY(double newY)
{
    y = newY;
}

void Entidad::setColor(const QColor &newColor)
{
    color = newColor;
}
#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QColor>
#include <QPainter>

// Clase base abstracta para todos los objetos del juego
class Entidad
{
public:
    Entidad(double x, double y, const QColor &color);
    virtual ~Entidad() = default;

    // Método virtual puro: cada clase hija (Bola, Pared, etc.) debe saber cómo dibujarse
    virtual void dibujar(QPainter *painter) const = 0;

    // Getters
    double getX() const;
    double getY() const;
    QColor getColor() const;

    // Setters
    void setX(double newX);
    void setY(double newY);
    void setColor(const QColor &newColor);

protected:
    // Posición en el mundo 2D
    double x;
    double y;
    QColor color;
};

#endif // ENTIDAD_H

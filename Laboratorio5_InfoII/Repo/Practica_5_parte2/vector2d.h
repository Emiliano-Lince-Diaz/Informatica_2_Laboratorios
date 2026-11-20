#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    double x;
    double y;

    Vector2D();
    Vector2D(double x, double y);

    // Operaciones matemáticas necesarias para el motor de física y colisiones
    double magnitud() const;
    double productoPunto(const Vector2D& otro) const;

    // Sobrecarga de operadores básicos para facilitar cálculos
    Vector2D operator+(const Vector2D& otro) const;
    Vector2D operator-(const Vector2D& otro) const;
    Vector2D operator*(double escalar) const;
};

#endif // VECTOR2D_H
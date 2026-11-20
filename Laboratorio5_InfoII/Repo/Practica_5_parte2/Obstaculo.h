#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Entidad.h"
#include <QRectF>

class Obstaculo : public Entidad
{
public:
    Obstaculo(double x, double y, double ancho, double alto,
              double resistencia, const QColor &color);

    QRectF obtenerLimites() const;          // (x, y) = esquina superior izquierda
    double getResistencia() const;
    double getResistenciaInicial() const;
    bool estaDestruido() const;
    void recibirDanio(double danio);

    void dibujar(QPainter *painter) const override;

private:
    double ancho;
    double alto;
    double resistencia;
    double resistenciaInicial;
};

#endif // OBSTACULO_H
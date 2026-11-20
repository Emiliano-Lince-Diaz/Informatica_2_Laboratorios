#include "Obstaculo.h"
#include <QPen>
#include <QString>
#include <QtGlobal>

Obstaculo::Obstaculo(double x, double y, double ancho, double alto,
                     double resistencia, const QColor &color)
    : Entidad(x, y, color), ancho(ancho), alto(alto),
    resistencia(resistencia), resistenciaInicial(resistencia)
{
}

QRectF Obstaculo::obtenerLimites() const { return QRectF(x, y, ancho, alto); }
double Obstaculo::getResistencia() const { return resistencia; }
double Obstaculo::getResistenciaInicial() const { return resistenciaInicial; }
bool Obstaculo::estaDestruido() const { return resistencia <= 0.0; }

void Obstaculo::recibirDanio(double danio)
{
    resistencia -= danio;
    if (resistencia < 0.0)
        resistencia = 0.0;
}

void Obstaculo::dibujar(QPainter *painter) const
{
    if (estaDestruido())
        return;                              // un bloque destruido desaparece

    painter->setPen(QPen(Qt::black, 1.5));
    painter->setBrush(color);
    painter->drawRect(obtenerLimites());
    painter->drawText(obtenerLimites(), Qt::AlignCenter,
                      QString::number(qRound(resistencia)));   // muestra la resistencia
}
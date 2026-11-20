#ifndef RESOLUTORCOLISIONES_H
#define RESOLUTORCOLISIONES_H

#include "Bola.h"
#include "Obstaculo.h"
#include "Rival.h"

struct ResultadoImpacto {
    bool hubo = false;           // ¿hubo choque?
    double rapidezImpacto = 0.0; // |v| justo antes del rebote
    double danio = 0.0;          // daño aplicado al obstáculo
    bool destruido = false;      // ¿el obstáculo quedó en resistencia 0?
};

class ResolutorColisiones
{
public:
    explicit ResolutorColisiones(double coefRestitucion = 0.7,
                                 double factorDanio = 0.1);

    bool resolverPared(Bola *bola, double ancho, double alto);
    ResultadoImpacto resolverProyectilObstaculo(Bola *proyectil, Obstaculo *obstaculo,
                                                bool aplicarDanio = true);
    bool tocaRival(const Bola *proyectil, const Rival *rival) const;
    double calcularDanio(double masa, double rapidez) const;

private:
    double coefRestitucion;   // e de los obstáculos
    double factorDanio;       // la constante k de la fórmula del daño
};

#endif // RESOLUTORCOLISIONES_H
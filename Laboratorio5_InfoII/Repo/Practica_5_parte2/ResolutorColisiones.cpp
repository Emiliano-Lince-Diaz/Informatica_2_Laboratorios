#include "ResolutorColisiones.h"
#include <QtGlobal>
#include <cmath>
#include <algorithm>

ResolutorColisiones::ResolutorColisiones(double coefRestitucion, double factorDanio)
    : coefRestitucion(coefRestitucion), factorDanio(factorDanio)
{
}

// Daño = factor constante × masa × |v_impacto|
double ResolutorColisiones::calcularDanio(double masa, double rapidez) const
{
    return factorDanio * masa * rapidez;
}

// Límites del escenario: perfectamente elásticas (igual que la parte 1)
bool ResolutorColisiones::resolverPared(Bola *bola, double ancho, double alto)
{
    bool choco = false;
    const double r = bola->getRadio();
    Vector2D v = bola->obtenerVelocidad();

    if (bola->getX() - r < 0.0)        { bola->setX(r);         v.x =  std::fabs(v.x); choco = true; }
    else if (bola->getX() + r > ancho) { bola->setX(ancho - r); v.x = -std::fabs(v.x); choco = true; }

    if (bola->getY() - r < 0.0)        { bola->setY(r);         v.y =  std::fabs(v.y); choco = true; }
    else if (bola->getY() + r > alto)  { bola->setY(alto - r);  v.y = -std::fabs(v.y); choco = true; }

    bola->establecerVelocidad(v);
    return choco;
}

// Infraestructura: inelástica con restitución + daño proporcional al momento lineal
ResultadoImpacto ResolutorColisiones::resolverProyectilObstaculo(Bola *bola,
                                                                 Obstaculo *obstaculo,
                                                                 bool aplicarDanio)
{
    ResultadoImpacto res;
    if (obstaculo->estaDestruido())
        return res;                                   // un bloque destruido no choca

    const QRectF lim = obstaculo->obtenerLimites();
    const double r = bola->getRadio();
    const double bx = bola->getX();
    const double by = bola->getY();

    // 1. Punto del rectángulo más cercano al centro de la bola
    const double cx = qBound(lim.left(), bx, lim.right());
    const double cy = qBound(lim.top(), by, lim.bottom());
    const double dx = bx - cx;
    const double dy = by - cy;
    const double dist = std::sqrt(dx * dx + dy * dy);
    if (dist >= r)
        return res;                                   // no hay contacto

    // Normal y cuánto hay que empujar la bola hacia afuera
    Vector2D n;
    double empuje;
    if (dist > 1e-9) {
        n = Vector2D(dx / dist, dy / dist);
        empuje = r - dist;
    } else {
        const double izq = bx - lim.left();
        const double der = lim.right() - bx;
        const double arr = by - lim.top();
        const double aba = lim.bottom() - by;
        const double m = std::min(std::min(izq, der), std::min(arr, aba));
        if (m == izq)      n = Vector2D(-1.0, 0.0);
        else if (m == der) n = Vector2D(1.0, 0.0);
        else if (m == arr) n = Vector2D(0.0, -1.0);
        else               n = Vector2D(0.0, 1.0);
        empuje = m + r;
    }
    bola->setX(bx + n.x * empuje);
    bola->setY(by + n.y * empuje);

    // Lado golpeado: el eje dominante de la normal
    Vector2D nLado;
    if (std::fabs(n.x) >= std::fabs(n.y))
        nLado = Vector2D(n.x > 0 ? 1.0 : -1.0, 0.0);   // lado derecho o izquierdo
    else
        nLado = Vector2D(0.0, n.y > 0 ? 1.0 : -1.0);   // lado inferior o superior

    // Solo hay rebote y daño si el proyectil venía hacia el bloque
    const Vector2D v = bola->obtenerVelocidad();
    const double vn = v.productoPunto(nLado);
    if (vn >= 0.0)
        return res;

    res.hubo = true;
    res.rapidezImpacto = v.magnitud();                 // |v_impacto| antes de rebotar

    // Rebote: v' = v∥ − e·v⊥
    const Vector2D vPerp(nLado.x * vn, nLado.y * vn);
    const Vector2D vPar(v.x - vPerp.x, v.y - vPerp.y);
    bola->establecerVelocidad(Vector2D(vPar.x - coefRestitucion * vPerp.x,
                                       vPar.y - coefRestitucion * vPerp.y));

    // Daño a la resistencia
    if (aplicarDanio) {
        res.danio = calcularDanio(bola->getMasa(), res.rapidezImpacto);
        obstaculo->recibirDanio(res.danio);
        res.destruido = obstaculo->estaDestruido();
    }
    return res;
}

// El proyectil alcanza al representante enemigo (no rebota: se acaba el juego)
bool ResolutorColisiones::tocaRival(const Bola *bola, const Rival *rival) const
{
    const QRectF lim = rival->obtenerLimites();
    const double cx = qBound(lim.left(), bola->getX(), lim.right());
    const double cy = qBound(lim.top(), bola->getY(), lim.bottom());
    const double dx = bola->getX() - cx;
    const double dy = bola->getY() - cy;
    return (dx * dx + dy * dy) < bola->getRadio() * bola->getRadio();
}
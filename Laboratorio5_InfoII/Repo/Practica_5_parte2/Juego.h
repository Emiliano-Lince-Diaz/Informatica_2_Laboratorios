#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <QPainter>
#include "Bola.h"
#include "Canon.h"
#include "Jugador.h"
#include "Pared.h"
#include "Obstaculo.h"
#include "Rival.h"
#include "MotorFisica.h"
#include "ResolutorColisiones.h"

class Juego
{
public:
    Juego();
    ~Juego();

    void inicializarJuego();
    void actualizarMundo(double dt);
    void dibujarMundo(QPainter *painter);
    void dispararCanon(double fuerza);
    void setAnguloCanon(double grados);
    void disparar(double fuerza);

private:
    int estadoJuego; // 0 = Jugando, 1 = Victoria

    // Entidades principales
    Jugador* jugador;
    Canon* canon;
    Bola* proyectil;
    Rival* rival;

    // Colecciones de entidades
    std::vector<Obstaculo*> obstaculos;
    std::vector<Pared*> paredes;

    // Sistemas
    MotorFisica motor;
    ResolutorColisiones resolutor;
};

#endif // JUEGO_H

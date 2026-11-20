#include "Juego.h"
#include <cmath>

Juego::Juego() : jugador(nullptr), canon(nullptr), proyectil(nullptr), rival(nullptr), estadoJuego(0)
{
    // Configurar sistemas
    motor.setGravedad(800.0); // <--- CAMBIAR AQUÍ: 800.0 en lugar de 9.8
    resolutor = ResolutorColisiones(0.6, 0.5); // Restitución y factor de daño

    inicializarJuego();
}

Juego::~Juego()
{
    delete jugador;
    delete canon;
    delete proyectil;
    delete rival;
    for (auto p : paredes) delete p;
    for (auto o : obstaculos) delete o;
}

void Juego::inicializarJuego()
{
    // Limpiar estado previo
    if (proyectil) { delete proyectil; proyectil = nullptr; }
    obstaculos.clear();
    paredes.clear();

    // Crear Entidades (Simulando un nivel)
    jugador = new Jugador(100, 500, 40, "Player 1", Qt::blue);
    canon = new Canon(120, 480, 50, Qt::darkGreen);
    canon->setAngulo(45.0);

    rival = new Rival(700, 480, 40, 40, Qt::red);

    // Suelo y bordes
    paredes.push_back(new Pared(0, 520, 800, 80, Qt::darkGray));

    // Obstáculos tipo castillo
    obstaculos.push_back(new Obstaculo(600, 420, 30, 100, 100.0, Qt::darkYellow));
    obstaculos.push_back(new Obstaculo(650, 480, 30, 40, 50.0, Qt::darkYellow));
}

void Juego::dispararCanon(double fuerza)
{
    if (proyectil) delete proyectil;

    // Convertir ángulo a radianes para calcular el vector inicial
    double anguloRad = canon->getAngulo() * 3.14159 / 180.0;

    proyectil = new Bola(canon->getX(), canon->getY() - 20, 10, 5.0, Qt::black);

    // Eje Y en Qt es invertido (crece hacia abajo), por lo que restamos en Y
    proyectil->establecerVelocidad(Vector2D(fuerza * std::cos(anguloRad), -fuerza * std::sin(anguloRad)));
}

void Juego::actualizarMundo(double dt)
{
    if (estadoJuego != 0) return; // Si ya ganó, detener lógica

    if (proyectil) {
        // 1. Aplicar Gravedad y Movimiento
        motor.actualizarMovimiento(proyectil, dt);

        // 2. ¡NUEVO!: Comprobar si toca el suelo (520). Si es así, se destruye.
        if (proyectil->getY() + proyectil->getRadio() >= 520.0) {
            delete proyectil;
            proyectil = nullptr;
            return; // Salimos de la función inmediatamente para evitar errores
        }

        // 3. Colisiones con las otras paredes (laterales y techo).
        // Le pasamos un alto muy grande (2000) para que el resolutor ya no
        // intercepte la bola por abajo, ya que lo hicimos manualmente arriba.
        resolutor.resolverPared(proyectil, 800, 2000);

        // 4. Colisiones con Obstáculos Destructibles
        for (auto obs : obstaculos) {
            resolutor.resolverProyectilObstaculo(proyectil, obs, true);
        }

        // 5. Colisión final con el Rival
        if (resolutor.tocaRival(proyectil, rival)) {
            estadoJuego = 1; // ¡Victoria!
        }
    }
}

void Juego::dibujarMundo(QPainter *painter)
{
    for (auto p : paredes) p->dibujar(painter);
    for (auto o : obstaculos) o->dibujar(painter);

    if (rival) rival->dibujar(painter);
    if (jugador) jugador->dibujar(painter);
    if (canon) canon->dibujar(painter);
    if (proyectil) proyectil->dibujar(painter);

    // Dibujar texto de estado si hay victoria
    if (estadoJuego == 1) {
        painter->setPen(Qt::black);
        QFont font = painter->font();
        font.setPointSize(24);
        painter->setFont(font);
        painter->drawText(300, 200, "¡VICTORIA!");
    }
}

void Juego::setAnguloCanon(double grados) {
    if (canon != nullptr) {
        canon->setAngulo(grados); // Asumiendo que tu Canon tiene un método setAngulo
    }
}

// Cambia la implementación de la función así:
void Juego::disparar(double fuerza) {
    if (canon != nullptr) {
        if (proyectil != nullptr) {
            delete proyectil;
            proyectil = nullptr;
        }

        double anguloRad = canon->getAngulo() * (M_PI / 180.0);

        // USAMOS LA FUERZA QUE PASAMOS POR PARÁMETRO
        double vx = fuerza * std::cos(anguloRad);
        double vy = -fuerza * std::sin(anguloRad);

        proyectil = new Bola(canon->getX(), canon->getY(), 5.0, 1.0, QColor(Qt::red));
        proyectil->establecerVelocidad(Vector2D(vx, vy));
    }
}
#include "VentanaJuego.h"
#include <QPainter>
#include <cmath>

VentanaJuego::VentanaJuego(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    setFixedSize(800, 600); // Tamaño fijo de la ventana

    juego = new Juego();

    // QTimer se encarga del bucle principal del juego (Game Loop)
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VentanaJuego::actualizarFrame);
    timer->start(16); // Aproximadamente 60 FPS (1000ms / 60 = 16.6ms)
}

VentanaJuego::~VentanaJuego()
{
    delete juego;
}

void VentanaJuego::actualizarFrame()
{
    // Si estamos presionando el click, la fuerza aumenta
    if (cargandoDisparo) {
        fuerzaDisparo += 15.0; // Qué tan rápido carga
        if (fuerzaDisparo > 1200.0) fuerzaDisparo = 1200.0; // Límite máximo
    }

    juego->actualizarMundo(0.016);
    update();
}

void VentanaJuego::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Pintar fondo del cielo
    painter.fillRect(rect(), QColor(135, 206, 235));

    // Delegar todo el dibujo al controlador del juego
    juego->dibujarMundo(&painter);

    // --- DIBUJAR LA BARRA DE ENERGÍA ---
    if (cargandoDisparo) {
        painter.setBrush(Qt::red);
        painter.setPen(Qt::black);
        // Dibuja un rectángulo que crece según la fuerza (dividido por 5 para que quepa en pantalla)
        painter.drawRect(20, 25, fuerzaDisparo / 5, 15);

        // Texto de potencia
        painter.setPen(Qt::black);
        painter.drawText(20, 20, "Potencia de disparo:");
    }
}

void VentanaJuego::keyPressEvent(QKeyEvent *event)
{
    // Controles básicos del teclado (opcional, puedes borrarlo si solo usarás mouse)
    if (event->key() == Qt::Key_Space) {
        juego->dispararCanon(120.0); // Disparo antiguo de prueba
    }
}

void VentanaJuego::mouseMoveEvent(QMouseEvent *event) {
    double canonX = 50.0;
    double canonY = height() - 50.0;

    // Calculamos las diferencias
    double dx = event->position().x() - canonX;
    double dy = event->position().y() - canonY;

    // Calculamos el ángulo original
    double anguloRadianes = std::atan2(dy, dx);
    double anguloGrados = anguloRadianes * (180.0 / M_PI);

    // Invertir el ángulo para el sistema de coordenadas de Qt
    anguloGrados = -anguloGrados;

    if (juego != nullptr) {
        juego->setAnguloCanon(anguloGrados);
    }

    update();
}

void VentanaJuego::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        cargandoDisparo = true;      // Empezar a cargar
        fuerzaDisparo = 100.0;       // Reiniciar la fuerza al mínimo (100)
    }
}

void VentanaJuego::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && cargandoDisparo) {
        cargandoDisparo = false;     // Soltamos el botón

        if (juego != nullptr) {
            juego->disparar(fuerzaDisparo); // Disparar con la fuerza acumulada
        }
    }
}
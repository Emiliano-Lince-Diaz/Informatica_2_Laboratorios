#include <QApplication>
#include "VentanaJuego.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Crear y mostrar la ventana principal del juego
    VentanaJuego ventana;
    ventana.setWindowTitle("Simulador de Física - Práctica 5");
    ventana.show();

    return app.exec();
}
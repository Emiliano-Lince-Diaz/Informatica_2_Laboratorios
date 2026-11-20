#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Ajustar el tamaño de la ventana principal
    setFixedSize(800, 600);
    setWindowTitle("Simulador de Física - Práctica 5 (MainWindow)");

    // Instanciar nuestro widget del juego
    juegoWidget = new VentanaJuego(this);

    // Establecer el widget del juego como el componente central de la ventana
    setCentralWidget(juegoWidget);
}

MainWindow::~MainWindow()
{
    // Qt se encarga de eliminar juegoWidget automáticamente al ser su "parent",
    // pero si lo eliminas manualmente asegúrate de no causar un double-free.
}
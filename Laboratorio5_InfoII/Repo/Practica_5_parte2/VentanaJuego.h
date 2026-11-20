#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include "Juego.h"

class VentanaJuego : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaJuego(QWidget *parent = nullptr);
    ~VentanaJuego();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Juego *juego;
    QTimer *timer;

    // Variables para la potencia del disparo con el ratón
    bool cargandoDisparo = false;
    double fuerzaDisparo = 100.0;

private slots:
    void actualizarFrame();
};

#endif // VENTANAJUEGO_H
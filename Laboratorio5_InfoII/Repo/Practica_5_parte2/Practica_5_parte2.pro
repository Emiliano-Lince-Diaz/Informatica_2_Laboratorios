QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entidad.cpp \
    Juego.cpp \
    Obstaculo.cpp \
    ResolutorColisiones.cpp \
    Rival.cpp \
    VentanaJuego.cpp \
    bola.cpp \
    canon.cpp \
    jugador.cpp \
    main.cpp \
    mainwindow.cpp \
    motorfisica.cpp \
    pared.cpp \
    vector2d.cpp

HEADERS += \
    Entidad.h \
    Juego.h \
    Obstaculo.h \
    ResolutorColisiones.h \
    Rival.h \
    VentanaJuego.h \
    bola.h \
    canon.h \
    jugador.h \
    mainwindow.h \
    motorfisica.h \
    pared.h \
    vector2d.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        interfaz.cpp \
        creadorTopologia.cpp \
        enrutador.cpp \
        red.cpp

HEADERS += \
        interfaz.h \
        creadorTopologia.h \
        enrutador.h \
        red.h

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        RLE.cpp \
        lz78.cpp \
        main.cpp \
        menu.cpp

HEADERS += \
    RLE.h \
    lz78.h \
    menu.h

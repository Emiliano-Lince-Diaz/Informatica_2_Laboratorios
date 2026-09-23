#include "menu.h"
#include "RLE.h"
#include "lz78.h"
#include <iostream>
#include <limits> // Necesario para std::numeric_limits

using namespace std;

namespace Menu {

// Función con bucle de validación estricto
int leerOpcion(int minOpcion, int maxOpcion) {
    int opcion;
    while (true) {
        cout << "\nSeleccione una opcion (" << minOpcion << " - " << maxOpcion << "): ";

        // Intenta leer un entero
        if (cin >> opcion) {
            // Verifica que esté dentro del rango permitido
            if (opcion >= minOpcion && opcion <= maxOpcion) {
                return opcion; // Entrada válida
            } else {
                cout << "[ERROR] Opcion fuera de rango. Por favor intente de nuevo.\n";
            }
        } else {
            // Captura cuando el usuario ingresa texto/letras o caracteres no numéricos
            cout << "[ERROR] Entrada invalida. Debe ingresar un numero entero.\n";
            cin.clear(); // Limpia la bandera de error de std::cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta el texto inválido del buffer
        }
    }
}

void mostrarMenuPruebas() {
    bool enSubmenu = true;

    while (enSubmenu) {
        cout << "\n========================================\n";
        cout << "          MENU DE PRUEBAS               \n";
        cout << "========================================\n";
        cout << "1. Probar Algoritmo RLE (Dia 1)\n";
        cout << "2. Probar Diccionario LZ78 (Dia 2)\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "========================================\n";

        int opcion = leerOpcion(0, 2);

        switch (opcion) {
        case 1: {
            cout << "\n--- EJECUTANDO PRUEBA RLE ---\n";
            string textoPrueba = "AAAABBBCC";
            string comp = RLE::compress(textoPrueba);
            string decomp = RLE::decompress(comp);
            cout << "Texto original:    " << textoPrueba << "\n";
            cout << "Texto comprimido:  " << comp << "\n";
            cout << "Texto recuperado:  " << decomp << "\n";
            cout << "Estado: " << (textoPrueba == decomp ? "[CORRECTO]" : "[ERROR]") << "\n";
            break;
        }
        case 2: {
            cout << "\n--- EJECUTANDO PRUEBA DICCIONARIO LZ78 ---\n";
            Dictionary dict(2);
            dict.insert(0, 'A');
            dict.insert(0, 'B');
            dict.insert(1, 'A');
            dict.insert(2, 'A');
            cout << "Entradas insertadas correctamente. Tamano actual: " << dict.size << "\n";
            cout << "Busqueda de (1, 'A'): Indice " << dict.find(1, 'A') << " (Esperado: 3)\n";
            break;
        }
        case 0:
            enSubmenu = false;
            break;
        }
    }
}

void mostrarMenuPrincipal() {
    bool ejecutando = true;

    while (ejecutando) {
        cout << "\n========================================\n";
        cout << "       SISTEMA PRINCIPAL C++            \n";
        cout << "========================================\n";
        cout << "1. Seccion de Pruebas\n";
        cout << "0. Salir\n";
        cout << "========================================\n";

        int opcion = leerOpcion(0, 1);

        switch (opcion) {
        case 1:
            mostrarMenuPruebas();
            break;
        case 0:
            cout << "\nSaliendo del programa... ¡Hasta luego!\n";
            ejecutando = false;
            break;
        }
    }
}
}
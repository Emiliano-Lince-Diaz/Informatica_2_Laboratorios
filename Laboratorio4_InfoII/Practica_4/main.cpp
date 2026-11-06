#include "Red.h"
#include <iostream>
#include <string>

using namespace std;

static string leer(const string& msg) {
    cout << msg;
    string s;
    getline(cin, s);
    return s;
}

static int leerEntero(const string& msg) {
    string s = leer(msg);
    try {
        return stoi(s);
    } catch (...) {
        return -1;
    }
}

static void menu() {
    cout << "\n===== SIMULADOR DE RED DE ENRUTADORES =====\n"
         << "1. Cargar topologia desde archivo\n"
         << "2. Agregar enrutador\n"
         << "3. Eliminar enrutador\n"
         << "4. Agregar / modificar enlace\n"
         << "5. Eliminar enlace\n"
         << "6. Mostrar tablas de costos\n"
         << "7. Mostrar caminos completos\n"
         << "8. Consultar camino entre dos enrutadores\n"
         << "9. Mostrar enlaces directos\n"
         << "0. Salir\n";
}

int main() {
    Red red;
    bool salir = false;

    while (!salir && cin) {
        menu();
        int op = leerEntero("Opcion: ");
        switch (op) {
        case 1: {
            string ruta = leer("Ruta del archivo: ");
            if (red.cargarTopologia(ruta)) {
                cout << "Topologia cargada.\n";
                red.imprimirTablas();
            } else {
                cout << "No se pudo abrir el archivo.\n";
            }
            break;
        }
        case 2: {
            string id = leer("Id del nuevo enrutador: ");
            cout << (red.agregarEnrutador(id) ? "Enrutador agregado.\n"
                                              : "Id vacio o ya existente.\n");
            break;
        }
        case 3: {
            string id = leer("Id del enrutador a eliminar: ");
            cout << (red.removerEnrutador(id) ? "Enrutador eliminado y tablas actualizadas.\n"
                                              : "El enrutador no existe.\n");
            break;
        }
        case 4: {
            string a = leer("Enrutador origen: ");
            string b = leer("Enrutador destino: ");
            int c = leerEntero("Costo (entero > 0): ");
            cout << (red.agregarEnlace(a, b, c) ? "Enlace agregado/actualizado y tablas recalculadas.\n"
                                                : "Datos invalidos (revise ids y costo).\n");
            break;
        }
        case 5: {
            string a = leer("Enrutador origen: ");
            string b = leer("Enrutador destino: ");
            cout << (red.removerEnlace(a, b) ? "Enlace eliminado y tablas recalculadas.\n"
                                             : "El enlace no existe.\n");
            break;
        }
        case 6:
            red.imprimirTablas();
            break;
        case 7:
            red.imprimirCaminos();
            break;
        case 8: {
            string a = leer("Origen: ");
            string b = leer("Destino: ");
            int costo;
            list<string> camino = red.obtenerCamino(a, b, costo);
            if (camino.empty()) {
                cout << "No existe camino (o algun enrutador no existe).\n";
            } else {
                cout << "Camino: ";
                bool primero = true;
                for (const auto& n : camino) {
                    if (!primero) cout << " -> ";
                    cout << n;
                    primero = false;
                }
                cout << "\nCosto total: " << costo << "\n";
            }
            break;
        }
        case 9:
            red.imprimirTopologia();
            break;
        case 0:
            salir = true;
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    }
    cout << "Hasta luego.\n";
    return 0;
}

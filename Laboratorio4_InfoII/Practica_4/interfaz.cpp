#include "interfaz.h"
#include "creadorTopologia.h"

#include <filesystem>
#include <iostream>
#include <list>
#include <string>

namespace {
std::string leer(const std::string& msg) {
    std::cout << msg;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int leerEntero(const std::string& msg) {
    const std::string s = leer(msg);
    try {
        return std::stoi(s);
    } catch (...) {
        return -1;
    }
}

std::filesystem::path directorioDebug() {
    const std::filesystem::path actual = std::filesystem::current_path();
    if (actual.filename() == "debug") return actual;
    return actual / "debug";
}

bool nombreArchivoDebug(const std::string& nombreIngresado, std::filesystem::path& ruta) {
    if (nombreIngresado.empty()) return false;
    std::filesystem::path nombre(nombreIngresado);
    // Solo se permite un nombre de archivo, para que siempre se use el directorio debug.
    if (nombre.is_absolute() || nombre.has_parent_path() || nombre.filename() != nombre)
        return false;
    if (nombre.extension().empty()) nombre += ".txt";
    ruta = directorioDebug() / nombre;
    return true;
}

bool cargarDesdeDebug(Red& red, const std::string& etiqueta) {
    const std::string nombre = leer("Nombre del archivo de topologia en debug (ej. topologia.txt): ");
    std::filesystem::path ruta;
    if (!nombreArchivoDebug(nombre, ruta)) {
        std::cout << "Ingresa solo el nombre del archivo, sin carpetas.\n";
        return false;
    }
    if (!red.cargarTopologia(ruta.string())) {
        std::cout << "No se pudo abrir: " << ruta.string() << "\n";
        return false;
    }
    std::cout << etiqueta << " cargada desde " << ruta.string() << ".\n";
    red.imprimirTablas();
    return true;
}

void menu() {
    std::cout << "\n===== SIMULADOR DE RED DE ENRUTADORES =====\n"
              << "1. Cargar topologia desde debug\n"
              << "2. Agregar enrutador\n"
              << "3. Eliminar enrutador\n"
              << "4. Agregar / modificar enlace\n"
              << "5. Eliminar enlace\n"
              << "6. Mostrar tablas de costos\n"
              << "7. Mostrar caminos completos\n"
              << "8. Consultar camino entre dos enrutadores\n"
              << "9. Mostrar enlaces directos\n"
              << "10. Crear archivo de topologia en debug\n"
              << "11. Prueba: cargar topologia desde debug\n"
              << "0. Salir\n";
}
} // namespace

void ejecutarInterfaz(Red& red) {
    bool salir = false;
    while (!salir && std::cin) {
        menu();
        const int op = leerEntero("Opcion: ");
        switch (op) {
        case 1:
            cargarDesdeDebug(red, "Topologia");
            break;
        case 2: {
            const std::string id = leer("Id del nuevo enrutador: ");
            std::cout << (red.agregarEnrutador(id) ? "Enrutador agregado.\n"
                                                   : "Id vacio o ya existente.\n");
            break;
        }
        case 3: {
            const std::string id = leer("Id del enrutador a eliminar: ");
            std::cout << (red.removerEnrutador(id) ? "Enrutador eliminado y tablas actualizadas.\n"
                                                   : "El enrutador no existe.\n");
            break;
        }
        case 4: {
            const std::string a = leer("Enrutador origen: ");
            const std::string b = leer("Enrutador destino: ");
            const int costo = leerEntero("Costo (entero > 0): ");
            std::cout << (red.agregarEnlace(a, b, costo)
                              ? "Enlace agregado/actualizado y tablas recalculadas.\n"
                              : "Datos invalidos (revise ids y costo).\n");
            break;
        }
        case 5: {
            const std::string a = leer("Enrutador origen: ");
            const std::string b = leer("Enrutador destino: ");
            std::cout << (red.removerEnlace(a, b) ? "Enlace eliminado y tablas recalculadas.\n"
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
            const std::string a = leer("Origen: ");
            const std::string b = leer("Destino: ");
            int costo;
            const std::list<std::string> camino = red.obtenerCamino(a, b, costo);
            if (camino.empty()) {
                std::cout << "No existe camino (o algun enrutador no existe).\n";
            } else {
                std::cout << "Camino: ";
                bool primero = true;
                for (const auto& n : camino) {
                    if (!primero) std::cout << " -> ";
                    std::cout << n;
                    primero = false;
                }
                std::cout << "\nCosto total: " << costo << "\n";
            }
            break;
        }
        case 9:
            red.imprimirTopologia();
            break;
        case 10: {
            const std::string nombre = leer("Nombre para el archivo de topologia (ej. topologia.txt): ");
            std::filesystem::path ruta;
            if (!nombreArchivoDebug(nombre, ruta)) {
                std::cout << "Ingresa solo un nombre de archivo, sin carpetas.\n";
                break;
            }
            std::error_code error;
            std::filesystem::create_directories(ruta.parent_path(), error);
            if (error) {
                std::cout << "No se pudo crear el directorio debug: " << error.message() << "\n";
                break;
            }
            if (crearArchivoTopologia(ruta.string()))
                std::cout << "Topologia guardada en: " << ruta.string() << "\n";
            else
                std::cout << "No se pudo crear la topologia.\n";
            break;
        }
        case 11:
            cargarDesdeDebug(red, "Prueba");
            break;
        case 0:
            salir = true;
            break;
        default:
            std::cout << "Opcion invalida.\n";
        }
    }
    std::cout << "Hasta luego.\n";
}

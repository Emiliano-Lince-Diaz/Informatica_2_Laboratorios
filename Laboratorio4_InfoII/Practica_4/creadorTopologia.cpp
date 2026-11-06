#include "creadorTopologia.h"

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>

namespace {
int leerCantidad(const std::string& mensaje) {
    std::string texto;
    std::cout << mensaje;
    std::getline(std::cin, texto);
    try {
        std::size_t procesados = 0;
        const int cantidad = std::stoi(texto, &procesados);
        if (procesados != texto.size() || cantidad < 0) return -1;
        return cantidad;
    } catch (...) {
        return -1;
    }
}
}

bool crearArchivoTopologia(const std::string& rutaArchivo) {
    const int cantidadRouters = leerCantidad("Cantidad de enrutadores: ");
    if (cantidadRouters <= 0) {
        std::cout << "La cantidad debe ser un entero mayor que cero.\n";
        return false;
    }

    std::set<std::string> routers;
    for (int i = 0; i < cantidadRouters; ++i) {
        std::string id;
        std::cout << "Id del enrutador " << i + 1 << ": ";
        std::getline(std::cin, id);
        if (id.empty() || id.find_first_of(" \t") != std::string::npos ||
            !routers.insert(id).second) {
            std::cout << "Id vacio, repetido o con espacios. Intenta de nuevo.\n";
            --i;
        }
    }

    const int cantidadEnlaces = leerCantidad("Cantidad de enlaces: ");
    if (cantidadEnlaces < 0) {
        std::cout << "La cantidad debe ser un entero no negativo.\n";
        return false;
    }

    std::vector<std::string> enlaces;
    for (int i = 0; i < cantidadEnlaces; ++i) {
        std::string origen, destino, textoCosto;
        std::cout << "Enlace " << i + 1 << " (origen destino costo): ";
        std::getline(std::cin, textoCosto);
        // Separar los tres campos sin depender de que el costo se lea como entero.
        const auto primero = textoCosto.find_first_not_of(" \t");
        if (primero == std::string::npos) {
            std::cout << "Formato invalido. Intenta de nuevo.\n";
            --i;
            continue;
        }
        const auto finOrigen = textoCosto.find_first_of(" \t", primero);
        const auto inicioDestino = textoCosto.find_first_not_of(" \t", finOrigen);
        const auto finDestino = textoCosto.find_first_of(" \t", inicioDestino);
        const auto inicioCosto = textoCosto.find_first_not_of(" \t", finDestino);
        if (finOrigen == std::string::npos || inicioDestino == std::string::npos ||
            finDestino == std::string::npos || inicioCosto == std::string::npos) {
            std::cout << "Formato invalido. Usa: origen destino costo.\n";
            --i;
            continue;
        }
        origen = textoCosto.substr(primero, finOrigen - primero);
        destino = textoCosto.substr(inicioDestino, finDestino - inicioDestino);
        int costo = 0;
        try {
            std::size_t procesados = 0;
            costo = std::stoi(textoCosto.substr(inicioCosto), &procesados);
            if (procesados != textoCosto.substr(inicioCosto).size()) costo = 0;
        } catch (...) {
            costo = 0;
        }
        if (routers.count(origen) == 0 || routers.count(destino) == 0 ||
            origen == destino || costo <= 0) {
            std::cout << "Enlace invalido: revisa los ids y usa un costo mayor que cero.\n";
            --i;
            continue;
        }
        enlaces.push_back("E " + origen + " " + destino + " " + std::to_string(costo));
    }

    std::ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cout << "No se pudo crear el archivo en: " << rutaArchivo << "\n";
        return false;
    }

    archivo << "# Topologia creada desde el simulador\n"
            << "# R <id> declara un enrutador\n"
            << "# E <id1> <id2> <costo> declara un enlace bidireccional\n";
    for (const auto& id : routers) archivo << "R " << id << "\n";
    archivo << "\n";
    for (const auto& enlace : enlaces) archivo << enlace << "\n";
    return archivo.good();
}

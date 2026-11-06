#include "red.h"

#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <utility>
#include <vector>

Red::Red() = default;

bool Red::conectar(const std::string& a, const std::string& b, int costo) {
    if (a == b || costo <= 0) return false;
    auto ia = enrutadores.find(a);
    auto ib = enrutadores.find(b);
    if (ia == enrutadores.end() || ib == enrutadores.end()) return false;
    ia->second.agregarVecino(b, costo);
    ib->second.agregarVecino(a, costo);
    return true;
}

bool Red::existe(const std::string& id) const {
    return enrutadores.count(id) > 0;
}

bool Red::vacia() const {
    return enrutadores.empty();
}

bool Red::agregarEnrutador(const std::string& id) {
    if (id.empty() || existe(id)) return false;
    enrutadores.insert({id, Enrutador(id)});
    calcularCaminos();
    return true;
}

bool Red::removerEnrutador(const std::string& id) {
    auto it = enrutadores.find(id);
    if (it == enrutadores.end()) return false;
    for (const auto& vecino : it->second.getVecinos()) {
        auto iv = enrutadores.find(vecino.first);
        if (iv != enrutadores.end()) iv->second.removerVecino(id);
    }
    enrutadores.erase(it);
    calcularCaminos();
    return true;
}

bool Red::agregarEnlace(const std::string& origen, const std::string& destino, int costo) {
    if (!conectar(origen, destino, costo)) return false;
    calcularCaminos();
    return true;
}

bool Red::removerEnlace(const std::string& origen, const std::string& destino) {
    auto io = enrutadores.find(origen);
    auto id = enrutadores.find(destino);
    if (io == enrutadores.end() || id == enrutadores.end()) return false;
    if (!io->second.esVecino(destino)) return false;
    io->second.removerVecino(destino);
    id->second.removerVecino(origen);
    calcularCaminos();
    return true;
}

void Red::calcularCaminos() {
    for (auto& par : enrutadores) {
        const std::string& origen = par.first;
        std::map<std::string, int> dist;
        std::map<std::string, std::string> prev;
        for (const auto& router : enrutadores) dist[router.first] = Enrutador::INF;
        dist[origen] = 0;

        using Par = std::pair<int, std::string>;
        std::priority_queue<Par, std::vector<Par>, std::greater<Par>> pq;
        pq.push({0, origen});
        while (!pq.empty()) {
            const Par top = pq.top();
            pq.pop();
            const int d = top.first;
            const std::string u = top.second;
            if (d > dist[u]) continue;
            for (const auto& vecino : enrutadores.at(u).getVecinos()) {
                const int nuevoCosto = d + vecino.second;
                if (nuevoCosto < dist[vecino.first]) {
                    dist[vecino.first] = nuevoCosto;
                    prev[vecino.first] = u;
                    pq.push({nuevoCosto, vecino.first});
                }
            }
        }

        std::map<std::string, std::list<std::string>> caminos;
        for (const auto& destino : dist) {
            if (destino.second == Enrutador::INF) continue;
            std::list<std::string> camino;
            std::string n = destino.first;
            while (true) {
                camino.push_front(n);
                if (n == origen) break;
                n = prev[n];
            }
            caminos[destino.first] = camino;
        }
        par.second.actualizarTablas(dist, caminos);
    }
}

std::list<std::string> Red::obtenerCamino(
    const std::string& origen, const std::string& destino, int& costo) const {
    costo = Enrutador::INF;
    auto it = enrutadores.find(origen);
    if (it == enrutadores.end() || !existe(destino)) return {};
    costo = it->second.getCosto(destino);
    if (costo == Enrutador::INF) return {};
    return it->second.getCamino(destino);
}

bool Red::cargarTopologia(const std::string& rutaArchivo) {
    std::ifstream in(rutaArchivo);
    if (!in.is_open()) return false;

    enrutadores.clear();
    std::string linea;
    int nLinea = 0;
    while (std::getline(in, linea)) {
        ++nLinea;
        const std::size_t pos = linea.find('#');
        if (pos != std::string::npos) linea = linea.substr(0, pos);
        std::istringstream ss(linea);
        std::string tipo;
        if (!(ss >> tipo)) continue;

        if (tipo == "R") {
            std::string id;
            if (ss >> id) {
                if (!existe(id)) enrutadores.insert({id, Enrutador(id)});
            } else {
                std::cerr << "Linea " << nLinea << ": falta el id del enrutador\n";
            }
        } else if (tipo == "E") {
            std::string a, b;
            int costo;
            if (ss >> a >> b >> costo) {
                if (!existe(a)) enrutadores.insert({a, Enrutador(a)});
                if (!existe(b)) enrutadores.insert({b, Enrutador(b)});
                if (!conectar(a, b, costo))
                    std::cerr << "Linea " << nLinea << ": enlace invalido\n";
            } else {
                std::cerr << "Linea " << nLinea << ": formato de enlace invalido\n";
            }
        } else {
            std::cerr << "Linea " << nLinea << ": instruccion desconocida '" << tipo << "'\n";
        }
    }
    calcularCaminos();
    return true;
}

std::string Red::fmtCosto(int costo) {
    return costo == Enrutador::INF ? "INF" : std::to_string(costo);
}

void Red::imprimirTablas() const {
    if (enrutadores.empty()) {
        std::cout << "La red esta vacia.\n";
        return;
    }
    std::cout << "\nTabla de costos minimos:\n" << std::setw(6) << " ";
    for (const auto& router : enrutadores) std::cout << std::setw(6) << router.first;
    std::cout << "\n";
    for (const auto& fila : enrutadores) {
        std::cout << std::setw(6) << fila.first;
        for (const auto& columna : enrutadores)
            std::cout << std::setw(6) << fmtCosto(fila.second.getCosto(columna.first));
        std::cout << "\n";
    }
}

void Red::imprimirCaminos() const {
    std::cout << "\nCaminos completos por enrutador:\n";
    for (const auto& fila : enrutadores) {
        std::cout << "Enrutador " << fila.first << ":\n";
        for (const auto& columna : enrutadores) {
            if (columna.first == fila.first) continue;
            const std::list<std::string> camino = fila.second.getCamino(columna.first);
            std::cout << "  -> " << columna.first << ": ";
            if (camino.empty()) {
                std::cout << "sin ruta\n";
                continue;
            }
            bool primero = true;
            for (const auto& n : camino) {
                if (!primero) std::cout << " -> ";
                std::cout << n;
                primero = false;
            }
            std::cout << "  (costo " << fila.second.getCosto(columna.first) << ")\n";
        }
    }
}

void Red::imprimirTopologia() const {
    std::cout << "\nEnlaces directos:\n";
    for (const auto& router : enrutadores) {
        std::cout << "  " << router.first << ": ";
        if (router.second.getVecinos().empty()) std::cout << "(sin vecinos)";
        for (const auto& vecino : router.second.getVecinos())
            std::cout << vecino.first << "(" << vecino.second << ") ";
        std::cout << "\n";
    }
}

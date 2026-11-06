#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <functional>

// Gestor centralizado de la topologia (modelo simplificado de la guia).
class Red {
private:
    std::map<std::string, Enrutador> enrutadores;

    // Crea el enlace bidireccional SIN recalcular (uso interno)
    bool conectar(const std::string& a, const std::string& b, int costo) {
        if (a == b || costo <= 0) return false;
        auto ia = enrutadores.find(a);
        auto ib = enrutadores.find(b);
        if (ia == enrutadores.end() || ib == enrutadores.end()) return false;
        ia->second.agregarVecino(b, costo);
        ib->second.agregarVecino(a, costo);
        return true;
    }

public:
    Red() {}

    bool existe(const std::string& id) const { return enrutadores.count(id) > 0; }
    bool vacia() const { return enrutadores.empty(); }

    // ---------- Gestion de enrutadores ----------
    bool agregarEnrutador(const std::string& id) {
        if (id.empty() || existe(id)) return false;
        enrutadores.insert({id, Enrutador(id)});
        calcularCaminos();
        return true;
    }

    bool removerEnrutador(const std::string& id) {
        auto it = enrutadores.find(id);
        if (it == enrutadores.end()) return false;
        // Quitar al enrutador de la lista de vecinos de los demas
        for (const auto& v : it->second.getVecinos()) {
            auto iv = enrutadores.find(v.first);
            if (iv != enrutadores.end()) iv->second.removerVecino(id);
        }
        enrutadores.erase(it);
        calcularCaminos();
        return true;
    }

    // ---------- Gestion de enlaces (bidireccionales) ----------
    // Si el enlace ya existe, se actualiza su costo.
    bool agregarEnlace(const std::string& origen, const std::string& destino, int costo) {
        if (!conectar(origen, destino, costo)) return false;
        calcularCaminos();
        return true;
    }

    bool removerEnlace(const std::string& origen, const std::string& destino) {
        auto io = enrutadores.find(origen);
        auto id = enrutadores.find(destino);
        if (io == enrutadores.end() || id == enrutadores.end()) return false;
        if (!io->second.esVecino(destino)) return false;
        io->second.removerVecino(destino);
        id->second.removerVecino(origen);
        calcularCaminos();
        return true;
    }

    // ---------- Dijkstra desde cada enrutador ----------
    void calcularCaminos() {
        for (auto& par : enrutadores) {
            const std::string& origen = par.first;

            std::map<std::string, int> dist;
            std::map<std::string, std::string> prev;
            for (const auto& r : enrutadores) dist[r.first] = Enrutador::INF;
            dist[origen] = 0;

            using Par = std::pair<int, std::string>;
            std::priority_queue<Par, std::vector<Par>, std::greater<Par>> pq;
            pq.push({0, origen});

            while (!pq.empty()) {
                Par top = pq.top();
                pq.pop();
                int d = top.first;
                const std::string u = top.second;
                if (d > dist[u]) continue; // entrada obsoleta
                for (const auto& v : enrutadores.at(u).getVecinos()) {
                    int nd = d + v.second;
                    if (nd < dist[v.first]) {
                        dist[v.first] = nd;
                        prev[v.first] = u;
                        pq.push({nd, v.first});
                    }
                }
            }

            // Reconstruir caminos con push_front (de destino hacia origen)
            std::map<std::string, std::list<std::string>> caminos;
            for (const auto& d : dist) {
                if (d.second == Enrutador::INF) continue;
                std::list<std::string> camino;
                std::string n = d.first;
                while (true) {
                    camino.push_front(n);
                    if (n == origen) break;
                    n = prev[n];
                }
                caminos[d.first] = camino;
            }
            par.second.actualizarTablas(dist, caminos);
        }
    }

    // ---------- Consulta de caminos ----------
    // Devuelve el camino (vacio si no existe) y escribe el costo en 'costo'.
    std::list<std::string> obtenerCamino(const std::string& origen,
                                         const std::string& destino, int& costo) const {
        costo = Enrutador::INF;
        auto it = enrutadores.find(origen);
        if (it == enrutadores.end() || !existe(destino)) return {};
        costo = it->second.getCosto(destino);
        if (costo == Enrutador::INF) return {};
        return it->second.getCamino(destino);
    }

    // ---------- Carga desde archivo ----------
    // Formato (una instruccion por linea, '#' inicia un comentario):
    //   R <id>                 -> declara un enrutador
    //   E <id1> <id2> <costo>  -> enlace bidireccional (crea los enrutadores si faltan)
    bool cargarTopologia(const std::string& rutaArchivo) {
        std::ifstream in(rutaArchivo);
        if (!in.is_open()) return false;

        enrutadores.clear();
        std::string linea;
        int nLinea = 0;
        while (std::getline(in, linea)) {
            ++nLinea;
            std::size_t pos = linea.find('#');
            if (pos != std::string::npos) linea = linea.substr(0, pos);
            std::istringstream ss(linea);
            std::string tipo;
            if (!(ss >> tipo)) continue; // linea vacia

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
        calcularCaminos(); // un unico recalculo al final
        return true;
    }

    // ---------- Salida ----------
    static std::string fmtCosto(int c) { return c == Enrutador::INF ? "INF" : std::to_string(c); }

    void imprimirTablas() const {
        if (enrutadores.empty()) {
            std::cout << "La red esta vacia.\n";
            return;
        }
        std::cout << "\nTabla de costos minimos:\n" << std::setw(6) << " ";
        for (const auto& c : enrutadores) std::cout << std::setw(6) << c.first;
        std::cout << "\n";
        for (const auto& f : enrutadores) {
            std::cout << std::setw(6) << f.first;
            for (const auto& c : enrutadores)
                std::cout << std::setw(6) << fmtCosto(f.second.getCosto(c.first));
            std::cout << "\n";
        }
    }

    void imprimirCaminos() const {
        std::cout << "\nCaminos completos por enrutador:\n";
        for (const auto& f : enrutadores) {
            std::cout << "Enrutador " << f.first << ":\n";
            for (const auto& c : enrutadores) {
                if (c.first == f.first) continue;
                std::list<std::string> cam = f.second.getCamino(c.first);
                std::cout << "  -> " << c.first << ": ";
                if (cam.empty()) {
                    std::cout << "sin ruta\n";
                    continue;
                }
                bool primero = true;
                for (const auto& n : cam) {
                    if (!primero) std::cout << " -> ";
                    std::cout << n;
                    primero = false;
                }
                std::cout << "  (costo " << f.second.getCosto(c.first) << ")\n";
            }
        }
    }

    void imprimirTopologia() const {
        std::cout << "\nEnlaces directos:\n";
        for (const auto& r : enrutadores) {
            std::cout << "  " << r.first << ": ";
            if (r.second.getVecinos().empty()) std::cout << "(sin vecinos)";
            for (const auto& v : r.second.getVecinos())
                std::cout << v.first << "(" << v.second << ") ";
            std::cout << "\n";
        }
    }
};

#endif

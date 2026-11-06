#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
#include <list>
#include <limits>

// Representa unicamente la informacion LOCAL de un enrutador:
// su id, sus vecinos directos y lo que la red le ha informado (costos y caminos).
class Enrutador {
public:
    static constexpr int INF = std::numeric_limits<int>::max();

private:
    std::string id;
    std::map<std::string, int> vecinos;                         // <vecino, costo del enlace>
    std::map<std::string, int> tablaCostos;                     // <destino, costo minimo>
    std::map<std::string, std::list<std::string>> tablaCaminos; // <destino, camino completo>

public:
    explicit Enrutador(const std::string& _id) : id(_id) {
        // Al encenderse solo se conoce a si mismo
        tablaCostos[id] = 0;
        tablaCaminos[id] = std::list<std::string>{id};
    }

    const std::string& getId() const { return id; }

    // ---- Gestion de enlaces directos ----
    void agregarVecino(const std::string& idVecino, int costo) { vecinos[idVecino] = costo; }
    void removerVecino(const std::string& idVecino) { vecinos.erase(idVecino); }
    bool esVecino(const std::string& idVecino) const { return vecinos.count(idVecino) > 0; }
    const std::map<std::string, int>& getVecinos() const { return vecinos; }

    // ---- Informacion entregada por la Red tras un recalculo ----
    void actualizarTablas(const std::map<std::string, int>& costos,
                          const std::map<std::string, std::list<std::string>>& caminos) {
        tablaCostos = costos;
        tablaCaminos = caminos;
    }

    const std::map<std::string, int>& getTablaCostos() const { return tablaCostos; }

    int getCosto(const std::string& destino) const {
        auto it = tablaCostos.find(destino);
        return (it == tablaCostos.end()) ? INF : it->second;
    }

    // Camino completo hacia 'destino' (lista vacia si no es alcanzable)
    std::list<std::string> getCamino(const std::string& destino) const {
        auto it = tablaCaminos.find(destino);
        return (it == tablaCaminos.end()) ? std::list<std::string>() : it->second;
    }
};

#endif

#include "enrutador.h"

Enrutador::Enrutador(const std::string& _id) : id(_id) {
    tablaCostos[id] = 0;
    tablaCaminos[id] = std::list<std::string>{id};
}

const std::string& Enrutador::getId() const {
    return id;
}

void Enrutador::agregarVecino(const std::string& idVecino, int costo) {
    vecinos[idVecino] = costo;
}

void Enrutador::removerVecino(const std::string& idVecino) {
    vecinos.erase(idVecino);
}

bool Enrutador::esVecino(const std::string& idVecino) const {
    return vecinos.count(idVecino) > 0;
}

const std::map<std::string, int>& Enrutador::getVecinos() const {
    return vecinos;
}

void Enrutador::actualizarTablas(
    const std::map<std::string, int>& costos,
    const std::map<std::string, std::list<std::string>>& caminos) {
    tablaCostos = costos;
    tablaCaminos = caminos;
}

const std::map<std::string, int>& Enrutador::getTablaCostos() const {
    return tablaCostos;
}

int Enrutador::getCosto(const std::string& destino) const {
    const auto it = tablaCostos.find(destino);
    return it == tablaCostos.end() ? INF : it->second;
}

std::list<std::string> Enrutador::getCamino(const std::string& destino) const {
    const auto it = tablaCaminos.find(destino);
    return it == tablaCaminos.end() ? std::list<std::string>() : it->second;
}

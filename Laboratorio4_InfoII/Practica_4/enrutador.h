#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <limits>
#include <list>
#include <map>
#include <string>

// Representa la informacion local de un enrutador.
class Enrutador {
public:
    static constexpr int INF = std::numeric_limits<int>::max();

private:
    std::string id;
    std::map<std::string, int> vecinos;
    std::map<std::string, int> tablaCostos;
    std::map<std::string, std::list<std::string>> tablaCaminos;

public:
    explicit Enrutador(const std::string& id);

    const std::string& getId() const;
    void agregarVecino(const std::string& idVecino, int costo);
    void removerVecino(const std::string& idVecino);
    bool esVecino(const std::string& idVecino) const;
    const std::map<std::string, int>& getVecinos() const;
    void actualizarTablas(
        const std::map<std::string, int>& costos,
        const std::map<std::string, std::list<std::string>>& caminos);
    const std::map<std::string, int>& getTablaCostos() const;
    int getCosto(const std::string& destino) const;
    std::list<std::string> getCamino(const std::string& destino) const;
};

#endif

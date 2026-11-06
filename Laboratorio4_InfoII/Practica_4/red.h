#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <list>
#include <map>
#include <string>

// Gestor centralizado de la topologia de la red.
class Red {
private:
    std::map<std::string, Enrutador> enrutadores;
    bool conectar(const std::string& a, const std::string& b, int costo);

public:
    Red();

    bool existe(const std::string& id) const;
    bool vacia() const;
    int cantidadEnrutadores() const;
    int cantidadEnlaces() const;
    bool agregarEnrutador(const std::string& id);
    bool removerEnrutador(const std::string& id);
    bool agregarEnlace(const std::string& origen, const std::string& destino, int costo);
    bool removerEnlace(const std::string& origen, const std::string& destino);
    void calcularCaminos();
    std::list<std::string> obtenerCamino(
        const std::string& origen, const std::string& destino, int& costo) const;
    bool cargarTopologia(const std::string& rutaArchivo);
    static std::string fmtCosto(int costo);
    void imprimirTablas() const;
    void imprimirCaminos() const;
    void imprimirTopologia() const;

};


#endif
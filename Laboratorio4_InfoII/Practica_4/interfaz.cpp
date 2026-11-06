#include "interfaz.h"
#include "creadorTopologia.h"

#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <system_error>
#include <vector>

namespace fs = std::filesystem;

namespace {

const std::size_t ANCHO = 64;

// ---------------------------------------------------------------- entrada

std::string leer(const std::string& msg) {
    std::cout << msg;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// Quita espacios y comillas (Windows agrega comillas al "Copiar como ruta").
std::string limpiar(std::string s) {
    const char* blancos = " \t\r\n";
    const auto ini = s.find_first_not_of(blancos);
    if (ini == std::string::npos) return "";
    const auto fin = s.find_last_not_of(blancos);
    s = s.substr(ini, fin - ini + 1);
    if (s.size() >= 2 && ((s.front() == '"' && s.back() == '"') ||
                          (s.front() == '\'' && s.back() == '\'')))
        s = limpiar(s.substr(1, s.size() - 2));
    return s;
}

bool aEntero(const std::string& texto, int& valor) {
    const std::string t = limpiar(texto);
    if (t.empty()) return false;
    try {
        std::size_t usados = 0;
        const int v = std::stoi(t, &usados);
        if (usados != t.size()) return false;
        valor = v;
        return true;
    } catch (...) {
        return false;
    }
}

// ----------------------------------------------------------------- salida

void linea(char c) {
    std::cout << '+' << std::string(ANCHO - 2, c) << "+\n";
}

void fila(const std::string& texto) {
    std::cout << "| " << std::left << std::setw(static_cast<int>(ANCHO - 4)) << texto << std::right
              << " |\n";
}

void centrada(const std::string& texto) {
    const std::size_t libre = ANCHO - 4;
    const std::size_t izq = texto.size() < libre ? (libre - texto.size()) / 2 : 0;
    fila(std::string(izq, ' ') + texto);
}

void encabezado(const std::string& titulo) {
    std::cout << "\n";
    linea('=');
    centrada(titulo);
    linea('=');
}

void ok(const std::string& msg) { std::cout << "\n  [OK] " << msg << "\n"; }
void fallo(const std::string& msg) { std::cout << "\n  [X]  " << msg << "\n"; }
void pausa() { leer("\n  Presione Enter para volver al menu..."); }

void menu(const Red& red) {
    std::cout << "\n";
    linea('=');
    centrada("SIMULADOR DE RED DE ENRUTADORES");
    linea('=');
    if (red.vacia())
        fila(" Red actual: vacia (cargue o cree una topologia)");
    else
        fila(" Red actual: " + std::to_string(red.cantidadEnrutadores()) + " enrutadores | " +
             std::to_string(red.cantidadEnlaces()) + " enlaces");
    linea('-');
    fila(" ARCHIVOS");
    fila("   1. Cargar topologia desde archivo");
    fila("   2. Crear archivo de topologia");
    linea('-');
    fila(" GESTION DE LA RED");
    fila("   3. Agregar enrutador");
    fila("   4. Eliminar enrutador");
    fila("   5. Agregar / modificar enlace");
    fila("   6. Eliminar enlace");
    linea('-');
    fila(" CONSULTAS");
    fila("   7. Mostrar tablas de costos");
    fila("   8. Mostrar caminos completos");
    fila("   9. Consultar camino entre dos enrutadores");
    fila("  10. Mostrar enlaces directos");
    linea('-');
    fila("   0. Salir");
    linea('=');
}

// ----------------------------------------------------------------- rutas

fs::path directorioActual() {
    std::error_code ec;
    const fs::path p = fs::current_path(ec);
    return ec ? fs::path(".") : p;
}

fs::path directorioDebug() {
    const fs::path actual = directorioActual();
    if (actual.filename() == "debug") return actual;
    return actual / "debug";
}

// Archivos .txt en la carpeta actual y en la carpeta debug.
std::vector<fs::path> buscarTopologias() {
    std::vector<fs::path> resultado;
    std::set<std::string> vistos;
    for (const fs::path& dir : {directorioActual(), directorioDebug()}) {
        std::error_code ec;
        for (fs::directory_iterator it(dir, ec), fin; !ec && it != fin; it.increment(ec)) {
            std::error_code ec2;
            if (!it->is_regular_file(ec2) || it->path().extension() != ".txt") continue;
            if (vistos.insert(it->path().generic_string()).second) resultado.push_back(it->path());
        }
    }
    std::sort(resultado.begin(), resultado.end());
    return resultado;
}

// Acepta nombre suelto, nombre sin extension o ruta completa.
bool resolverArchivoExistente(const std::string& entrada, fs::path& ruta) {
    const std::string texto = limpiar(entrada);
    if (texto.empty()) return false;
    const fs::path p(texto);

    std::vector<fs::path> candidatos;
    auto agregar = [&](fs::path c) {
        candidatos.push_back(c);
        if (c.extension().empty()) {
            c += ".txt";
            candidatos.push_back(c);
        }
    };
    if (p.is_absolute() || p.has_parent_path()) {
        agregar(p);
    } else {
        agregar(directorioActual() / p);
        agregar(directorioDebug() / p);
    }
    for (const fs::path& c : candidatos) {
        std::error_code ec;
        if (fs::is_regular_file(c, ec)) {
            ruta = c;
            return true;
        }
    }
    return false;
}

// Un nombre suelto se guarda en debug; con ruta, se respeta la ruta.
fs::path rutaDeSalida(const std::string& entrada) {
    fs::path p(limpiar(entrada));
    if (!(p.is_absolute() || p.has_parent_path())) p = directorioDebug() / p;
    if (p.extension().empty()) p += ".txt";
    return p;
}

void mostrarCarpetasRevisadas() {
    std::cout << "\n  Carpetas revisadas:\n"
              << "   - " << directorioActual().string() << "\n"
              << "   - " << directorioDebug().string() << "\n";
}

// --------------------------------------------------------------- acciones

void accionCargar(Red& red) {
    encabezado("CARGAR TOPOLOGIA");
    const std::vector<fs::path> lista = buscarTopologias();
    if (lista.empty()) {
        std::cout << "\n  No se encontraron archivos .txt.\n";
    } else {
        std::cout << "\n  Archivos de topologia encontrados:\n";
        for (std::size_t i = 0; i < lista.size(); ++i)
            std::cout << "   " << std::setw(2) << i + 1 << ") " << lista[i].filename().string()
                      << "\n";
    }
    mostrarCarpetasRevisadas();

    const std::string entrada =
        leer("\n  Numero, nombre o ruta completa (Enter para cancelar): ");
    if (limpiar(entrada).empty()) {
        std::cout << "\n  Operacion cancelada.\n";
        return;
    }

    fs::path ruta;
    int numero = 0;
    bool encontrada = false;
    if (aEntero(entrada, numero) && numero >= 1 && numero <= static_cast<int>(lista.size())) {
        ruta = lista[static_cast<std::size_t>(numero - 1)];
        encontrada = true;
    } else {
        encontrada = resolverArchivoExistente(entrada, ruta);
    }

    if (!encontrada) {
        fallo("No se encontro el archivo '" + limpiar(entrada) + "'.");
        return;
    }
    if (!red.cargarTopologia(ruta.string())) {
        fallo("No se pudo abrir: " + ruta.string());
        return;
    }
    ok("Topologia cargada desde " + ruta.string());
    red.imprimirTablas();
}

void accionCrear(Red& red) {
    encabezado("CREAR ARCHIVO DE TOPOLOGIA");
    std::cout << "\n  Un nombre suelto se guarda en: " << directorioDebug().string() << "\n"
              << "  Tambien puede escribir una ruta completa.\n";
    const std::string entrada = leer("\n  Nombre del archivo (Enter para cancelar): ");
    if (limpiar(entrada).empty()) {
        std::cout << "\n  Operacion cancelada.\n";
        return;
    }

    const fs::path ruta = rutaDeSalida(entrada);
    std::error_code ec;
    if (fs::exists(ruta, ec)) {
        const std::string r = limpiar(leer("\n  El archivo ya existe. Sobrescribir? (s/n): "));
        if (r != "s" && r != "S") {
            std::cout << "\n  Operacion cancelada.\n";
            return;
        }
    }
    if (ruta.has_parent_path()) {
        fs::create_directories(ruta.parent_path(), ec);
        if (ec) {
            fallo("No se pudo crear la carpeta: " + ec.message());
            return;
        }
    }

    std::cout << "\n";
    if (!crearArchivoTopologia(ruta.string())) {
        fallo("No se pudo crear la topologia.");
        return;
    }
    ok("Topologia guardada en: " + ruta.string());

    const std::string r = limpiar(leer("\n  Cargarla ahora en el simulador? (s/n): "));
    if (r == "s" || r == "S") {
        if (red.cargarTopologia(ruta.string())) {
            ok("Topologia cargada.");
            red.imprimirTablas();
        } else {
            fallo("No se pudo abrir el archivo recien creado.");
        }
    }
}

void accionAgregarEnrutador(Red& red) {
    encabezado("AGREGAR ENRUTADOR");
    const std::string id = limpiar(leer("\n  Id del nuevo enrutador: "));
    if (id.find_first_of(" \t") != std::string::npos)
        fallo("El id no puede tener espacios.");
    else if (red.agregarEnrutador(id))
        ok("Enrutador '" + id + "' agregado.");
    else
        fallo("Id vacio o ya existente.");
}

void accionEliminarEnrutador(Red& red) {
    encabezado("ELIMINAR ENRUTADOR");
    const std::string id = limpiar(leer("\n  Id del enrutador a eliminar: "));
    if (red.removerEnrutador(id))
        ok("Enrutador '" + id + "' eliminado. Tablas recalculadas.");
    else
        fallo("El enrutador no existe.");
}

void accionAgregarEnlace(Red& red) {
    encabezado("AGREGAR / MODIFICAR ENLACE");
    const std::string a = limpiar(leer("\n  Enrutador origen : "));
    const std::string b = limpiar(leer("  Enrutador destino: "));
    int costo = 0;
    if (!aEntero(leer("  Costo (entero > 0): "), costo)) costo = -1;
    if (red.agregarEnlace(a, b, costo))
        ok("Enlace " + a + " <-> " + b + " con costo " + std::to_string(costo) +
           ". Tablas recalculadas.");
    else
        fallo("Datos invalidos: revise que existan ambos enrutadores, que sean distintos y que el costo sea > 0.");
}

void accionEliminarEnlace(Red& red) {
    encabezado("ELIMINAR ENLACE");
    const std::string a = limpiar(leer("\n  Enrutador origen : "));
    const std::string b = limpiar(leer("  Enrutador destino: "));
    if (red.removerEnlace(a, b))
        ok("Enlace " + a + " <-> " + b + " eliminado. Tablas recalculadas.");
    else
        fallo("El enlace no existe.");
}

void accionConsultarCamino(const Red& red) {
    encabezado("CONSULTAR CAMINO");
    const std::string a = limpiar(leer("\n  Origen : "));
    const std::string b = limpiar(leer("  Destino: "));
    int costo = 0;
    const std::list<std::string> camino = red.obtenerCamino(a, b, costo);
    if (camino.empty()) {
        fallo("No existe camino (o algun enrutador no existe).");
        return;
    }
    std::cout << "\n  Camino      : ";
    bool primero = true;
    for (const auto& n : camino) {
        if (!primero) std::cout << " -> ";
        std::cout << n;
        primero = false;
    }
    std::cout << "\n  Costo total : " << costo << "\n";
}

} // namespace

void ejecutarInterfaz(Red& red) {
    bool salir = false;
    while (!salir && std::cin) {
        menu(red);
        int op = -1;
        if (!aEntero(leer("  Seleccione una opcion: "), op)) op = -1;

        bool conPausa = true;
        switch (op) {
        case 1:
            accionCargar(red);
            break;
        case 2:
            accionCrear(red);
            break;
        case 3:
            accionAgregarEnrutador(red);
            break;
        case 4:
            accionEliminarEnrutador(red);
            break;
        case 5:
            accionAgregarEnlace(red);
            break;
        case 6:
            accionEliminarEnlace(red);
            break;
        case 7:
            encabezado("TABLAS DE COSTOS");
            red.imprimirTablas();
            break;
        case 8:
            encabezado("CAMINOS COMPLETOS");
            red.imprimirCaminos();
            break;
        case 9:
            accionConsultarCamino(red);
            break;
        case 10:
            encabezado("ENLACES DIRECTOS");
            red.imprimirTopologia();
            break;
        case 0:
            salir = true;
            conPausa = false;
            break;
        default:
            fallo("Opcion invalida. Elija un numero del menu.");
        }
        if (conPausa && !salir) pausa();
    }
    std::cout << "\n  Hasta luego.\n";
}
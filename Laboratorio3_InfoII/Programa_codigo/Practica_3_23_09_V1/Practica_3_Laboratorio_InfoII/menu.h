#ifndef MENU_H
#define MENU_H

namespace Menu {
// Función auxiliar reutilizable para solicitar y validar opciones numéricas
int leerOpcion(int minOpcion, int maxOpcion);

// Despliega el menú principal
void mostrarMenuPrincipal();

// Despliega el menú de pruebas de algoritmos (RLE / LZ78)
void mostrarMenuPruebas();
}

#endif // MENU_H

#ifndef LZ78_H
#define LZ78_H

#include <cstddef>

// Estructura para los pares emitidos durante la compresión: (índice_prefijo, carácter)
struct Pair {
    unsigned int index;
    char character;
};

// Estructura para almacenar cada frase del diccionario
struct DictEntry {
    unsigned int prefixIndex;
    char character;
};

// Gestionador manual de memoria dinámica para el diccionario
struct Dictionary {
    DictEntry* entries;
    std::size_t size;
    std::size_t capacity;

    Dictionary(std::size_t initialCapacity = 4);
    ~Dictionary();

    void clear();
    void resize();
    void insert(unsigned int prefixIndex, char c);
    int find(unsigned int prefixIndex, char c) const; // Retorna índice 1-based si existe, 0 si no
};
#endif // LZ78_H

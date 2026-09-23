#include "lz78.h"

#include <iostream>

using namespace std;

// Constructor: asigna memoria inicial
Dictionary::Dictionary(size_t initialCapacity) {
    size = 0;
    capacity = initialCapacity;
    entries = new DictEntry[capacity];
}

// Destructor: libera la memoria asignada
Dictionary::~Dictionary() {
    clear();
}

void Dictionary::clear() {
    if (entries != nullptr) {
        delete[] entries;
        entries = nullptr;
    }
    size = 0;
    capacity = 0;
}

// Duplica la capacidad de la memoria dinámica cuando el arreglo se llena
void Dictionary::resize() {
    size_t newCapacity = (capacity == 0) ? 4 : capacity * 2;
    DictEntry* newEntries = new DictEntry[newCapacity];

    for (size_t i = 0; i < size; ++i) {
        newEntries[i] = entries[i];
    }

    delete[] entries; // Libera el arreglo antiguo
    entries = newEntries;
    capacity = newCapacity;
}

// Inserta una nueva entrada al diccionario
void Dictionary::insert(unsigned int prefixIndex, char c) {
    if (size >= capacity) {
        resize();
    }
    entries[size].prefixIndex = prefixIndex;
    entries[size].character = c;
    size++;
}

// Busca si la pareja (prefixIndex, c) ya existe en el diccionario.
// Retorna el índice 1-based si la encuentra, o 0 si no existe.
int Dictionary::find(unsigned int prefixIndex, char c) const {
    for (size_t i = 0; i < size; ++i) {
        if (entries[i].prefixIndex == prefixIndex && entries[i].character == c) {
            return static_cast<int>(i + 1); // Retorna índice 1-based
        }
    }
    return 0;
}
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
namespace LZ78 {

// Auxiliar: calcula la longitud de una frase en el diccionario acumulando sus prefijos
size_t getPhraseLength(const Dictionary& dict, unsigned int index) {
    size_t len = 0;
    while (index > 0) {
        len++;
        index = dict.entries[index - 1].prefixIndex;
    }
    return len;
}

// Auxiliar: escribe la frase en el búfer de derecha a izquierda
void getPhrase(const Dictionary& dict, unsigned int index, char* buffer) {
    size_t len = getPhraseLength(dict, index);
    size_t curr = len;
    while (index > 0) {
        buffer[--curr] = dict.entries[index - 1].character;
        index = dict.entries[index - 1].prefixIndex;
    }
}

Pair* compress(const char* input, size_t length, size_t& outPairCount) {
    if (input == nullptr || length == 0) {
        outPairCount = 0;
        return nullptr;
    }

    Dictionary dict(16);
    size_t pairCapacity = 16;
    outPairCount = 0;
    Pair* pairs = new Pair[pairCapacity];

    size_t pos = 0;
    while (pos < length) {
        unsigned int currentMatchingIndex = 0;
        size_t matchLen = 0;

        // Busca la coincidencia más larga en el diccionario
        while (pos + matchLen < length) {
            char c = input[pos + matchLen];
            int nextIndex = dict.find(currentMatchingIndex, c);
            if (nextIndex > 0) {
                currentMatchingIndex = static_cast<unsigned int>(nextIndex);
                matchLen++;
            } else {
                break;
            }
        }

        char nextChar = '\0';
        if (pos + matchLen < length) {
            nextChar = input[pos + matchLen];
            dict.insert(currentMatchingIndex, nextChar);
            pos += matchLen + 1;
        } else {
            // Caso al llegar al final del texto con coincidencia exacta
            pos += matchLen;
        }

        // Redimensiona el arreglo dinámico de pares si es necesario
        if (outPairCount >= pairCapacity) {
            pairCapacity *= 2;
            Pair* newPairs = new Pair[pairCapacity];
            for (size_t i = 0; i < outPairCount; ++i) {
                newPairs[i] = pairs[i];
            }
            delete[] pairs;
            pairs = newPairs;
        }

        pairs[outPairCount].index = currentMatchingIndex;
        pairs[outPairCount].character = nextChar;
        outPairCount++;
    }

    return pairs;
}

char* decompress(const Pair* pairs, size_t pairCount, size_t& outTextLength) {
    if (pairs == nullptr || pairCount == 0) {
        outTextLength = 0;
        return nullptr;
    }

    Dictionary dict(16);

    // Paso 1: Calcular la longitud total que tendrá la cadena recuperada
    outTextLength = 0;
    for (size_t i = 0; i < pairCount; ++i) {
        outTextLength += getPhraseLength(dict, pairs[i].index);
        if (pairs[i].character != '\0') {
            outTextLength++;
            dict.insert(pairs[i].index, pairs[i].character);
        }
    }

    // Paso 2: Asignar memoria exacta para el texto resultante (+1 para '\0' terminal)
    char* decompressedText = new char[outTextLength + 1];
    decompressedText[outTextLength] = '\0';

    // Reconstrucción del texto
    dict.clear(); // Reiniciamos el diccionario para el proceso de escritura
    dict.resize();

    size_t writePos = 0;
    for (size_t i = 0; i < pairCount; ++i) {
        unsigned int idx = pairs[i].index;
        char c = pairs[i].character;

        // Si el índice es mayor a 0, extraemos el prefijo del diccionario
        if (idx > 0) {
            size_t phraseLen = getPhraseLength(dict, idx);
            getPhrase(dict, idx, decompressedText + writePos);
            writePos += phraseLen;
        }

        // Agregamos el carácter de extensión si no es el delimitador final
        if (c != '\0') {
            decompressedText[writePos++] = c;
            dict.insert(idx, c);
        }
    }

    return decompressedText;
}
}
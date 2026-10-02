#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <cstddef>

namespace FileHandler {
// Lee un archivo binario y devuelve un puntero a un arreglo de bytes
unsigned char* readFile(const char* filepath, std::size_t& outLength);

// Escribe un arreglo de bytes en un archivo binario
void writeFile(const char* filepath, const unsigned char* buffer, std::size_t length);
}

#endif // FILEHANDLER_H

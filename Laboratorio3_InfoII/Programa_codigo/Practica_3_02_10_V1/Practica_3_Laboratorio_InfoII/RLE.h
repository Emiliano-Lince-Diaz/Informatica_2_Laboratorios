#ifndef RLE_H
#define RLE_H

#include <string>

namespace RLE {
// Genera la versión comprimida usando RLE
std::string compress(const std::string& input);

// Implementa el proceso inverso para recuperar la cadena original
std::string decompress(const std::string& input);
}

#endif // RLE_H

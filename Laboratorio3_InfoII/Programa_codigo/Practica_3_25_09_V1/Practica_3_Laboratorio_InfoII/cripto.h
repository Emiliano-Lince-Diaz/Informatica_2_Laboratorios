#ifndef CRIPTO_H
#define CRIPTO_H

#include <cstddef> // Para std::size_t

namespace Cripto {
// Desplaza los bits de un byte hacia la izquierda n posiciones de forma circular
unsigned char rotateLeft(unsigned char byte, int n);

// Desplaza los bits de un byte hacia la derecha n posiciones de forma circular
unsigned char rotateRight(unsigned char byte, int n);

// Encripta un arreglo de bytes en el lugar (In-Place)
void encrypt(unsigned char* data, std::size_t length, unsigned char key, int n);

// Desencripta un arreglo de bytes en el lugar (In-Place)
void decrypt(unsigned char* data, std::size_t length, unsigned char key, int n);
}

#endif // CRIPTO_H

#include "cripto.h"

using namespace std;

namespace Cripto {

unsigned char rotateLeft(unsigned char byte, int n) {
    n = n % 8; // Garantiza desplazamiento seguro entre 0 y 7
    return static_cast<unsigned char>((byte << n) | (byte >> (8 - n)));
}

unsigned char rotateRight(unsigned char byte, int n) {
    n = n % 8; // Garantiza desplazamiento seguro entre 0 y 7
    return static_cast<unsigned char>((byte >> n) | (byte << (8 - n)));
}

void encrypt(unsigned char* data, size_t length, unsigned char key, int n) {
    if (data == nullptr || length == 0) return;

    for (size_t i = 0; i < length; ++i) {
        // 1. Rotación hacia la izquierda
        unsigned char rotated = rotateLeft(data[i], n);
        // 2. Operación XOR con la clave K
        data[i] = rotated ^ key;
    }
}

void decrypt(unsigned char* data, size_t length, unsigned char key, int n) {
    if (data == nullptr || length == 0) return;

    for (size_t i = 0; i < length; ++i) {
        // 1. XOR inverso con la misma clave K
        unsigned char unxored = data[i] ^ key;
        // 2. Rotación hacia la derecha para restaurar el byte original
        data[i] = rotateRight(unxored, n);
    }
}

}
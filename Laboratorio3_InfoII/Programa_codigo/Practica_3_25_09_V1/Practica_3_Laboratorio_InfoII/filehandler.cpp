#include "exceptions.h"
#include "filehandler.h"
#include <fstream>
#include <new>

using namespace std;

namespace FileHandler {

unsigned char* readFile(const char* filepath, size_t& outLength) {
    ifstream file(filepath, ios::binary | ios::ate);
    if (!file.is_open()) {
        throw FileNotFoundException(filepath);
    }

    streamsize fileSize = file.tellg();
    if (fileSize < 0) {
        file.close();
        throw CorruptedFileException("No se pudo determinar el tamano del archivo.");
    }

    outLength = static_cast<size_t>(fileSize);
    if (outLength == 0) {
        file.close();
        return nullptr;
    }

    file.seekg(0, ios::beg);

    unsigned char* buffer = nullptr;
    try {
        buffer = new unsigned char[outLength];
    } catch (const bad_alloc&) {
        file.close();
        throw MemoryAllocationException();
    }

    if (!file.read(reinterpret_cast<char*>(buffer), outLength)) {
        delete[] buffer;
        file.close();
        throw CorruptedFileException("Fallo al leer los datos del archivo.");
    }

    file.close();
    return buffer;
}

void writeFile(const char* filepath, const unsigned char* buffer, size_t length) {
    ofstream file(filepath, ios::binary);
    if (!file.is_open()) {
        throw FileNotFoundException(filepath);
    }

    if (length > 0 && buffer != nullptr) {
        file.write(reinterpret_cast<const char*>(buffer), length);
        if (!file.good()) {
            file.close();
            throw CorruptedFileException("Error durante la escritura del archivo.");
        }
    }

    file.close();
}

}
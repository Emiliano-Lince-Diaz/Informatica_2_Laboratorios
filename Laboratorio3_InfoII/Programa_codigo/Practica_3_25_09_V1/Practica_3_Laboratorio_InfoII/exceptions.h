#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// Excepción para archivos no encontrados
struct FileNotFoundException : public std::exception {
    std::string message;

    explicit FileNotFoundException(const std::string& filepath)
        : message("Error: El archivo '" + filepath + "' no existe o no se pudo abrir.") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Excepción para corrupción o error de lectura/escritura
struct CorruptedFileException : public std::exception {
    std::string message;

    explicit CorruptedFileException(const std::string& reason)
        : message("Error de Archivo: " + reason) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Excepción para fallos de asignación de memoria
struct MemoryAllocationException : public std::exception {
    const char* what() const noexcept override {
        return "Error Critico: Fallo en la asignacion dinamica de memoria.";
    }
};

#endif // EXCEPTIONS_H

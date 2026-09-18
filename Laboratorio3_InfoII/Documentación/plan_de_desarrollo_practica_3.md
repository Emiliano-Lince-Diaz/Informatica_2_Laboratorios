# Plan de Desarrollo y Cronograma de Trabajo: Práctica 3 C++
**Asignatura:** Informática 2 - Universidad de Antioquia  
**Duración del Sprint:** 7 Días (Plan Intensivo)  
**Autor:** Emiliano de jesus Lince Diaz - Estudiante Ing.Electrónica
**Rol:** Líder de Proyecto & Arquitecto de Software C++


---

## 1. Resumen Ejecutivo del Proyecto

El objetivo principal es construir una aplicación modular en C++ orientada a consola que integre algoritmos de **compresión sin pérdida** (RLE y LZ78) y **criptografía a nivel de bits** (Rotación de bits y XOR), con persistencia de datos en archivos de texto/binarios y un manejo robusto de excepciones.

### Restricciones Técnicas Críticas (C++ Strict Rules):
1. **`std::string`**: Permitido **únicamente** en el módulo RLE. Prohibido en el módulo LZ78 y encriptación.
2. **Contenedores STL**: Prohibido el uso de `std::vector`, `std::map`, `std::unordered_map` o similares en LZ78.
3. **Gestión de Memoria**: El diccionario de LZ78 y la manipulación de frases debe realizarse mediante **arreglos dinámicos manuales** (`new[]` / `delete[]`) y punteros.
4. **Manejo de Excepciones**: Implementar bloques `try-catch` y clases de excepciones personalizadas para gestión de archivos ausentes, punteros nulos o fallos de asignación.
5. **Operaciones Bitwise**: Manipulación explícita de bytes mediante máscaras y desplazamientos para rotación ($0 < n < 8$) y la propiedad idempotente del XOR ($A \oplus K \oplus K = A$).

---

## 2. Arquitectura Modular del Software

El proyecto se estructurará siguiendo el principio de responsabilidad única (SRP) mediante archivos de cabecera (`.hpp`) e implementación (`.cpp`):

```text
Practica3/
├── include/
│   ├── RLE.hpp            // Declaración de funciones de compresión/descompresión RLE
│   ├── LZ78.hpp           // Estructuras dinámicas y funciones para LZ78
│   ├── Cripto.hpp         // Funciones de rotación bitwise y XOR
│   ├── FileHandler.hpp    // Lectura/Escritura de archivos y persistencia
│   └── Exceptions.hpp     // Clases de excepción personalizadas
├── src/
│   ├── RLE.cpp
│   ├── LZ78.cpp
│   ├── Cripto.cpp
│   ├── FileHandler.cpp
│   └── main.cpp           // Menú interactivo e integración completa
└── Makefile / CMakeLists.txt (Opcional para compilación rápida)
```

---

## 3. Cronograma de Desarrollo (Sprint de 7 Días)

| Día | Módulo / Fase | Entregable Principal | Horas Est. |
| :--- | :--- | :--- | :---: |
| **Día 1** | Configuración & Módulo RLE | `RLE.hpp` / `RLE.cpp` totalmente funcional y probado. | 3.5h |
| **Día 2** | Diseño Estructuras Dinámicas LZ78 | Estructura `DictionaryEntry` y arreglo dinámico redimensionable. | 4.0h |
| **Día 3** | Algoritmo LZ78 (Compress & Decompress) | `LZ78.hpp` / `LZ78.cpp` sin *memory leaks*. | 5.0h |
| **Día 4** | Módulo de Criptografía (Bitwise) | `Cripto.hpp` / `Cripto.cpp` con rotación a izquierda/derecha y XOR. | 3.0h |
| **Día 5** | Persistencia en Archivos y Excepciones | `FileHandler` y Jerarquía de Excepciones integradas. | 4.0h |
| **Día 6** | Integración del Sistema & CLI | Aplicación ejecutable `main.cpp` unificando el flujo completo. | 4.5h |
| **Día 7** | Testing, Valgrind y Documentación | Código refactorizado, validación de dataset y memoria limpia. | 3.0h |

---

## 4. Desglose Detallado por Día

### Día 1: Arquitectura Base y Módulo RLE
- **Objetivos:**
  - Crear la estructura del directorio de proyecto.
  - Diseñar e implementar el módulo RLE utilizando `std::string`.
- **Estrategia C++:**
  - Compresión: Recorrer la cadena contando caracteres contiguos idénticos.
  - Descompresión: Leer el entero multiplicador y duplicar el carácter correspondiente.
- **Criterio de Aceptación:**
  - Probar con cadenas como `"AAAABBBCC"` $\rightarrow$ `"4A3B2C"` y garantizar que la descompresión recupere el valor original exactamente.

### Día 2: Abstracción de Memoria Dinámica para LZ78
- **Objetivos:**
  - Diseñar la estructura de un par `(índice, carácter)` y el Diccionario Dinámico.
- **Estrategia C++:**
  ```cpp
  struct Pair {
      unsigned int index;
      char character;
  };

  struct DictEntry {
      unsigned int prefixIndex;
      char character;
  };
  ```
  - Implementar una clase o estructura `Dictionary` que gestione un arreglo dinámico de `DictEntry` que crezca según sea necesario (`capacity *= 2`).
- **Criterio de Aceptación:**
  - Probar independientemente la inserción y búsqueda de prefijos en el diccionario sin usar `std::vector`.

### Día 3: Algoritmo LZ78 Completo
- **Objetivos:**
  - Implementar `LZ78_compress` y `LZ78_decompress`.
- **Estrategia C++:**
  - **Compresión:** Recorrer el buffer de entrada, buscar la coincidencia más larga en el diccionario. Emitir par `(index, c)` e insertar nueva entrada.
  - **Descompresión:** Leer arreglo de pares, reconstruir la cadena concatenando recursivamente o iterativamente el prefijo más el carácter.
- **Criterio de Aceptación:**
  - Validar el algoritmo con el ejemplo del enunciado: `"ABAABABA"`.
  - Liberar la memoria con `delete[]` correctamente al finalizar cada proceso.

### Día 4: Módulo de Encriptación y Criptografía Bitwise
- **Objetivos:**
  - Implementar funciones para rotación de bits y encriptación/desencriptación con XOR.
- **Estrategia C++:**
  - **Rotación Izquierda (n bits):** `(unsigned char)((byte << n) | (byte >> (8 - n)))`
  - **Rotación Derecha (n bits):** `(unsigned char)((byte >> n) | (byte << (8 - n)))`
  - **XOR:** `byte ^ K`
  - **Orden Encriptación:** Rotación izquierda por $n$ $\rightarrow$ XOR con clave $K$.
  - **Orden Desencriptación:** XOR con clave $K$ $\rightarrow$ Rotación derecha por $n$.
- **Criterio de Aceptación:**
  - Comprobar la propiedad $A \oplus K \oplus K = A$ y la reversibilidad completa de cualquier `unsigned char`.

### Día 5: Manejo de Archivos y Excepciones
- **Objetivos:**
  - Crear módulo `FileHandler` utilizando `std::fstream` (modo binario y texto).
  - Definir clases de excepciones derivadas de `std::exception`.
- **Estrategia C++:**
  - Excepciones personalizadas: `FileNotFoundException`, `CorruptedFileException`, `MemoryAllocationException`.
  - Manejo seguro de memoria en caso de lanzar excepciones (Garantía de Exception Safety).
- **Criterio de Aceptación:**
  - El programa no debe cerrarse bruscamente si el archivo de entrada no existe o está corrupto; debe capturar la excepción y notificar al usuario.

### Día 6: Integración y Menú Interactiva (CLI)
- **Objetivos:**
  - Unificar todos los módulos en `main.cpp`.
- **Flujo de Trabajo:**
  1. Selección de método de compresión (1: RLE, 2: LZ78).
  2. Leer archivo de entrada.
  3. Comprimir datos.
  4. Encriptar resultado (ingresar clave $K$ y desplazamiento $n$).
  5. Guardar archivo procesado.
  6. Leer archivo procesado, desencriptar, descomprimir y guardar resultado final.
  7. Comparar archivo original vs resultado final.

### Día 7: Pruebas de Estrés, Sanitizers y Entrega
- **Objetivos:**
  - Ejecutar el programa contra el dataset de prueba provisto por el docente.
  - Verificar ausencia de fugas de memoria (*Memory Leaks*).
- **Herramientas de Validación:**
  - Compilar con flags: `-Wall -Wextra -pedantic -fsanitize=address,undefined`.
  - Verificar que no existan accesos inválidos fuera de límites de arreglos.

---

## 5. Riesgos Identificados y Estrategias de Mitigación

1. **Riesgo:** Fugas de memoria al redimensionar el diccionario en LZ78.
   - *Mitigación:* Implementar una función helper `reallocate()` que copie los datos a un nuevo puntero y destruya de inmediato el arreglo viejo.
2. **Riesgo:** Comportamiento indefinido en desplazamientos de bits en C++.
   - *Mitigación:* Garantizar el uso exclusivo de `unsigned char` para evitar *sign extension* indeseada en variables `char` estándar.
3. **Riesgo:** Pérdida de caracteres nulos (`\0`) durante la compresión o encriptación.
   - *Mitigación:* Manejar los buffers binarios utilizando tamaños/longitudes explícitas (`size_t`) en lugar de depender del caracter delimitador nulo.
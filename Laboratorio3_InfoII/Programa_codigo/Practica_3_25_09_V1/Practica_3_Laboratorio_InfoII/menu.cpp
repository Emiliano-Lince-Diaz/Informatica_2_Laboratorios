#include "menu.h"
#include "RLE.h"
#include "lz78.h"
#include "filehandler.h"
#include "exceptions.h"
#include "cripto.h"
#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

namespace Menu {

int leerOpcion(int minOpcion, int maxOpcion) {
    int opcion;
    while (true) {
        cout << "\nSeleccione una opcion (" << minOpcion << " - " << maxOpcion << "): ";
        if (cin >> opcion) {
            if (opcion >= minOpcion && opcion <= maxOpcion) {
                return opcion;
            } else {
                cout << "[ERROR] Opcion fuera de rango. Intente de nuevo.\n";
            }
        } else {
            cout << "[ERROR] Entrada invalida. Ingrese un numero entero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void ejecutarFlujoCompleto() {
    cout << "\n========================================\n";
    cout << "      FLUJO COMPLETO DE PROCESAMIENTO   \n";
    cout << "========================================\n";

    // Limpiamos cualquier '\n' pendiente en el buffer antes de leer la linea
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string rutaEntrada;
    cout << "Ingrese la ruta del archivo de entrada: ";
    getline(cin, rutaEntrada);

    // Eliminar comillas dobles al inicio y al final si el usuario copio la ruta con ellas
    if (!rutaEntrada.empty() && rutaEntrada.front() == '"' && rutaEntrada.back() == '"') {
        rutaEntrada = rutaEntrada.substr(1, rutaEntrada.length() - 2);
    }

    cout << "\nSeleccione el metodo de compresion:\n";
    cout << "1. RLE\n";
    cout << "2. LZ78\n";
    int metodoCompresion = leerOpcion(1, 2);

    cout << "\nParametros de Criptografia:\n";
    cout << "Ingrese la clave K (0 - 255): ";
    unsigned char claveK = static_cast<unsigned char>(leerOpcion(0, 255));

    cout << "Ingrese el desplazamiento de rotacion n (1 - 7): ";
    int shiftN = leerOpcion(1, 7);

    try {
        // 1. Lectura del archivo original
        size_t lenOriginal = 0;
        unsigned char* rawBuffer = FileHandler::readFile(rutaEntrada.c_str(), lenOriginal);
        cout << "\n[OK] Archivo leido exitosamente (" << lenOriginal << " bytes).\n";

        unsigned char* bufferAEncriptar = nullptr;
        size_t lenBufferAEncriptar = 0;

        // 2. Compresión
        if (metodoCompresion == 1) { // RLE
            string textoEntrada(reinterpret_cast<char*>(rawBuffer), lenOriginal);
            string textoComprimido = RLE::compress(textoEntrada);

            lenBufferAEncriptar = textoComprimido.length();
            bufferAEncriptar = new unsigned char[lenBufferAEncriptar];
            memcpy(bufferAEncriptar, textoComprimido.c_str(), lenBufferAEncriptar);

            cout << "[OK] Compresion RLE finalizada. Tamano: " << lenBufferAEncriptar << " bytes.\n";
        }
        else { // LZ78
            size_t pairCount = 0;
            Pair* pairs = LZ78::compress(reinterpret_cast<char*>(rawBuffer), lenOriginal, pairCount);

            // Serialización binaria: [pairCount (sizeof(size_t))] + [Pairs...]
            lenBufferAEncriptar = sizeof(size_t) + (pairCount * sizeof(Pair));
            bufferAEncriptar = new unsigned char[lenBufferAEncriptar];

            memcpy(bufferAEncriptar, &pairCount, sizeof(size_t));
            memcpy(bufferAEncriptar + sizeof(size_t), pairs, pairCount * sizeof(Pair));

            delete[] pairs;
            cout << "[OK] Compresion LZ78 finalizada (" << pairCount << " pares emitidos).\n";
        }

        delete[] rawBuffer; // Liberación del buffer original

        // 3. Encriptación
        Cripto::encrypt(bufferAEncriptar, lenBufferAEncriptar, claveK, shiftN);
        cout << "[OK] Encriptacion bitwise aplicada correctamente.\n";

        // 4. Guardar archivo procesado
        const char* rutaBinaria = "procesado_encriptado.bin";
        FileHandler::writeFile(rutaBinaria, bufferAEncriptar, lenBufferAEncriptar);
        cout << "[OK] Archivo binario guardado en: '" << rutaBinaria << "'\n";

        delete[] bufferAEncriptar;

        // 5. Lectura y Proceso Inverso
        cout << "\n--- Iniciando Desencriptacion y Descompresion ---\n";
        size_t lenBinarioLeido = 0;
        unsigned char* bufferEncriptadoLeido = FileHandler::readFile(rutaBinaria, lenBinarioLeido);

        // 6. Desencriptación
        Cripto::decrypt(bufferEncriptadoLeido, lenBinarioLeido, claveK, shiftN);
        cout << "[OK] Desencriptacion completada.\n";

        // 7. Descompresión
        unsigned char* bufferFinalDescomprimido = nullptr;
        size_t lenFinalDescomprimido = 0;

        if (metodoCompresion == 1) { // RLE
            string textoComprimidoRecuperado(reinterpret_cast<char*>(bufferEncriptadoLeido), lenBinarioLeido);
            string textoDescomprimido = RLE::decompress(textoComprimidoRecuperado);

            lenFinalDescomprimido = textoDescomprimido.length();
            bufferFinalDescomprimido = new unsigned char[lenFinalDescomprimido];
            memcpy(bufferFinalDescomprimido, textoDescomprimido.c_str(), lenFinalDescomprimido);
        }
        else { // LZ78
            size_t pairCountRecuperado = 0;
            memcpy(&pairCountRecuperado, bufferEncriptadoLeido, sizeof(size_t));

            Pair* pairsRecuperados = reinterpret_cast<Pair*>(bufferEncriptadoLeido + sizeof(size_t));

            char* textoRecuperado = LZ78::decompress(pairsRecuperados, pairCountRecuperado, lenFinalDescomprimido);
            bufferFinalDescomprimido = reinterpret_cast<unsigned char*>(textoRecuperado);
        }

        delete[] bufferEncriptadoLeido;

        // 8. Guardar resultado final
        const char* rutaResultado = "resultado_descomprimido.txt";
        FileHandler::writeFile(rutaResultado, bufferFinalDescomprimido, lenFinalDescomprimido);
        cout << "[OK] Texto final restaurado guardado en: '" << rutaResultado << "'\n";

        delete[] bufferFinalDescomprimido;

        cout << "\n========================================\n";
        cout << " [EXITO] Proceso finalizado sin errores \n";
        cout << "========================================\n";

    } catch (const FileNotFoundException& e) {
        cout << "\n[EXCEPTION CAPTURADA]: " << e.what() << "\n";
    } catch (const CorruptedFileException& e) {
        cout << "\n[EXCEPTION CAPTURADA]: " << e.what() << "\n";
    } catch (const MemoryAllocationException& e) {
        cout << "\n[EXCEPTION CAPTURADA]: " << e.what() << "\n";
    } catch (const exception& e) {
        cout << "\n[ERROR GENERAL]: " << e.what() << "\n";
    }
}

void mostrarMenuPruebas() {
    bool enSubmenu = true;

    while (enSubmenu) {
        cout << "\n========================================\n";
        cout << "          MENU DE PRUEBAS               \n";
        cout << "========================================\n";
        cout << "1. Probar Algoritmo RLE\n";
        cout << "2. Probar Algoritmo LZ78 Completo\n";
        cout << "3. Probar Criptografia Bitwise\n";
        cout << "4. Probar Archivos y Excepciones\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "========================================\n";

        int opcion = leerOpcion(0, 4);

        switch (opcion) {
        case 1: {
            cout << "\n--- PRUEBA RLE ---\n";
            string textoPrueba = "AAAABBBCC 7777   9999";
            string comp = RLE::compress(textoPrueba);
            string decomp = RLE::decompress(comp);
            cout << "Original:     " << textoPrueba << "\n";
            cout << "Comprimido:   " << comp << "\n";
            cout << "Recuperado:   " << decomp << "\n";
            cout << "Estado: " << (textoPrueba == decomp ? "[CORRECTO]" : "[ERROR]") << "\n";
            break;
        }
        case 2: {
            cout << "\n--- PRUEBA LZ78 COMPLETO ---\n";
            const char* textoOriginal = "ABAABABA 101010 111111";
            size_t lenOriginal = strlen(textoOriginal);

            size_t pairCount = 0;
            Pair* pairs = LZ78::compress(textoOriginal, lenOriginal, pairCount);

            cout << "Texto Original: " << textoOriginal << "\n";
            cout << "Pares Emitidos: ";
            for (size_t i = 0; i < pairCount; ++i) {
                cout << "(" << pairs[i].index << ", '" << pairs[i].character << "') ";
            }
            cout << "\n";

            size_t lenRecuperada = 0;
            char* textoRecuperado = LZ78::decompress(pairs, pairCount, lenRecuperada);

            cout << "Texto Recuperado: " << textoRecuperado << "\n";
            bool coinciden = (strcmp(textoOriginal, textoRecuperado) == 0);
            cout << "Estado: " << (coinciden ? "[CORRECTO]" : "[ERROR]") << "\n";

            delete[] pairs;
            delete[] textoRecuperado;
            break;
        }
        case 3: {
            cout << "\n--- PRUEBA CRIPTOGRAFIA BITWISE ---\n";
            const char* mensajeOriginal = "Mensaje Secreto C++";
            size_t len = strlen(mensajeOriginal);

            cout << "Ingrese la clave K (0 - 255): ";
            unsigned char claveK = static_cast<unsigned char>(leerOpcion(0, 255));

            cout << "Ingrese el desplazamiento de rotacion n (1 - 7): ";
            int shiftN = leerOpcion(1, 7);

            unsigned char* buffer = new unsigned char[len + 1];
            memcpy(buffer, mensajeOriginal, len);
            buffer[len] = '\0';

            cout << "\n[1] Original:    " << mensajeOriginal << "\n";

            Cripto::encrypt(buffer, len, claveK, shiftN);
            cout << "[2] Encriptado (hex): ";
            for (size_t i = 0; i < len; ++i) {
                cout << hex << (int)buffer[i] << " ";
            }
            cout << dec << "\n";

            Cripto::decrypt(buffer, len, claveK, shiftN);
            buffer[len] = '\0';
            cout << "[3] Desencriptado: " << buffer << "\n";

            bool exito = (strcmp((char*)buffer, mensajeOriginal) == 0);
            cout << "Estado: " << (exito ? "[EXITO]" : "[ERROR]") << "\n";

            delete[] buffer;
            break;
        }
        case 4: {
            cout << "\n--- PRUEBA PERSISTENCIA Y EXCEPCIONES ---\n";
            const char* testFilename = "test_output.bin";
            const char* textToWrite = "Prueba de persistencia en disco con C++";
            size_t writeLen = strlen(textToWrite);

            try {
                cout << "[1] Escribiendo archivo '" << testFilename << "'...\n";
                FileHandler::writeFile(testFilename, reinterpret_cast<const unsigned char*>(textToWrite), writeLen);

                cout << "[2] Leyendo archivo '" << testFilename << "'...\n";
                size_t readLen = 0;
                unsigned char* readBuffer = FileHandler::readFile(testFilename, readLen);

                cout << "    Contenido leido (" << readLen << " bytes): ";
                for (size_t i = 0; i < readLen; ++i) {
                    cout << static_cast<char>(readBuffer[i]);
                }
                cout << "\n";
                delete[] readBuffer;

                cout << "[3] Forzando excepcion leyendo archivo inexistente...\n";
                size_t dummyLen = 0;
                unsigned char* dummyBuffer = FileHandler::readFile("archivo_fantasma.bin", dummyLen);
                delete[] dummyBuffer;

            } catch (const FileNotFoundException& e) {
                cout << "    [CAPTURADO FileNotFoundException]: " << e.what() << "\n";
            } catch (const exception& e) {
                cout << "    [CAPTURADO EXCEPCION GENERICA]: " << e.what() << "\n";
            }
            break;
        }
        case 0:
            enSubmenu = false;
            break;
        }
    }
}

void mostrarMenuPrincipal() {
    bool ejecutando = true;

    while (ejecutando) {
        cout << "\n========================================\n";
        cout << "       SISTEMA PRINCIPAL C++            \n";
        cout << "========================================\n";
        cout << "1. Procesar Archivo (Compresion + Criptografia)\n";
        cout << "2. Seccion de Pruebas Unitarias\n";
        cout << "0. Salir\n";
        cout << "========================================\n";

        int opcion = leerOpcion(0, 2);

        switch (opcion) {
        case 1:
            ejecutarFlujoCompleto();
            break;
        case 2:
            mostrarMenuPruebas();
            break;
        case 0:
            cout << "\nSaliendo del sistema...\n";
            ejecutando = false;
            break;
        }
    }
}
}
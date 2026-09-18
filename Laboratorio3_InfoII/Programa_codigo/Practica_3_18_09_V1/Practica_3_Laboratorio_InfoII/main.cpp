#include <iostream>
#include <string>
#include "RLE.hpp"

using namespace std;

int main()
{
    string original = "AAAABBBCC";
    string compressed = RLE::compress(original);
    string decompressed = RLE::decompress(compressed);

    cout << "Original:     " << original << "\n";
    cout << "Comprimido:   " << compressed << "\n";
    cout << "Descomprimido: " << decompressed << "\n";

    if (original == decompressed) {
        cout << "\n[EXITO] La cadena original coincide con la descompresion.\n";
    } else {
        cout << "\n[ERROR] Hay perdida o alteracion de datos.\n";
    }
    return 0;
}

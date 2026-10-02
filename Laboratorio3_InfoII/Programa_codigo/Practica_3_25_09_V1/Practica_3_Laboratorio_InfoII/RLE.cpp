#include "RLE.h"
#include <cctype>
#include <string>

using namespace std;

namespace RLE {

string compress(const string& input) {
    if (input.empty()) return "";

    string compressed = "";
    int count = 1;

    for (size_t i = 0; i < input.length(); ++i) {
        if (i + 1 < input.length() && input[i] == input[i + 1]) {
            count++;
        } else {
            // Formato delimitado: cantidad[carácter]
            compressed += to_string(count) + "[" + input[i] + "]";
            count = 1;
        }
    }
    return compressed;
}

string decompress(const string& input) {
    if (input.empty()) return "";

    string decompressed = "";
    string numberStr = "";

    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '[') {
            // El carácter literal está ubicado inmediatamente después de '['
            if (i + 1 < input.length() && !numberStr.empty()) {
                int count = stoi(numberStr);
                char c = input[i + 1];

                decompressed.append(count, c);
                numberStr = ""; // Reiniciamos el acumulador de número
                i += 2; // Saltamos el carácter leído y el ']' de cierre
            }
        } else if (isdigit(input[i])) {
            numberStr += input[i];
        }
    }
    return decompressed;
}

}
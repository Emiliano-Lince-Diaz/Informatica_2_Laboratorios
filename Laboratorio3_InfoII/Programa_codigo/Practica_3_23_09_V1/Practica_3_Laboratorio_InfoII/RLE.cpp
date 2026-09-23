#include "RLE.h"
#include <cctype>
using namespace std;

namespace RLE{

string compress(const string& input){
    if(input.empty()) return "";

    string compressed="";
    int count = 1;

    for(size_t i=0; i<input.length();++i){
        // Si el carácter actual es igual al anterior, incrementamos el contador
        if (i < input.length() && input[i] == input[i + 1]) {
            count++;
        }else {
            // Si cambia o llegamos al final, concatenamos la cuenta y el carácter
            compressed += to_string(count) + input[i];
            count = 1; // Reiniciamos el contador para el nuevo carácter
        }
    }
    return compressed;
}

string decompress(const string& input) {
    if (input.empty()) return "";

    string decompressed = "";
    string numberStr = "";

    for (size_t i = 0; i < input.length(); ++i) {
        if (isdigit(input[i])) {
            // Acumulamos los dígitos para formar el número completo
            numberStr += input[i];
        } else {
            // Cuando encontramos un carácter, lo multiplicamos por el número leído
            if (!numberStr.empty()) {
                int count = stoi(numberStr);
                decompressed += string(count, input[i]);
                numberStr = ""; // Reiniciamos el acumulador numérico
            }
        }
    }
    return decompressed;
}

}
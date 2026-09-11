#include <iostream>

using namespace std;

float PI = 3.1416;


int Residuo(int a, int b){
    return a % b;
}

bool ParOImpar(int a){
    if(a & 1){
        return false;
    }else{
        return true;
    }
}



void Ejercicio1(){
    int a, b;
    cout << "Elija un valor para a: " << endl;
    cin >> a;
    cout << "Elija un valor para b: " << endl;
    cin >> b;
    cout << "El residuo de la division entre " << a << "/" << b << " es: " << Residuo(a,b) << endl;
}


void Ejercicio2(){
    int N;
    bool flag;
    cout << "Elija un valor para N: " << endl;
    cin >> N;
    flag = ParOImpar(N);
    if (flag){
        cout << "El numero N es par " << endl;
    }else{
        cout << "El numero N es impar " << endl;
    }
}


/*
Ejercicio 3. Escriba un programa que pida dos números A y B e imprima en pantalla el mayor.
Ej: si se ingresan 7 y 3 se debe imprimir:
El mayor es 7
Ejercicio 4. Escriba un programa que pida dos números A y B e imprima en pantalla el menor.
Ej: si se ingresan 7 y 3 se debe imprimir:
El menor es 3
*/



int main()
{
    int N;
    while (true) {
        cout << "Escoja el ejercicio que quiere ejecutar: " << endl;
        cin >> N;
        switch (N) {
        case 1:
            Ejercicio1();
            break;
        case 2:
            Ejercicio2();
            break;
        default:
            cout << "Numero de ejercicio no valido. " << endl;
            break;
        }
    }

    return 0;
}

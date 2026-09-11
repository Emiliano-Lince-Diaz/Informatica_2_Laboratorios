#include<funciones.h>
#include<algorithm>

using namespace std;

//Funcion problema 3
bool compararCadenas(char cadena1[],char cadena2[]){
    int i=0;

    while(cadena1[i] != '\0' || cadena2[i] != '\0'){
        if(cadena1[i]!=cadena2[i]){
            return false;
        }
        i++;
    }

    return true;
}

//Funcion problema 5
void numeroCadena(int numero, char cadena[]){
    int i = 0,num,caracter;

    if (numero == 0){
        cadena[i] = '0';
        i++;
        cadena[i] = '\0';
        return;
    }

    while(numero>0){
        num = numero % 10;
        caracter = num + '0';
        cadena[i]= caracter;
        i++;
        numero = numero / 10;
    }
    cadena[i] = '\0';

    for(int primero=0, ultimo=i-1;primero<ultimo;primero++,ultimo--){
        char cad;
        cad = cadena[primero];
        cadena[primero] = cadena[ultimo];
        cadena[ultimo] = cad;
    }
}

//Funcion problema 13

int contarEstrellas(int *ptrGalaxia, int filas, int columnas){
    int cantidad = 0;

    for(int i=1;i<filas-1;i++){
        for(int j=1;j<columnas-1;j++){

            int centro = *(ptrGalaxia+(i * columnas) + j);
            int arriba = *(ptrGalaxia+((i-1) * columnas) + j);
            int abajo = *(ptrGalaxia+((i+1) * columnas) + j);
            int izquierda = *(ptrGalaxia+(i * columnas) + (j-1));
            int derecha = *(ptrGalaxia+(i * columnas) + (j+1));

            if((centro + arriba+ abajo + izquierda + derecha) > 30){
                cantidad++;
            }
        }
    }

    return cantidad;
}

//Funcion problema 15
void interseccion(int A[], int B[], int C[]){
    C[0] = max(A[0],B[0]);
    C[1] = max(A[1],B[1]);

    int derechaA = A[0] + A[2];
    int inferiorA = A[1] + A[3];

    int derechaB = B[0] + B[2];
    int inferiorB = B[1] + B[3];

    int derechaC = min(derechaA, derechaB);
    int inferiorC = min(inferiorA, inferiorB);

    C[2] = derechaC - C[0];
    C[3] = inferiorC - C[1];

    if(C[2]<=0 || C[3]<=0){
        C[0] = 0;
        C[1] = 0;
        C[2] = 0;
        C[3] = 0;
    }
}

//Funcion problema 17
int sumaDivisor(int n){
    int suma = 0;

    for(int i=1;i<=n/2;i++){
        if(n%i==0){
            suma = suma + i;
        }
    }

    return suma;
}

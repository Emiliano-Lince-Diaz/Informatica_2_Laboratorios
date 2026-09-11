#include <iostream>
#include <limits>
#include<funciones.h>

using namespace std;


int main()
{
    int ejercicio;

    do {
        cout<<"\n\n1. Cantidad de dinero"<<endl;
        cout<<"3. Comparacion de dos cadenas"<<endl;
        cout<< "5. Convertir entero a cadena de caracteres"<<endl;
        cout<<"7. Eliminacion caracteres repetidos"<<endl;
        cout<<"9. Suma de n cifras"<<endl;
        cout<<"11. Cine"<<endl;
        cout<<"13. Fotografia de estrellas"<<endl;
        cout<<"15. Interseccion de rectangulos"<<endl;
        cout<<"17. Numeros amigables"<<endl;
        cout <<"0. Salir" << endl;
        cout<<"Ingrese el numero del ejercicio a resolver: "<<endl;

        if(cin >> ejercicio) {

        switch(ejercicio){

        case 0:
            cout << "Saliste" << endl;
            break;

        case 1:{

            /*Se necesita un programa que permita determinar la mínima combinación de billetes y monedas para una cantidad de dinero determinada.
            Los billetes en circulación son de $50.000, $20.000, $10.000, $5.000, $2.000 y $1.000, y las monedas son de $500, $200, $100 y $50.
            Haz un programa que entregue el número de billetes y monedas de cada denominación para completar la cantidad deseada.
            Si por medio de los billetes y monedas disponibles no se puede lograr la cantidad deseada, el sistema deberá decir lo que resta para lograrla.
            Usa arreglos y ciclos para realizar el programa.*/

            int denominaciones[]={50000,20000,10000,5000,2000,1000,500,200,100,50};
            int dinero;
            bool bandera = false;

            do{
                cout<<"Ingrese la cantidad de dinero: "<<endl;

                if(cin>>dinero){
                    if(dinero>=0){
                        bandera = true;
                    }
                    else{
                        cout<<"La cantidad debe ser positiva, ingrese un numero positivo"<<endl;
                    }
                }
                else{
                    cout<<"Ingresaste una letra, ingresa solo numeros"<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
            }while(!bandera);

            for(int i=0;i<10;i++){
                int cantidad =0;
                cantidad = dinero / denominaciones[i];
                cout << denominaciones[i]<<": "<<cantidad<<endl;
                dinero = dinero % denominaciones[i];
            }

            cout << "Faltante: "<< dinero;

            break;

            }

        case 3:{

            /*Haz una función que compare 2 cadenas de caracteres y retorne un valor lógico verdadero si son iguales, y falso en caso contrario,
            no olvides también tener en cuenta la longitud de las cadenas. Escribe un programa de prueba.*/

            char cadena1[30];
            char cadena2[30];

            cin.ignore();
            cout<<"Ingrese la primer cadena: ";
            cin.getline(cadena1,30);

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }

            cout<<"Ingrese la segunda cadena: ";
            cin.getline(cadena2,30);

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }

            if(compararCadenas(cadena1,cadena2) == false){
                cout<<"Las cadenas no son iguales";
            }
            else{
                cout<<"Las cadenas son iguales";
            }

            break;

            }

        case 5:{

            /*Haz una función que reciba un número entero (int) y lo convierta a cadena de caracteres.
            Usa parámetros por referencia para retornar la cadena. Escribe un programa de prueba.*/

            int numeroIng;
            char cadenaRes[30];
            bool bandera = false;

            do{
                cout<<"Ingrese el numero a convertir: ";

                if(cin>>numeroIng){
                    if(numeroIng>=0){
                        bandera = true;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }
                    else{
                        cout<<"El numero no puede ser negativo, ingrese un numero positivo"<<endl;
                    }
                }
                else{
                    cout<<"Ingresaste una letra, ingresa solo numeros"<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
            }while(!bandera);


            numeroCadena(numeroIng, cadenaRes);

            cout<<"El numero convertido a cadena de caracteres es: "<<cadenaRes;

            break;

            }

        case 7:{

            /*Escribe un programa que reciba una cadena de caracteres y elimina los caracteres repetidos.*/

            char cadenaOriginal[30];
            char cadenaSinRepetidos[30];
            bool bandera = false;
            int pos = 0;

            cin.ignore();
            cout<<"Ingrese la cadena original: ";
            cin.getline(cadenaOriginal,30);

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }

            for(int i=0;cadenaOriginal[i] != '\0' ;i++){
                bandera = false;
                for(int j=0;j<pos;j++){
                    if(cadenaOriginal[i]==cadenaSinRepetidos[j]){
                        bandera = true;
                        break;
                    }
                }
                if(bandera == false){
                    cadenaSinRepetidos[pos] = cadenaOriginal[i];
                    pos++;
                }
            }

            cadenaSinRepetidos[pos] = '\0';

            cout<<"Original: "<<cadenaOriginal<<"." "Sin repetidos: "<< cadenaSinRepetidos<<"."<<endl;

            break;

        }

        case 9:{

            /*Escribe un programa que reciba un número n y lea una cadena de caracteres numéricos, el programa debe separar la cadena de caracteres
            en números de n cifras, sumarlos e imprimir el resultado. En caso de no poderse dividir exactamente
            en números de n cifras se colocan ceros a la izquierda del primer número.*/

            int n, suma = 0, longitud = 0, actual = 0, faltante, temporal=0;
            char caracteresNumericos[30];
            bool banderaN = false, banderaCadena = false;

            //Entrada de datos y validaciones

            do{
                cout<<"Ingrese un numero que divide la cadena en n cifras: ";

                if(cin>>n){
                    if(n>0){
                        banderaN = true;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }
                    else{
                        cout<<"Ingresa un numero mayor a 0'\n'";
                    }
                }
                else{
                    cout<<"Ingresaste una letra, ingresa solo numeros'\n'";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
            }while(!banderaN);

            do{
                cout<<"Ingrese la cadena de caracteres numericos: ";
                cin.getline(caracteresNumericos,30);

                if(cin.fail()){
                    cout<<"La cadena es muy larga, solo se permiten 30 numeros\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    continue;
                }

                banderaCadena = true;

                for(int i = 0; caracteresNumericos[i] != '\0'; i++){
                    if(caracteresNumericos[i] < '0' || caracteresNumericos[i] > '9'){
                        cout<<"Ingresaste letras, ingresa solo numeros\n";
                        banderaCadena = false;
                        break;
                    }
                }
            }while(!banderaCadena);

            //Logica principal

            while(caracteresNumericos[longitud] != '\0'){
                longitud++;
            }

            faltante = longitud % n;

            if(faltante>0){
                temporal=0;

                for(int i=0;i<faltante;i++){
                    temporal = (temporal * 10) + caracteresNumericos[actual] - '0';
                    actual++;
                }
                suma = suma + temporal;
            }

            while(actual<longitud){
                temporal = 0;

                for(int i=0; i<n;i++){
                    temporal = (temporal * 10) + caracteresNumericos[actual] - '0';
                    actual ++;
                }
                suma = suma + temporal;
            }

            cout<<"Original: "<<caracteresNumericos<<"." <<endl<<"Suma: "<<suma<<"."<<endl;

            break;
        }

        case 11:{

            /*Escribe un programa que permita manejar las reservas de asientos en una sala de cine,
            estos están organizados en 15 filas con 20 (asientos) cada una.
            El programa debe mostrar una representación de la sala, que indique qué asientos están disponibles y cuales se encuentran reservados.
            Además, debe permitir realizar reservas o cancelaciones al ingresar la fila (letras A-O) y el número del asiento (números 1-20).*/

            char sala[15][20];
            int asiento, menuCine;
            char fila;
            bool salir = false;

            for(int i=0;i<15;i++){
                for(int j=0;j<20;j++){
                    sala[i][j] = '-';
                 }
            }

            do{
                cout << "\n   SALA DE CINE    " << endl;
                cout << "1. Ver sala" << endl;
                cout << "2. Reservar asiento" << endl;
                cout << "3. Cancelar reserva" << endl;
                cout << "4. Salir al menu principal" << endl;
                cout << "Seleccione una opcion: ";

                if(cin>>menuCine){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch(menuCine){
                    case 1:{
                        cout<<"\n    PANTALLA    "<<endl;
                        cout<<" ";
                        for(int j=1; j <=20; j++){
                            if(j<10){
                                cout<< j << "  ";
                            }
                            else{
                                cout<< j << " ";
                            }
                        }
                        cout<<endl;

                        for(int i =0;i<15; i++){
                            char letraFila = 'A'+ i;
                            cout<<letraFila<< " ";

                            for(int j=0;j<20;j++){
                                cout<<sala[i][j] << "  ";
                            }
                            cout << endl;
                        }
                    }
                    break;

                    case 2:{
                        cout<<"Reservar asiento"<<endl;
                        cout<<"Ingrese la letra de la fila de la A la O: ";cin>>fila;
                        cout<<"Ingrese el numero del asiento del 1 al 20: ";

                        if(cin>>asiento){
                            if(fila>='a' && fila<='o'){
                                fila = fila -32;
                            }

                            if(fila >= 'A'&& fila<='O' && asiento >= 1 && asiento <= 20){
                                int indFila = fila - 'A';
                                int indCol = asiento - 1;

                                if(sala[indFila][indCol]== '-'){
                                    sala[indFila][indCol]= '+';
                                    cout<<"EL asiento "<< fila<< asiento << " se reservo con exito"<<endl;
                                }
                                else{
                                    cout<<"EL asiento "<< fila<< asiento << " se encuentra ocupado"<<endl;
                                }
                            }
                            else{
                                cout<<"Coordenadas invalidas: Ingrese una fila de la A a la O y una columna del 1 al 20"<<endl;
                            }
                        }
                        else{
                            cout<<"El asiento debe ser un numero"<<endl;
                        }

                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    case 3:{
                        cout<<"     Cancelar asiento     "<<endl;
                        cout<<"Ingrese la letra de la fila de la A la O: ";cin>>fila;
                        cout<<"Ingrese el numero del asiento del 1 al 20: ";

                        if(cin>>asiento){
                            if(fila>='a' && fila<='o'){
                                fila = fila -32;
                            }

                            if(fila >= 'A'&& fila<='O' && asiento >= 1 && asiento <= 20){
                                int indFila = fila - 'A';
                                int indCol = asiento - 1;

                                if(sala[indFila][indCol]== '+'){
                                    sala[indFila][indCol]= '-';
                                    cout<<"EL asiento "<< fila<< asiento << " se cancelo con exito"<<endl;
                                }
                                else{
                                    cout<<"EL asiento "<< fila<< asiento << " no se encuentra ocupado"<<endl;
                                }
                            }
                            else{
                                cout<<"Coordenadas invalidas: Ingrese una fila de la A a la O y una columna del 1 al 20"<<endl;
                            }
                        }
                        else{
                            cout<<"El asiento debe ser un numero"<<endl;
                        }

                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        break;
                    }
                    case 4:{
                        cout<<"Saliendo del menu del cine"<<endl;
                        salir =true;
                        break;
                    }
                    default: cout<<"Error, ingrese un numero del 1 al 4"<<endl;
                        break;
                    }
                }
                else{
                    cout<<"Ingrese solo numeros"<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(salir==false);


            break;

        }

        case 13:{

            /*Elabora y prueba una función que reciba un puntero a la matriz de enteros como argumento y que retorne el número de estrellas
            encontradas en la imagen. Ignora las posibles estrellas que puedan existir en los bordes de la matriz.*/

            int galaxia[6][8] = {
                {0, 3, 4, 0, 0, 0, 6, 8},
                {5, 13, 6, 0, 0, 0, 2, 3},
                {2, 6, 2, 7, 3, 0, 10, 0},
                {0, 0, 4, 15, 4, 1, 6, 0},
                {0, 0, 7, 12, 6, 9, 10, 4},
                {5, 0, 6, 10, 6, 4, 8, 0}
            };

            int estrellas = contarEstrellas(&galaxia[0][0], 6, 8);

            cout<<"Se encontraron: "<<estrellas<< " estrellas en la fotografia.";

            break;
        }

        case 15:{

            /*Implementa una función que reciba 2 arreglos que representen los rectángulos A y B, y por referencia retorne un rectángulo C
             (con la misma estructura descrita anteriormente) que corresponda a la intersección de A y B, como se observa en la figura 6.*/


            int rectanguloA[4];
            int rectanguloB[4];
            int rectanguloC[4];
            bool banderaA = false;
            bool banderaB = false;

            do{
                cout<<"Ingrese los valores del rectangulo A"<<endl;
                cout<<"Ingrese X, Y, Ancho y Alto separados por espacios: ";

                if(cin>> rectanguloA[0] >> rectanguloA[1] >> rectanguloA[2] >> rectanguloA[3]){
                    if(rectanguloA[2]>0 && rectanguloA[3]>0){
                        banderaA = true;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else{
                        cout<<"El ancho y el alto deben ser mayores a cero"<<endl;
                    }
                }
                else{
                    cout<<"Ingresaste letras. Ingresa solo numeros"<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

            }while(!banderaA);

            do{
                cout<<"Ingrese los valores del rectangulo B"<<endl;
                cout<<"Ingrese X, Y, Ancho y Alto separados por espacios: ";

                if(cin>> rectanguloB[0] >> rectanguloB[1] >> rectanguloB[2] >> rectanguloB[3]){
                    if(rectanguloB[2]>0 && rectanguloB[3]>0){
                        banderaB = true;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else{
                        cout<<"El ancho y el alto deben ser mayores a cero"<<endl;
                    }
                }
                else{
                    cout<<"Ingresaste letras. Ingresa solo numeros"<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(!banderaB);


            interseccion(rectanguloA,rectanguloB,rectanguloC);

            if(rectanguloC[2]==0 || rectanguloC[3]==0){
                cout<<"Los rectangulos no se intersectan, El resultado es {0, 0, 0, 0}"<<endl;
            }
            else{
                cout<<"{"<<rectanguloC[0]<<" "<<rectanguloC[1]<<" "<<rectanguloC[2]<< " "<< rectanguloC[3]<<"}";
            }

            break;

         }

        case 17:{

            int n;
            int amigables = 0;
            bool bandera = false;

            do{
                cout<<"Ingrese un numero: ";
                if(cin>>n){
                    if(n>0){
                        bandera = true;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else{
                        cout<<"El numero debe ser mayor a 0"<<endl;
                    }
                }
                else{
                    cout<<"Ingresaste letras. Ingresa un numero"<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(!bandera);

            for(int i = 1; i<n; i++){
                int posibleAmigable = sumaDivisor(i);

                if(posibleAmigable != i && sumaDivisor(posibleAmigable) == i){
                    amigables = amigables + i;
                }
            }

            cout<<"El resultado de la suma es: "<<amigables<<endl;

            break;

        }

            default: cout<<"No esta en el rango de ejercicios";

            break;
        }
        } else {
            cout << "Error: Ingresaste letras. Ingresa un numero del menu." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ejercicio = -1;
        }

    } while (ejercicio != 0);


    return 0;
}
#include <iostream>

using namespace std;

float PI = 3.1416;


bool Consonante_Vocal(char c){
    char Minus = c;
    if (c>='A' && c<='Z'){
        Minus=c+32;
    }
    if (Minus=='a' || Minus=='e' || Minus=='i' || Minus=='o' || Minus=='u'){
        return true;
    }else{
        return false;
    }
}

int division_entera(int a, int b){
    return a/b;
}

int Minutos_totales(int H, int M){
    return H*60+M;
}

void Separar_Hor_Min(int N, int &horas, int &minutos){
    // Este simbolo "&" significa "Referencia"
    horas = N/100;
    minutos = N%100;
}

int Numero_Min_total(int M1, int M2){
    return (M1+M2)%1440;
}

float factorial(int N){
    float Fact=1;
    for (int i = 1; i <= N; ++i) {
        Fact = Fact*i;
    }
    return Fact;
}

float euler(int N){
    float e=0;
    for (int i = 0; i < N; ++i) {
        e=(1/factorial(i))+e;
    }
    return e;
}

int Multiplos_suma_2N(int x, int y, int N){
    int Total=0;
    for (int i = x; i < N; i+=x) {
        Total=Total + i;
    }
    for (int i = y; i < N; i+=y) {
        if(i%x!=0){
            Total=Total + i;
        }
    }
    return Total;
}

bool Primo(int x){
    for (int i = 2; i <= x/2; ++i) {
        if(x%i==0){
            return false;
        }
    }
    return true;
}

int MCD(int n){
    int max_prime=0;
    while (n % 2 == 0) {
        max_prime = 2;
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            max_prime = i;
            n /= i;
        }
    }
    if (n > 2) {
        max_prime = n;
    }
    return max_prime;
}

bool Palindromo(int numero) {
    int original = numero;
    int reverso = 0;

    while (numero > 0) {
        int digito = numero % 10;
        reverso = reverso * 10 + digito;
        numero /= 10;
    }

    return original == reverso;
}
int ContarCollatz(long long n) {
    int terminos = 1;
    while (n != 1) {
        if ((n & 1) == 0) {
            n = n / 2;
        } else {
            n = (3 * n) + 1;
        }
        terminos++;
    }
    return terminos;
}
void Bonus(long long n) {
    while (n != 1) {
        cout << n << ", ";
        if ((n & 1) == 0) {
            n = n / 2;
        } else {
            n = (3 * n) + 1;
        }
    }
    cout << "1" << endl;
}

void Problema1(){
    char c;
    cout << "Dame un caracter cualquiera: " << endl; cin >> c;
    if ((c>='A' && c<='Z') || (c>='a' && c<='z')){
        if(Consonante_Vocal(c)){
            cout << c << " Es una vocal. " << endl;
        }else{
            cout << c << " Es una consonante. " << endl;
        }
    }else{
        cout << c << " No es una letra. " << endl;
    }
}

void Problema2(){
    int N;
    cout << "Ingrese su valor N de dinero: " << endl; cin >> N;
    if (N>=0){
        int denominaciones[10] = {50000,20000,10000,5000,2000,1000,500,200,100,50};
        int cantidad_billetes[10];
        cout << "Del Valor " << N << " salen: " << endl;
        for (int i = 0; i < 10; ++i) {
            if (denominaciones[i] <= N){
                cantidad_billetes[i] = division_entera(N, denominaciones[i]);
                N = N-(denominaciones[i]*cantidad_billetes[i]);
            }else{
                cantidad_billetes[i] = division_entera(N, denominaciones[i]);
            }
            cout << denominaciones[i] << " : " << cantidad_billetes[i] << endl;
        }
        if (N<=denominaciones[9]){
            cout << "Faltante: " << N << endl;
        }
    }else{
        cout << "Formato ingresado Invalido!" << endl;
    }

}

void Problema4(){
    int N1, N2, H1, H2, M1, M2;
    cout << "Ingrese una primera hora: " << endl; cin >> N1;
    cout << "Ingrese una segunda hora: " << endl; cin >> N2;
    if(N1>=0 || N2>=0){
        Separar_Hor_Min(N1, H1, M1);
        Separar_Hor_Min(N2, H2, M2);
        if ((H1<24 && H1>=0) && (M1<60 && M1>=0)){
            if ((H2<24 && H2>=00) && (M2<60 && M2>=00)){
                M1 = Minutos_totales(H1,M1);
                M2 = Minutos_totales(H2,M2);
                int Min_total = Numero_Min_total(M1,M2);
                int Hora_result = Min_total/60;
                int Min_result = Min_total%60;
                int Formato = (Hora_result*100)+Min_result;
                cout << "La hora es: " << Formato << endl;
            }else{
                cout << N2 << " Es un tiempo invalido. " << endl;
            }
        }else{
            cout << N1 << " Es un tiempo invalido. " << endl;
        }
    }else{
        cout << "Formato ingresado invalido!" << endl;
    }
}

void Problema6(){
    int N;
    cout << "Dame un numero de elementos para la aproximacion de euler: " << endl;cin >> N;
    if (N>0){
        cout << "e es aproximadamente: " << euler(N) << endl;
    }else{
        cout << "Valor ingresado es invalido!, elija un valor mayor a 0 " << endl;
    }

}

void Problema8(){
    int a, b, c;
    bool flag=true;
    cout << "Dame un primer numero: " << endl;cin >> a;
    cout << "Dame un segundo numero: " << endl;cin >> b;
    cout << "Dame un tercer numero: " << endl;cin >> c;

    for (int i = a; i < c; i+=a) {
        if(!flag){
            cout << " + ";
        }
        cout << i;
        flag=false;
    }

    for (int i = b; i < c; i+=b) {
        if (i%a!=0){
            cout << " + ";
            cout << i;
        }
    }
    cout << " = " << Multiplos_suma_2N(a,b,c) << endl;
}


void Problema10(){
    int n, contador=0, x=1;
    cout << "Elija la poscicion de su primo fav ;) : " << endl;cin >> n;
    do{
        ++x;
        if(Primo(x)){
            ++contador;
        }

    }while (contador!=n);


    cout << "El primo numero " << n << " es: " << x << endl;
}

void Problema12(){
    int n, max_prime;
    cout << "Dame un numero para calcular su maximo factor primo: " << endl; cin >> n;

    max_prime = MCD(n);
    cout << "El mayor factor primo de " << n << " es: " << max_prime << "." << endl;
}

void Problema14(){
    int max_palindromo = 0;
    int factor1 = 0;
    int factor2 = 0;

    for (int i = 999; i >= 100; i--) {

        for (int j = i; j >= 100; j--) {
            int producto = i * j;
            if (producto <= max_palindromo) {
                break;
            }

            if (Palindromo(producto)) {
                max_palindromo = producto;
                factor1 = i;
                factor2 = j;
            }
        }
    }

    cout << factor1 << "*" << factor2 << "=" << max_palindromo << endl;
}
void Problema16(){
    int k;
    cout << "Ingrese el limite k: "; cin >> k;

    int mejor_semilla = 1;
    int max_terminos = 0;

    for (int j = 1; j < k; j++) {
        int terminos_actuales = ContarCollatz(j);

        if (terminos_actuales > max_terminos) {
            max_terminos = terminos_actuales;
            mejor_semilla = j;
        }
    }

    cout << "La serie mas larga es con la semilla: " << mejor_semilla
         << ", teniendo " << max_terminos << " terminos." << endl;

    cout << "La serie es: ";
    Bonus(mejor_semilla);

}
int main()
{
    int N;
    while (true) {
        cout << "Elija el problema a revisar: " << endl;
        cin >> N;
        switch (N) {
        case 1:
            Problema1();
            break;
        case 2:
            Problema2();
            break;
        case 4:
            Problema4();
            break;
        case 6:
            Problema6();
            break;
        case 8:
            Problema8();
            break;
        case 10:
            Problema10();
            break;
        case 12:
            Problema12();
            break;
        case 14:
            Problema14();
            break;
        case 16:
            Problema16();
            break;
        default:
            cout << "Opción invalida!. " << endl;
            break;
        }
    }
    return 0;
}

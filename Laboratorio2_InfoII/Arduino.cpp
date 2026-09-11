/*Problema 1

long denominaciones[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};

void setup() {
  Serial.begin(9600); // Inicializa la comunicación con el monitor serial
  Serial.println("Ingrese la cantidad de dinero:");
}

void loop() {
  // Espera hasta que el usuario escriba algo en el monitor serial
  if (Serial.available() > 0) {

    // parseInt() es genial: lee el texto y extrae solo el número.
    // Si metes letras, devuelve 0 (actuando como validación implícita)
    long dinero = Serial.parseInt();

    // Limpia el búfer por si quedó el carácter de salto de línea ("Enter")
    while(Serial.available() > 0) {
      Serial.read();
    }

    // Validación de números negativos (y el 0 de las letras)
    if (dinero > 0) {
      Serial.print("Monto ingresado: ");
      Serial.println(dinero);

      // Tu lógica de ciclo for
      for(int i = 0; i < 10; i++) {
        long cantidad = dinero / denominaciones[i];

        Serial.print(denominaciones[i]);
        Serial.print(": ");
        Serial.println(cantidad);

        dinero = dinero % denominaciones[i];
      }

      Serial.print("Faltante: ");
      Serial.println(dinero);
      Serial.println("--------------------");
      Serial.println("Ingrese una nueva cantidad:");

    } else {
      Serial.println("Error: Ingrese una cantidad numerica positiva.");
    }
  }
} */





/*Problema 6

 void setup() {
    Serial.begin(9600);
    Serial.println("Ingrese una cadena:");
}

void loop() {
    if (Serial.available() > 0) {
        // Leemos todo el texto hasta que el usuario presione Enter (\n)
        String original = Serial.readStringUntil('\n');
        original.trim(); // Limpia espacios o saltos de línea invisibles al final

        String mayuscula = ""; // Creamos un String vacío para guardar el resultado

        for (int i = 0; i < original.length(); i++) {
            char letra = original[i];

            if (letra >= 'a' && letra <= 'z') {
                mayuscula += (char)(letra - 32);
            } else {
                mayuscula += letra;
            }
        }

        Serial.print("Original: ");
        Serial.print(original);
        Serial.println(".");

        Serial.print("En mayuscula: ");
        Serial.print(mayuscula);
        Serial.println(".\n");
    }
}*/





/*Problema 10

// Función de valores (Pegarla arriba del setup)
int valorRomano(char c) {
    if (c == 'M') return 1000;
    if (c == 'D') return 500;
    if (c == 'C') return 100;
    if (c == 'L') return 50;
    if (c == 'X') return 10;
    if (c == 'V') return 5;
    if (c == 'I') return 1;
    return 0;
}

void setup() {
    Serial.begin(9600);
    Serial.println("Ingrese un numero romano en mayusculas:");
}

void loop() {
    if (Serial.available() > 0) {
        String romano = Serial.readStringUntil('\n');
        romano.trim();

        int total = 0;

        for (int i = 0; i < romano.length(); i++) {
            int valorActual = valorRomano(romano[i]);

            int valorSiguiente = 0;
            // Solo miramos al futuro si no estamos en la última letra
            if (i + 1 < romano.length()) {
                valorSiguiente = valorRomano(romano[i + 1]);
            }

            if (valorActual >= valorSiguiente) {
                total += valorActual;
            } else {
                total -= valorActual;
            }
        }

        Serial.print("El numero ingresado fue: ");
        Serial.println(romano);
        Serial.print("Que corresponde a: ");
        Serial.print(total);
        Serial.println(".\n");
    }
}*/




/*Problema 17

// Tu función intacta, con el 0 cambiado por 1
int sumaDivisor(int n){
    int suma = 0;

    // ¡Aquí está tu cambio clave!
    for(int i = 1; i <= n/2; i++){
        if(n % i == 0){
            suma = suma + i;
        }
    }

    return suma;
}

// Reemplaza la parte inicial de tu int main()
void setup() {
    // Encendemos la comunicación con el computador a 9600 baudios
    Serial.begin(9600);
    Serial.println("--- BUSCADOR DE NUMEROS AMIGABLES ---");
    Serial.println("Ingrese un numero:");
}

// Reemplaza tu do-while, ya que loop() se repite por naturaleza
void loop() {

    // Verificamos si el usuario escribió algo en el Monitor Serial
    if (Serial.available() > 0) {

        // Leemos el número entero (El equivalente a cin >> n)
        int n = Serial.parseInt();

        // Limpiamos la basura del 'Enter' (El equivalente a tu cin.ignore)
        while(Serial.available() > 0) {
            Serial.read();
        }

        // Tu validación de que sea mayor a 0
        if (n > 0) {
            int amigables = 0;

            // Tu ciclo for exactamente igual a como lo escribiste
            for(int i = 1; i < n; i++){
                int posibleAmigable = sumaDivisor(i);

                if(posibleAmigable != i && sumaDivisor(posibleAmigable) == i){
                    amigables = amigables + i;
                }
            }

            // Tus impresiones de resultado usando Serial
            Serial.print("El resultado de la suma es: ");
            Serial.println(amigables);
            Serial.println("\nIngrese otro numero:"); // Listo para volver a empezar

        } else {
            Serial.println("El numero debe ser mayor a 0. Intente de nuevo:");
        }
    }
}*/


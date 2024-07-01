int buzzer = 12; // El pin del buzzer activo

void setup() {
  pinMode(buzzer, OUTPUT); // Inicializar el pin del buzzer como salida
  Serial.begin(9600); // Inicializar la comunicación serial a 9600 baudios
}

void loop() {
  while (1) {
    // Generar un sonido  aleatorio
    int duration = random(20, 100); // Duración aleatoria entre 20 y 100 ms
    int pitch = random(100, 1000); // Frecuencia aleatoria entre 100 y 1000 Hz

    // Imprimir la frecuencia en la consola
    Serial.print("Frecuencia: ");
    Serial.print(pitch);
    Serial.print(" Hz, Duración: ");
    Serial.print(duration);
    Serial.println(" ms");

    // Reproducir el sonido de tambor
    tone(buzzer, pitch, duration);
    delay(duration + 50); // Agregar un pequeño tiempo de espera entre sonidos
  }
}


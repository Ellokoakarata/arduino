int buzzer = 12; // El pin del buzzer activo

// Definir las frecuencias de las notas musicales
int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  pinMode(buzzer, OUTPUT); // Inicializar el pin del buzzer como salida
  Serial.begin(9600); // Inicializar la comunicación serial a 9600 baudios
  randomSeed(analogRead(0)); // Inicializar la semilla para generar números aleatorios
}

void loop() {
  while (1) {
    // Generar una secuencia aleatoria de notas musicales
    for (int i = 0; i < 8; i++) {
      int noteIndex = random(0, 8); // Escoger una nota aleatoria del array de notas
      int duration = random(100, 500); // Duración aleatoria entre 100 y 500 ms

      // Imprimir la nota y la duración en la consola
      Serial.print("Nota: ");
      Serial.print(noteIndex);
      Serial.print(", Frecuencia: ");
      Serial.print(notes[noteIndex]);
      Serial.print(" Hz, Duración: ");
      Serial.print(duration);
      Serial.println(" ms");

      // Reproducir la nota en el buzzer
      tone(buzzer, notes[noteIndex], duration);
      delay(duration + 50); // Agregar un pequeño tiempo de espera entre notas
    }
  }
}



const int buzzerPin = 8;  // Pin donde está conectado el buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);
  randomSeed(analogRead(0));  // Inicializa el generador de números aleatorios
}

void playToneWithNoise(int frequency, int duration, int vibratoDepth, int vibratoSpeed, int noiseLevel) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    int currentFrequency = frequency + sin(2 * PI * (millis() - startTime) / vibratoSpeed) * vibratoDepth;
    currentFrequency += random(-noiseLevel, noiseLevel);  // Añadir ruido
    tone(buzzerPin, currentFrequency);
    delay(10);  // Pequeña pausa para permitir la modulación
  }
  noTone(buzzerPin);  // Apagar el tono al finalizar
}

void loop() {
  // Array base de frecuencias para tonos (notas musicales)
  int baseFrequencies[] = { 333, 666, 888, 333, 666, 698, 784 };  
  int duration = 200;  // Duración base de cada tono en milisegundos
  
  for (int i = 0; i < 7; i++) {
    // Generar frecuencia aleatoria basada en la frecuencia base
    int frequency = baseFrequencies[random(0, 7)] + random(-30, 30);  // Variación aleatoria alrededor de la frecuencia base
    // Ajustes aleatorios para vibratoDepth y vibratoSpeed
    int vibratoDepth = random(66, 88);
    int vibratoSpeed = random(88, 333);
    int noiseLevel = random(33, 66);  // Nivel de ruido aleatorio

    playToneWithNoise(frequency, duration, vibratoDepth, vibratoSpeed, noiseLevel);
    delay(duration * 1.8);  // Pequeña pausa entre tonos
  }

  delay(1000);  // Pausa de 1 segundo antes de repetir
}


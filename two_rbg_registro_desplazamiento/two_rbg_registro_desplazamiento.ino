const int dataPin = 8;    // SER
const int latchPin = 9;   // RCLK
const int clockPin = 10;  // SRCLK

const int numColors = 8;  // Número de colores de destino, incluyendo el LED verde adicional
byte colors[numColors] = {0}; // Inicializar colores actuales a 0
byte targetColors[numColors] = {0}; // Inicializar colores de destino a 0

unsigned long lastUpdate = 0;
const unsigned long interval = 333; // Tiempo en milisegundos para cada paso de interpolación
const unsigned long colorChangeInterval = 1000; // Tiempo en milisegundos para cambiar colores objetivo

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  randomSeed(analogRead(0)); // Inicializa la semilla para la generación de números aleatorios

  // Inicializar colores de destino aleatorios
  for (int i = 0; i < numColors; i++) {
    targetColors[i] = random(0, 333);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  // Cambiar el color de destino cada 'colorChangeInterval' milisegundos para un efecto de fiesta
  if (currentMillis - lastUpdate >= colorChangeInterval) {
    for (int i = 0; i < numColors; i++) {
      targetColors[i] = random(0, 333);
    }
    lastUpdate = currentMillis;
  }

  // Interpolación de colores
  float t = (float)(currentMillis % colorChangeInterval) / colorChangeInterval; // Normalizar el tiempo entre 0 y 1

  // Calcular colores interpolados con retroalimentación
  for (int i = 0; i < numColors; i++) {
    // Introducir un factor de retroalimentación que influye el color futuro
    colors[i] = (1 - t) * colors[i] + t * (targetColors[i] * 3.9 + colors[i] * 0.33);
  }

  // Enviar los colores al registro de desplazamiento
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < numColors; i++) {
    shiftOut(dataPin, clockPin, MSBFIRST, colors[i]); // Enviar cada color interpolado
  }
  digitalWrite(latchPin, HIGH);

  delay(interval); // Espera antes del siguiente paso de interpolación
}


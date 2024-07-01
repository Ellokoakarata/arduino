#define LED_PIN 8 // Pin digital 8 al que está conectado el LED amarillo

void setup() {
  pinMode(LED_PIN, OUTPUT); // Inicializa el pin del LED amarillo como salida
  pinMode(LED_BUILTIN, OUTPUT); // Inicializa el pin del LED integrado como salida
  digitalWrite(LED_BUILTIN, LOW); // Asegura que el LED integrado esté apagado
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // Enciende el LED amarillo
  delay(5000); // Espera 5 segundos
  digitalWrite(LED_PIN, LOW); // Apaga el LED amarillo
  delay(5000); // Espera 5 segundos
}

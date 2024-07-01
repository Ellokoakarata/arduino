void setup() {
  // Inicializa el pin LED_BUILTIN como salida
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  // Enciende el LED integrado
  digitalWrite(LED_BUILTIN, HIGH);
  // Espera 5 segundos
  delay(5000); // Cambiado de 1000 ms a 5000 ms (5 segundos)
  // Apaga el LED integrado
  digitalWrite(LED_BUILTIN, LOW);
  // Espera 3 segundos
  delay(3000); // Cambiado de 1000 ms a 3000 ms (3 segundos)
}
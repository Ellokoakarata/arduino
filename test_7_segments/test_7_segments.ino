int latch = 9;  // 74HC595 pin 9 STCP
int clock = 10; // 74HC595 pin 10 SHCP
int data = 8;   // 74HC595 pin 8 DS

// Tabla de segmentos para los dígitos 0-9
unsigned char table[] = 
{0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

int digitPins[] = {2, 3, 4, 5}; // Pines para los dígitos

void setup() {
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
  
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW); // Asegurarse de que todos los dígitos estén apagados inicialmente
  }
}

void displayDigit(int digit, unsigned char num) {
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, table[num]);
  digitalWrite(latch, HIGH);
  
  digitalWrite(digitPins[digit], HIGH); // Encender el dígito específico
  delay(2); // Pequeño retraso para la multiplexación
  digitalWrite(digitPins[digit], LOW); // Apagar el dígito
}

void displaySequence(unsigned char digits[], int displayTime) {
  unsigned long startTime = millis();
  while (millis() - startTime < displayTime) {
    for (int i = 0; i < 4; i++) {
      displayDigit(i, digits[i]);
    }
  }
}

void loop() {
  unsigned char firstSequence[] = {1, 1, 1, 1}; // "1111"
  unsigned char secondSequence[] = {9, 9, 9, 9}; // "9999"
  unsigned char thirdSequence[] = {6,6,6,6} ; 

  // Mostrar "1111" por 2 segundos
  displaySequence(firstSequence, 2000);

  // Mostrar "9999" por 2 segundos
  displaySequence(secondSequence, 2000);

  // Mostrar "6666" por 2 segundos
  displaySequence(thirdSequence, 2000);
}


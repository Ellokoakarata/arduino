int latchPin = 11; // Pin de latch (ST_CP)
int clockPin = 9;  // Pin de reloj (SH_CP)
int dataPin = 12;  // Pin de datos (DS)

byte leds = 0; // Estado de los LEDs
int tDelay = 100; // Tiempo de retardo en milisegundos

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  randomSeed(analogRead(0)); // Inicializa el generador de números aleatorios
}

void loop() 
{
  for (int i = 0; i < 8; i++)
  {
    leds = 0; // Apaga todos los LEDs
    int colorIndex = random(0, 4); // Selecciona un color aleatorio
    for (int j = 0; j < 8; j++)
    {
      switch (colorIndex)
      {
        case 0: // Rojo
          if (j % 2 == 0) bitSet(leds, j);
          break;
        case 1: // Verde
          if (j % 2 == 1) bitSet(leds, j);
          break;
        case 2: // Azul
          if (j < 4) bitSet(leds, j);
          break;
        case 3: // Amarillo
          if (j >= 4) bitSet(leds, j);
          break;
      }
    }
    updateShiftRegister();
    delay(tDelay);
  }
}

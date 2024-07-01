int latchPin = 11; // Pin de latch (ST_CP)
int clockPin = 9;  // Pin de reloj (SH_CP)
int dataPin = 12;  // Pin de datos (DS)

byte leds = 0; // Estado de los LEDs
int tDelay = 100; // Tiempo de retardo en milisegundos
bool randomMode = false; // Indica si el modo aleatorio está activo

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
  Serial.begin(9600); // Inicializa la comunicación serial
  randomSeed(analogRead(0)); // Inicializa el generador de números aleatorios
  leds = 0; // Apaga todos los LEDs al inicio
  updateShiftRegister();
  Serial.println("Ingrese '2' para encender LEDs de 2 en 2, '4' para encender LEDs de 4 en 4, 'r' para encender LEDs aleatoriamente en bucle:");
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    char input = Serial.read();
    if (input == '2') 
    {
      randomMode = false;
      encenderDeDosEnDos();
    } 
    else if (input == '4') 
    {
      randomMode = false;
      encenderDeCuatroEnCuatro();
    } 
    else if (input == 'r') 
    {
      randomMode = true;
    }
  }

  if (randomMode) 
  {
    encenderAleatorio();
  }
}

void encenderDeDosEnDos() 
{
  leds = 0;
  for (int i = 0; i < 8; i += 2) 
  {
    bitSet(leds, i);
  }
  updateShiftRegister();
  delay(tDelay);
}

void encenderDeCuatroEnCuatro() 
{
  leds = 0;
  for (int i = 0; i < 8; i += 4) 
  {
    bitSet(leds, i);
    if (i + 1 < 8) bitSet(leds, i + 1);
    if (i + 2 < 8) bitSet(leds, i + 2);
    if (i + 3 < 8) bitSet(leds, i + 3);
  }
  updateShiftRegister();
  delay(tDelay);
}

void encenderAleatorio() 
{
  leds = 0; // Apaga todos los LEDs
  for (int j = 0; j < 8; j++)
  {
    if (random(0, 2) == 1)
    {
      bitSet(leds, j);
    }
  }
  updateShiftRegister();
  delay(tDelay);
}

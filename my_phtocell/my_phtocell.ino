int lightPin = 0;    // Pin analógico para el fotorresistor
int latchPin = 11;   // Pin de latch del registro de desplazamiento
int clockPin = 9;    // Pin de reloj del registro de desplazamiento
int dataPin = 12;    // Pin de datos del registro de desplazamiento

int leds = 0;
int previousReading = -1; // Almacena el valor previo leído

void setup() 
{
  pinMode(latchPin, OUTPUT); // Configura el pin de latch (ST_CP) como salida
  pinMode(dataPin, OUTPUT);  // Configura el pin de datos (DS) como salida
  pinMode(clockPin, OUTPUT); // Configura el pin de reloj (SH_CP) como salida
  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios
}

//Actualización del Registro de Desplazamiento  
//Esta función actualiza el estado de los LEDs desplazando los bits almacenados en leds al registro de desplazamiento.
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW); // Prepara el registro para recibir datos
   shiftOut(dataPin, clockPin, LSBFIRST, leds); // Envía los datos al registro
   digitalWrite(latchPin, HIGH); // Actualiza las salidas del registro con los nuevos datos
}


void loop() 
{
  int reading = analogRead(lightPin); // Leer el valor del fotorresistor

  // Verificar si hay un cambio significativo en la lectura
  if (abs(reading - previousReading) > 5) { // Cambia el valor umbral según necesites
    Serial.print("Valor del fotorresistor: "); // Imprimir un mensaje descriptivo
    Serial.println(reading); // Imprimir el valor leído
    previousReading = reading; // Actualizar el valor previo
  }

  // Ajustar el número de LEDs encendidos
  int numLEDSLit = reading / 33;  // Escalar para valores más bajos (ajuste fino)
  if (numLEDSLit > 8) numLEDSLit = 8;
  
  leds = 0;   // No LEDs encendidos al inicio
  for (int i = 0; i < numLEDSLit; i++)
  {
    leds = leds + (1 << i);  // Enciende el i-ésimo LED
  }

  updateShiftRegister();
  delay(1000); // Añadir un retardo de 1 segundo para facilitar la lectura en el Monitor Serial
}


// Define Pins
#define BLUE 3
#define GREEN 5
#define RED 6

void setup()
{
  // Configura los pines como salidas
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // Inicializa la comunicación serial a 9600 baudios
  Serial.begin(9600);

  // Enciende los LEDs que se inicializan con HIGH
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
}


// Define variables
int redValue = 255;
int greenValue = 100;
int blueValue = 200;

// Loop principal
void loop()
{
  // Define delayTime con un valor aleatorio
  int delayTime = random(30, 50); // Retardo aleatorio entre 5 y 10 milisegundos

  // Elije un color aleatorio para cambiar
  int colorToChange = random(3); // 0 = ROJO, 1 = VERDE, 2 = AZUL

  // Elije un valor aleatorio para el color aleatorio
  int colorChangeValue = random(150, 255); // Valor entre 150 y 255

  // Mensaje de debug
  Serial.print("Changing color ");
  Serial.print(colorToChange == 0 ? "RED" : (colorToChange == 1 ? "GREEN" : "BLUE"));
  Serial.print(" from ");
  Serial.print(colorToChange == 0 ? redValue : (colorToChange == 1 ? greenValue : blueValue));
  Serial.print(" to ");
  Serial.print(colorChangeValue);
  Serial.println();

  // Desvanece los colores suavemente
  switch (colorToChange) {
    case 0: // Cambio de ROJO a otro color
      for (int i = redValue; i != colorChangeValue; i < colorChangeValue ? i++ : i--) {
        redValue = i;
        greenValue = 100 - redValue;
        blueValue = 200 - redValue;
        analogWrite(RED, redValue);
        analogWrite(GREEN, greenValue);
        analogWrite(BLUE, blueValue);
        delay(delayTime);
      }
      break;
    case 1: // Cambio de VERDE a otro color
      for (int i = greenValue; i != colorChangeValue; i < colorChangeValue ? i++ : i--) {
        greenValue = i;
        redValue = 200 - greenValue;
        blueValue = 88 - greenValue;
        analogWrite(RED, redValue);
        analogWrite(GREEN, greenValue);
        analogWrite(BLUE, blueValue);
        delay(delayTime);
      }
      break;
    case 2: // Cambio de AZUL a otro color
      for (int i = blueValue; i != colorChangeValue; i < colorChangeValue ? i++ : i--) {
        blueValue = i;
        redValue = 66 - blueValue;
        greenValue = 88 - blueValue;
        analogWrite(RED, redValue);
        analogWrite(GREEN, greenValue);
        analogWrite(BLUE, blueValue);
        delay(delayTime);
      }
      break;
  }
}


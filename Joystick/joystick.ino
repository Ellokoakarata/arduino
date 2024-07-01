const int joyXPin = A0; // Pin para el eje X del joystick
const int joyYPin = A1; // Pin para el eje Y del joystick
const int joyButtonPin = 2; // Pin para el botón del joystick
const int numReadings = 5; // Número de lecturas para promediar
const int threshold = 10; // Umbral de cambio para considerar que hay movimiento

int readingsX[numReadings]; // Arreglo para almacenar las lecturas del eje X
int readingsY[numReadings]; // Arreglo para almacenar las lecturas del eje Y
int index = 0; // Índice actual en los arreglos
int totalX = 0; // Suma total de las lecturas del eje X
int totalY = 0; // Suma total de las lecturas del eje Y

void setup() {
  Serial.begin(9600);
  pinMode(joyButtonPin, INPUT_PULLUP); // Configurar el botón como entrada con resistencia pull-up interna
}

void loop() {
  // Leer el valor del joystick
  int joyX = analogRead(joyXPin);
  int joyY = analogRead(joyYPin);
  int joyButtonState = digitalRead(joyButtonPin);

  // Restar la lectura más antigua y agregar la nueva lectura al total
  totalX = totalX - readingsX[index] + joyX;
  totalY = totalY - readingsY[index] + joyY;

  // Guardar la nueva lectura en el arreglo
  readingsX[index] = joyX;
  readingsY[index] = joyY;

  // Avanzar al siguiente índice circularmente
  index = (index + 1) % numReadings;

  // Calcular el promedio de las últimas lecturas
  int avgX = totalX / numReadings;
  int avgY = totalY / numReadings;

  // Verificar si el botón se presiona (valor 0) y enviar solo en ese caso
  if (joyButtonState == LOW) {
    Serial.print("X: ");
    Serial.print(avgX);
    Serial.print("\tY: ");
    Serial.print(avgY);
    Serial.print("\tButton: ");
    Serial.println(joyButtonState);
  }

  delay(100); // Retraso para evitar saturar el puerto serie
}


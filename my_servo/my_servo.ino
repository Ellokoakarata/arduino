#include <Servo.h>

Servo myservo;  // Crear objeto servo para controlar un servo

int pos = 0;    // Variable para almacenar la posición del servo
int delayTime = 10; // Tiempo de retraso entre cada movimiento
int stepSize = 2;   // Tamaño del paso en grados
bool isRunning = true; // Estado del servo (encendido o apagado)

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // Adjunta el servo al pin 9
  Serial.println("Ingrese '+' para aumentar los grados, '-' para disminuirlos.");
  Serial.println("Ingrese 't' seguido de un número para establecer un nuevo tiempo de retraso.");
  Serial.println("Ingrese 'o' para apagar el servo, 'p' para encenderlo.");
  Serial.println("Ingrese 'v' para aumentar la velocidad, 'w' para disminuirla.");
}

void loop() {
  // Leer entrada del usuario
  if (Serial.available()) {
    char command = Serial.read();
    if (command == '+') {
      stepSize = min(10, stepSize + 1); // Aumentar el tamaño del paso (grados)
      Serial.print("Tamaño del paso aumentado a ");
      Serial.print(stepSize);
      Serial.println(" grados.");
    } else if (command == '-') {
      stepSize = max(1, stepSize - 1); // Disminuir el tamaño del paso (grados)
      Serial.print("Tamaño del paso disminuido a ");
      Serial.print(stepSize);
      Serial.println(" grados.");
    } else if (command == 't') {
      int newDelayTime = Serial.parseInt();
      if (newDelayTime > 0) {
        delayTime = newDelayTime; // Establecer un nuevo tiempo de retraso
        Serial.print("Nuevo tiempo de retraso establecido a ");
        Serial.print(delayTime);
        Serial.println(" ms.");
      }
    } else if (command == 'o') {
      isRunning = false; // Apagar el servo
      Serial.println("Servo apagado.");
    } else if (command == 'p') {
      isRunning = true; // Encender el servo
      Serial.println("Servo encendido.");
    } else if (command == 'v') {
      delayTime = max(1, delayTime - 1); // Aumentar la velocidad
      Serial.print("Velocidad aumentada a ");
      Serial.print(delayTime);
      Serial.println(" ms.");
    } else if (command == 'w') {
      delayTime = min(1000, delayTime + 1); // Disminuir la velocidad
      Serial.print("Velocidad disminuida a ");
      Serial.print(delayTime);
      Serial.println(" ms.");
    }
  }

  // Mover el servo si está encendido
  if (isRunning) {
    pos += stepSize;
    if (pos > 180) {
      pos = 0; // Reiniciar la posición si supera los 180 grados
    }
    myservo.write(pos);
    delay(delayTime);
  }
}


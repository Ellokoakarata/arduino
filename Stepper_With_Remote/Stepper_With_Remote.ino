#include <Stepper.h>
#include <IRremote.h>

/*----- Variables, Pines -----*/
#define STEPS  32   // Número de pasos por revolución del eje interno
const int stepsPerRevolution = 2048;  // Cambia esto para ajustar el número de pasos por revolución
const int rolePerMinute = 15;         // Rango ajustable del motor 28BYJ-48 es de 0~17 rpm
int direction = 1;                    // 1 para adelante, -1 para atrás
int receiverPin = 12; // Pin de señal del receptor IR al pin digital 12 del Arduino
bool motorOn = false; // Estado del motor, comienza apagado

// Define los códigos IR para diferentes botones
#define CODE_ON 0xBA45FF00
#define CODE_DIR1 0xF30CFF00
#define CODE_DIR2 0xE718FF00

/*-----( Declarar objetos )-----*/
// Inicializa la biblioteca stepper en los pines 8 a 11
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); 

void setup() {
  myStepper.setSpeed(rolePerMinute);
  Serial.begin(9600);  // Inicializa la comunicación serial
  IrReceiver.begin(receiverPin, ENABLE_LED_FEEDBACK); // Iniciar el receptor IR
  Serial.println("Receptor IR iniciado");
}

void loop() {
  if (IrReceiver.decode()) { // ¿Hemos recibido una señal IR?
    unsigned long receivedCode = IrReceiver.decodedIRData.decodedRawData;
    if (receivedCode != 0xFFFFFFFF) { // Ignorar códigos repetidos
      Serial.print("Código IR: 0x");
      Serial.println(receivedCode, HEX);

      switch(receivedCode) {
        case CODE_ON: // Botón para encender o apagar el motor
                      motorOn = !motorOn; // Alterna el estado del motor
                      if (motorOn) {
                        direction = 1; // Comienza en sentido horario
                        Serial.println("Motor encendido en sentido horario");
                      } else {
                        Serial.println("Motor apagado");
                      }
                      break;

        case CODE_DIR1: // Botón para cambiar a dirección 1 (sentido horario)
                        if (motorOn && direction != 1) {
                          direction = 1;
                          Serial.println("Dirección cambiada a sentido horario (clockwise)");
                        }
                        break;

        case CODE_DIR2: // Botón para cambiar a dirección 2 (sentido antihorario)
                        if (motorOn && direction != -1) {
                          direction = -1;
                          Serial.println("Dirección cambiada a sentido antihorario (counterclockwise)");
                        }
                        break;

        default:
                        Serial.println("Código no reconocido");
                        break;
      }
    } else {
      Serial.println("Código repetido, ignorado");
    }
    
    IrReceiver.resume(); // Recibir el siguiente valor
  }

  if (motorOn) {
    // Gira el motor continuamente en la dirección seleccionada
    myStepper.step(direction); // Paso a paso continuo
  }
}



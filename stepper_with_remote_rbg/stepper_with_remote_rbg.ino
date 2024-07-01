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
#define CODE_COLOR_CHANGE 0xA15EFF00

// Define Pins para LED RGB
#define BLUE 3
#define GREEN 5
#define RED 6

// Define variables para el color
int currentColor = 0; // 0 = Rojo, 1 = Verde, 2 = Azul

unsigned long lastStepTime = 0; // Para el control no bloqueante del motor
int stepInterval = 5; // Intervalo entre pasos del motor (ajusta según sea necesario)

/*-----( Declarar objetos )-----*/
// Inicializa la biblioteca stepper en los pines 8 a 11
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(rolePerMinute);
  Serial.begin(9600);  // Inicializa la comunicación serial
  IrReceiver.begin(receiverPin, ENABLE_LED_FEEDBACK); // Iniciar el receptor IR
  Serial.println("Receptor IR iniciado");

  // Configura los pines como salidas
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // Inicializa los LEDs apagados
  setColor(0, 0, 0);
}

void loop() {
  handleIRInput();
  handleMotor();
}

void handleIRInput() {
  if (IrReceiver.decode()) {
    unsigned long receivedCode = IrReceiver.decodedIRData.decodedRawData;
    if (receivedCode != 0xFFFFFFFF) { // Ignorar códigos repetidos
      Serial.print("Código IR: 0x");
      Serial.println(receivedCode, HEX);

      switch(receivedCode) {
        case CODE_ON:
          toggleMotor();
          break;
        case CODE_DIR1:
          changeDirection(1);
          break;
        case CODE_DIR2:
          changeDirection(-1);
          break;
        case CODE_COLOR_CHANGE:
          changeColor();
          break;
        default:
          Serial.println("Código no reconocido");
          break;
      }
    }
    IrReceiver.resume(); // Recibir el siguiente valor
  }
}

void toggleMotor() {
  motorOn = !motorOn;
  if (motorOn) {
    direction = 1;
    Serial.println("Motor encendido en sentido horario");
    setColorByIndex(currentColor);
  } else {
    Serial.println("Motor apagado");
    setColor(0, 0, 0); // Apaga el LED RGB
  }
}

void changeDirection(int newDirection) {
  if (motorOn && direction != newDirection) {
    direction = newDirection;
    Serial.println(direction == 1 ? "Dirección cambiada a sentido horario" : "Dirección cambiada a sentido antihorario");
  }
}

void changeColor() {
  if (motorOn) {
    currentColor = (currentColor + 1) % 7; 
    setColorByIndex(currentColor);
    Serial.print("Color cambiado ");
    
  }
}

void handleMotor() {
  if (motorOn) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastStepTime >= stepInterval) {
      lastStepTime = currentMillis;
      myStepper.step(direction);
    }
  }
}

void setColorByIndex(int colorIndex) {
  switch (colorIndex) {
    case 0: setColor(255, 0, 0); break;    // Rojo
    case 1: setColor(0, 255, 0); break;    // Verde
    case 2: setColor(0, 0, 255); break;    // Azul
    case 3: setColor(255, 255, 0); break;  // Amarillo
    case 4: setColor(255, 0, 255); break;  // Magenta
    case 5: setColor(0, 255, 255); break;  // Cian
    case 6: setColor(255, 128, 0); break;  // Naranja
    case 7: setColor(128, 0, 128); break;  // Púrpura
    default: setColor(0, 0, 0); break;     // Apagado si el índice está fuera de rango
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);
}
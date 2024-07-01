#include <IRremote.h>

// Pin donde está conectado el receptor IR
const int RECV_PIN = 11;

// Define los códigos IR para diferentes botones
#define CODE_1 0xE916FF00
#define CODE_2 0xF30CFF00
#define CODE_3 0xE718FF00
#define CODE_4 0xA15EFF00
#define CODE_5 0xF708FF00
#define CODE_6 0xE31CFF00
#define CODE_7 0xA55AFF00
#define CODE_8 0xBD42FF00
#define CODE_9 0xAD52FF00

void setup() {
  Serial.begin(9600);
  // Inicializa el receptor IR
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Receptor IR listo");
}

void loop() {
  // Verifica si hay datos disponibles
  if (IrReceiver.decode()) {
    // Lee el código IR recibido
    unsigned long receivedCode = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("Código IR: 0x");
    Serial.println(receivedCode, HEX);

    // Reinicia el receptor para recibir la próxima señal
    IrReceiver.resume();
  }
}



#include <IRremote.h>

// Pin donde está conectado el receptor IR
const int RECV_PIN = 12;

void setup() {
  Serial.begin(9600);
  // Inicializa el receptor IR
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Receptor IR listo");
}

void loop() {
  // Verifica si hay datos disponibles
  if (IrReceiver.decode()) {
    // Imprime los datos recibidos en el Monitor Serial
    Serial.print("Código IR: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    
    // Reinicia el receptor para recibir la próxima señal
    IrReceiver.resume();
  }
}

#include <LiquidCrystal.h>

// Inicializa la biblioteca de LCD con los números de los pines de interfaz
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int screenWidth = 16;
const String message = "RD Works - never stops ";

void setup() {
  // Configura el número de columnas y filas del LCD:
  lcd.begin(screenWidth, 2);
}

void loop() {
  String displayMessage = message + message.substring(0, screenWidth); // Asegura una transición suave
  for (int i = 0; i < displayMessage.length() - screenWidth + 1; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(displayMessage.substring(i, i + screenWidth));
    delay(300);
  }
}


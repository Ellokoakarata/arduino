#include <LiquidCrystal.h>
#include <math.h>

int tempPin = A0; // Pin analógico donde está conectado el termistor
//                RS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int position = 0; // Posición del mensaje "RD informa"
int direction = 1; // Dirección del movimiento (1 = derecha, -1 = izquierda)

void setup() {
  lcd.begin(16, 2); // Inicializa la pantalla LCD con 16 columnas y 2 filas
}

void loop() {
  int tempReading = analogRead(tempPin); // Lee el valor analógico del termistor

  // Convertimos la lectura del termistor a resistencia
  double resistance = (1024.0 / tempReading - 1) * 10000; // Suponiendo un R0 de 10k ohms
  
  // Usamos la ecuación de Steinhart-Hart para calcular la temperatura en Kelvin
  double tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * log(resistance) * log(resistance))) * log(resistance));
  
  // Convertimos de Kelvin a Celsius
  float tempC = tempK - 273.15;
  
  // Mostrar la temperatura ajustada en la LCD en Celsius
  lcd.setCursor(0, 0);
  lcd.print("Temp C: ");
  lcd.print(tempC);

  // Limpiamos la segunda línea
  lcd.setCursor(0, 1);
  lcd.print("                "); // 16 espacios para limpiar la línea

  // Mueve el mensaje "RD informa" de un lado a otro
  lcd.setCursor(position, 1);
  lcd.print("RD informa");

  // Actualiza la posición del mensaje
  position += direction;
  if (position == 0 || position == 16 - strlen("RD informa")) {
    direction = -direction; // Cambia de dirección al llegar a los extremos
  }

  delay(1000); // Espera un corto tiempo antes de la siguiente lectura
}


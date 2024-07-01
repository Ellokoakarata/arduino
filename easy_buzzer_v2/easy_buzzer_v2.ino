#include <EasyBuzzer.h>

void setup() {
  // Setear pin
  EasyBuzzer.setPin(8);

  // Generar sonidos
  EasyBuzzer.beep(
  222, //Frecuencia Hz
  100, //Duración
  700, // Silencio
  5,   // Número de pitidos
  2000, // Pausa
  3,// Ciclos 
  sonidorandom // llamada a función que está abajo
 );
}

void sonidorandom() {
  EasyBuzzer.singleBeep(88,66,setup);  // Segundo tono al finalizar los ciclos de los primeros tonos
}

void loop() {
   EasyBuzzer.update();  // Actualizar el buzzer
}

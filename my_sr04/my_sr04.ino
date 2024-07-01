#include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define NUM_READINGS 1 // Número de lecturas para promediar

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long previousDistance = -1; // Almacena la distancia anterior
long totalDistance = 0; // Suma total de las distancias
int numReadings = 0; // Número actual de lecturas

void setup() {
   Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios
   delay(1000); // Espera un segundo antes de comenzar
}

void loop() {
   long currentDistance = sr04.Distance(); // Obtiene la distancic:\Users\Ricardo Ruiz\Desktop\arduino\Espanol\código\Lesson 11 DHT11 Temperature and Humidity Sensor\DHT11_Example\DHT11_Example.inoa actual
   totalDistance += currentDistance; // Suma la distancia actual al total
   numReadings++; // Incrementa el número de lecturas

   if (numReadings >= NUM_READINGS) { // Si se han realizado suficientes lecturas
      long averageDistance = totalDistance / NUM_READINGS; // Calcula el promedio
      if (averageDistance != previousDistance) { // Comprueba si la distancia ha cambiado
         Serial.print(averageDistance); // Imprime la distancia promedio en el Monitor Serial
         Serial.println(" cm"); // Añade " cm" al final de la distancia
         previousDistance = averageDistance; // Actualiza la distancia anterior
      }
      totalDistance = 0; // Reinicia la suma total
      numReadings = 0; // Reinicia el número de lecturas
   }

   delay(100); // Espera un breve periodo antes de la siguiente lectura
}


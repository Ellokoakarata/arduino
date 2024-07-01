//www.elegoo.com
//2018.10.25

#include "dht_nonblocking.h"
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

// Variables para almacenar la última temperatura y humedad medidas
float last_temperature = 0.0;
float last_humidity = 0.0;

/*
 * Inicializar el puerto serie.
 */
void setup( )
{
  Serial.begin( 9600);
}

/*
 * Realizar una medición, manteniendo viva la máquina de estados. Devuelve
 * true si hay una medición disponible.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Medir una vez cada cuatro segundos. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

/*
 * Bucle principal del programa.
 */
void loop( )
{
  float temperature;
  float humidity;

  /* Medir temperatura y humedad. Si la función devuelve
     true, entonces hay una medición disponible. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    // Verificar si la temperatura o la humedad han cambiado
    if( temperature != last_temperature || humidity != last_humidity )
    {
      // Imprimir los nuevos valores de temperatura y humedad
      Serial.print( "T = " );
      Serial.print( temperature, 1 );
      Serial.print( " deg. C, H = " );
      Serial.print( humidity, 1 );
      Serial.println( "%" );

      // Actualizar los valores de última temperatura y humedad
      last_temperature = temperature;
      last_humidity = humidity;
    }
  }
}
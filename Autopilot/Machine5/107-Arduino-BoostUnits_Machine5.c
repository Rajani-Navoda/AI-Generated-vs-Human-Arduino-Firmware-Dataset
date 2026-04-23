#include <Arduino.h>
#include <107-Arduino-BoostUnits.h>  // Include the BoostUnits library

using namespace ::arduino::units;  // Bring the units into scope

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Length example: Define length in meters and convert to kilometers
  meter_t distance = 5000.0_m;  // 5000 meters
  kilometer_t distanceInKm = distance;  // Convert to kilometers
  Serial.print("Distance: ");
  Serial.print(distanceInKm.value());
  Serial.println(" km");

  // Temperature example: Convert Celsius to Fahrenheit
  celsius_t tempC = 25.0_degC;  // 25°C
  fahrenheit_t tempF = unit_cast<fahrenheit_t>(tempC);  // Convert to Fahrenheit
  Serial.print("Temperature: ");
  Serial.print(tempF.value());
  Serial.println(" °F");

  // Pressure example: Define pressure in Pascals and convert to hPa
  pascal_t pressure = 101325.0_Pa;  // Standard atmospheric pressure (in Pa)
  hectopascal_t pressureInHpa = pressure;  // Convert to hPa
  Serial.print("Pressure: ");
  Serial.print(pressureInHpa.value());
  Serial.println(" hPa");
}

void loop() {
  // Nothing to do in the loop for this example
}

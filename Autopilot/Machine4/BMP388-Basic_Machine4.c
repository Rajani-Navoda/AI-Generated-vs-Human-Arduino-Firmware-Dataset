#include <Wire.h>
#include <Arduino_BMP388.h>  // Include the BMP388 library

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the BMP388 sensor
  if (!BMP388.begin()) {
    Serial.println("Error: BMP388 not detected!");
    while (1);
  }

  // Notify that the sensor was initialized
  Serial.println("BMP388 sensor initialized!");
}

void loop() {
  // Variables to store temperature and pressure
  float temperature;
  float pressure;

  // Read temperature and pressure
  if (BMP388.readTemperature(temperature) && BMP388.readPressure(pressure)) {
    // Print temperature and pressure to the Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" hPa");
  } else {
    Serial.println("Failed to read from BMP388 sensor");
  }

  // Wait 500 milliseconds before the next reading
  delay(500);
}

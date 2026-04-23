#include <Wire.h>
#include <Arduino_BMP388.h>  // Include the BMP388 library

// Create a BMP388 sensor object
ArduinoBMP388 bmp388;

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the BMP388 sensor
  if (!bmp388.begin()) {
    Serial.println("Error: BMP388 sensor not detected!");
    while (1);  // Halt the program if initialization fails
  }

  // Notify that the BMP388 sensor has been initialized
  Serial.println("BMP388 sensor initialized successfully!");
}

void loop() {
  // Variables to store sensor readings
  float temperature;
  float pressure;

  // Read the temperature and pressure from the BMP388 sensor
  if (bmp388.readTemperature(temperature) && bmp388.readPressure(pressure)) {
    // Print the temperature in Celsius
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Print the pressure in hPa (hectopascals)
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" hPa");
  } else {
    // Handle the case where the sensor reading fails
    Serial.println("Failed to read from BMP388 sensor");
  }

  // Delay for a short period before the next reading
  delay(1000);  // 1 second delay
}

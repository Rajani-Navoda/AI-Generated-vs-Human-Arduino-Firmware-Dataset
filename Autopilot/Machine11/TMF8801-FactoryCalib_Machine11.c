#include <Wire.h>                   // Required for I2C communication
#include <Arduino_TMF8801.h>         // Include the TMF8801 library

TMF8801 sensor;                      // Create a sensor object

void setup() {
  Serial.begin(9600);                // Initialize serial communication for debugging
  while (!Serial);                   // Wait for the serial connection to open

  // Initialize the sensor
  if (!sensor.begin()) {
    Serial.println("Failed to initialize TMF8801 sensor!");
    while (1);                       // Halt execution if sensor initialization fails
  }
  Serial.println("TMF8801 sensor initialized successfully.");

  // Perform factory calibration
  if (sensor.performFactoryCalibration()) {
    Serial.println("Factory calibration successful.");
  } else {
    Serial.println("Factory calibration failed.");
  }
}

void loop() {
  // No need to loop for calibration, halt execution
  while (1);
}

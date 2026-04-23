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
}

void loop() {
  // Get the distance reading from the sensor
  int distance = sensor.getDistance();

  // Check if the reading is valid
  if (distance != -1) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" mm");
  } else {
    Serial.println("Failed to read distance.");
  }

  delay(500);                        // Delay for half a second before the next reading
}

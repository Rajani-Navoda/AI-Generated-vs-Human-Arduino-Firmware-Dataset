#include <Wire.h>
#include <Arduino_AS504x.h>  // Include the AS504x library

// Global variable for the AS504x sensor object
AS504x sensor;

// Global variable to store the sensor angle
uint16_t sensorAngle = 0;

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the AS504x sensor
  if (!sensor.begin()) {
    Serial.println("Error: AS504x sensor not detected!");
    while (1);  // Halt the program if initialization fails
  }

  // Notify that the sensor has been initialized
  Serial.println("AS504x sensor initialized!");
}

void loop() {
  // Update the global sensor angle variable
  sensorAngle = sensor.readAngle();

  // Print the sensor angle to the Serial Monitor
  Serial.print("Angle: ");
  Serial.println(sensorAngle);

  // Wait for 500 milliseconds before the next reading
  delay(500);
}

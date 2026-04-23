/*
  Air Quality Sensor Example
  This sketch reads values from an air quality sensor and displays the results on the Serial Monitor.

  Written by [Your Name] under a GPL license.
*/

// Pin configuration
const int analogPin = A0; // Analog pin connected to the air quality sensor

void setup() {
  // Initialize the Serial communication
  Serial.begin(9600);
  Serial.println("Air Quality Sensor Example");
}

void loop() {
  // Read the sensor value
  int sensorValue = analogRead(analogPin);
  
  // Print the sensor value to the Serial Monitor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  // Add a delay for readability
  delay(1000);
}

#include <Wire.h>                   // Required for I2C communication
#include <Arduino_TMF8801.h>         // Include the TMF8801 library

TMF8801 sensor;                      // Create a sensor object
const int interruptPin = 2;          // GPIO pin connected to TMF8801 interrupt pin

volatile bool newMeasurement = false; // Flag to indicate a new measurement is available

// ISR to handle the interrupt from the TMF8801 sensor
void IRAM_ATTR handleInterrupt() {
  newMeasurement = true;            // Set the flag when an interrupt is triggered
}

void setup() {
  Serial.begin(9600);                // Initialize serial communication
  while (!Serial);

  // Initialize the TMF8801 sensor
  if (!sensor.begin()) {
    Serial.println("Failed to initialize TMF8801 sensor!");
    while (1);                       // Halt execution if sensor initialization fails
  }
  Serial.println("TMF8801 sensor initialized successfully.");

  // Configure the interrupt pin (pull-up resistor recommended)
  pinMode(interruptPin, INPUT_PULLUP);
  
  // Attach interrupt to the pin (trigger on FALLING edge)
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

  // Optionally, configure the sensor for interrupt-driven measurement
  // (Check the sensor's datasheet and library documentation for more settings)
  sensor.enableInterrupt();
}

void loop() {
  // Check if a new measurement is available
  if (newMeasurement) {
    newMeasurement = false;          // Reset the flag

    // Read the distance from the sensor
    int distance = sensor.getDistance();
    
    // Check if the reading is valid
    if (distance != -1) {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" mm");
    } else {
      Serial.println("Failed to read distance.");
    }
  }
}

#include <Arduino.h>

// Class definition for a dummy PressureSensor
class PressureSensor {
public:
    // Constructor
    PressureSensor() {}

    // Initialize the sensor (if needed)
    void begin() {
        // Initialization code can be placed here
        Serial.println("Pressure sensor initialized.");
    }

    // Simulate reading pressure values
    float readPressure() {
        return random(950, 1050) / 10.0; // Simulate pressure between 95.0 to 105.0 kPa
    }
};

// Create an instance of the PressureSensor class
PressureSensor pressureSensor;

// Setup function to initialize the sensor and serial communication
void setup() {
    Serial.begin(9600);       // Initialize serial communication at 9600 baud rate
    pressureSensor.begin();    // Initialize the dummy pressure sensor
}

// Loop function to read and print pressure data
void loop() {
    float pressure = pressureSensor.readPressure(); // Simulate reading pressure
    Serial.print("Pressure: ");
    Serial.println(pressure);   // Print the simulated pressure value
    delay(1000);                // Wait for a second before the next reading
}

#include <Wire.h>
#include <axp20x.h>

// Create an instance of the AXP20X class
AXP20X axp;

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("AXP202 Temperature Example");

    // Initialize I2C communication
    Wire.begin();

    // Initialize the AXP202X power management IC
    if (!axp.begin(Wire)) {
        Serial.println("AXP202 not found!");
        while (1); // Stop the program if AXP202 not found
    }
}

void loop() {
    // Read the temperature in Celsius
    float temperature = axp.getTemperature();

    // Print the temperature to the Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Wait for a second before the next reading
    delay(1000);
}

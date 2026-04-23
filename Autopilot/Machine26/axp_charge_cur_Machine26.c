#include <Wire.h>
#include <axp20x.h>

// Create an instance of the AXP20X class
AXP20X axp;

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("AXP202 Charge Current Example");

    // Initialize I2C communication
    Wire.begin();

    // Initialize the AXP202X power management IC
    if (!axp.begin(Wire)) {
        Serial.println("AXP202 not found!");
        while (1); // Stop the program if AXP202 not found
    }
}

void loop() {
    // Read the charging current in mA
    int chargeCurrent = axp.readChargeCurrent();

    // Print the charging current to the Serial Monitor
    Serial.print("Charging Current: ");
    Serial.print(chargeCurrent);
    Serial.println(" mA");

    // Wait for a second before the next reading
    delay(1000);
}

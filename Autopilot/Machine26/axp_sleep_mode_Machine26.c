#include <Wire.h>
#include <axp20x.h>

// Create an instance of the AXP20X class
AXP20X axp;

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("AXP202 Sleep Mode Example");

    // Initialize I2C communication
    Wire.begin();

    // Initialize the AXP202X power management IC
    if (!axp.begin(Wire)) {
        Serial.println("AXP202 not found!");
        while (1); // Stop the program if AXP202 not found
    }

    // Configure the power settings if needed
    axp.setPowerOutPut(AXP202_LDO2, AXP202_ON);  // Turn on LDO2
}

void loop() {
    // Enter sleep mode
    Serial.println("Entering sleep mode...");
    axp.enterSleep();

    // Wait for a few seconds to simulate sleep
    delay(5000);

    // Wake up from sleep mode
    Serial.println("Waking up from sleep mode...");
    axp.wakeUp();

    // Wait for a moment to stabilize
    delay(2000);

    // Print the current status
    float vbus = axp.getVBus();
    Serial.print("VBUS Voltage: ");
    Serial.print(vbus);
    Serial.println(" V");

    // Wait before the next iteration
    delay(10000); // Delay to observe the wake-up and sleep cycle
}

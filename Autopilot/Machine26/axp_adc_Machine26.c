#include <Wire.h>
#include <axp20x.h>

// Create an instance of the AXP20X class
AXP20X axp;

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("AXP202 ADC Example");

    // Initialize I2C communication
    Wire.begin();

    // Initialize the AXP202X power management IC
    if (!axp.begin(Wire)) {
        Serial.println("AXP202 not found!");
        while (1); // Stop the program if AXP202 not found
    }
}

void loop() {
    // Read the ADC value from the specified channel
    // For example, using ADC channel 0
    int adcValue = axp.readADC(AXP202_VBUS); // Change AXP202_VBUS to desired ADC channel

    // Print the ADC value to the Serial Monitor
    Serial.print("ADC Value: ");
    Serial.println(adcValue);

    // Print the corresponding voltage
    float voltage = adcValue * (1.1 / 1023.0); // Assuming a reference voltage of 1.1V
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");

    // Wait for a second before the next reading
    delay(1000);
}

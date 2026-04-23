#include <Wire.h>
#include <axp20x.h>

// Create an instance of the AXP20X class
AXP20X axp;

// Define the GPIO pin number you want to use (e.g., GPIO 2)
const int gpioPin = 2;

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("AXP202 GPIO Input Example");

    // Initialize I2C communication
    Wire.begin();

    // Initialize the AXP202X power management IC
    if (!axp.begin(Wire)) {
        Serial.println("AXP202 not found!");
        while (1); // Stop the program if AXP202 not found
    }

    // Set the GPIO pin as input
    axp.setGPIO(gpioPin, AXP202_GPIO_INPUT);
}

void loop() {
    // Read the state of the GPIO pin
    int gpioState = axp.digitalRead(gpioPin);

    // Print the GPIO state to the Serial Monitor
    if (gpioState == HIGH) {
        Serial.println("GPIO Pin HIGH");
    } else {
        Serial.println("GPIO Pin LOW");
    }

    // Add a delay for readability
    delay(500); // Adjust delay as needed
}

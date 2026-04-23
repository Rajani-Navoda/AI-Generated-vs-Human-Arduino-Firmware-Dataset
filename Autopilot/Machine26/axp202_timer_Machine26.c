#include <Wire.h>
#include <axp20x.h>

// Create an instance of the AXP20X class
AXP20X axp;

// Define the GPIO pin number you want to use (e.g., GPIO 2)
const int gpioPin = 2;

// Timer variables
unsigned long previousMillis = 0;  // Store the last time GPIO was updated
const long interval = 1000;         // Interval at which to toggle GPIO (milliseconds)

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    Serial.println("AXP202 Timer Example");

    // Initialize I2C communication
    Wire.begin();

    // Initialize the AXP202X power management IC
    if (!axp.begin(Wire)) {
        Serial.println("AXP202 not found!");
        while (1); // Stop the program if AXP202 not found
    }

    // Set the GPIO pin as output
    axp.setGPIO(gpioPin, AXP202_GPIO_OUTPUT);
}

void loop() {
    // Get the current time
    unsigned long currentMillis = millis();

    // Check if it's time to toggle the GPIO pin
    if (currentMillis - previousMillis >= interval) {
        // Save the last time the GPIO was updated
        previousMillis = currentMillis;

        // Read the current state of the GPIO pin
        int gpioState = axp.digitalRead(gpioPin);

        // Toggle the GPIO state
        if (gpioState == HIGH) {
            axp.digitalWrite(gpioPin, LOW);
            Serial.println("GPIO Pin LOW");
        } else {
            axp.digitalWrite(gpioPin, HIGH);
            Serial.println("GPIO Pin HIGH");
        }
    }
}

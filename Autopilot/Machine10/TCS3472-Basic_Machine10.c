#include <Wire.h>
#include <107-Arduino-TCS3472.h>

// Create an instance of the TCS3472 color sensor
TCS3472 tcs;

void setup() {
    Serial.begin(9600); // Start serial communication
    Wire.begin();       // Start I2C communication

    // Initialize the color sensor
    if (tcs.begin()) {
        Serial.println("TCS3472 sensor initialized.");
    } else {
        Serial.println("Failed to initialize TCS3472 sensor.");
        while (1); // Stop execution if sensor initialization fails
    }
}

void loop() {
    // Variables to hold the RGB values
    uint16_t r, g, b, c;

    // Read the color values from the sensor
    tcs.getRawData(&r, &g, &b, &c);

    // Print the RGB values to the Serial Monitor
    Serial.print("R: "); Serial.print(r);
    Serial.print(" G: "); Serial.print(g);
    Serial.print(" B: "); Serial.print(b);
    Serial.print(" C: "); Serial.println(c);

    delay(1000); // Wait for 1 second before the next reading
}

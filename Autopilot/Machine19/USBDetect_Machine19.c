#include <AStar32U4.h>

// Create instances for LCD
AStar32U4LCD lcd;

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    
    // Initialize LCD
    lcd.begin();
    lcd.clear();
    lcd.print("USB Status:");
    delay(1000); // Allow time to see the initial message

    // Initialize user LEDs
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // Check for USB power
    bool usbPowerPresent = (USB.isPowered());
    bool usbConfigured = (USB.isConfigured());
    bool usbConnected = (Serial.available() > 0);

    // Update LEDs based on USB status
    if (usbPowerPresent) {
        digitalWrite(LED_BUILTIN, HIGH); // Turn on LED to indicate USB power
    } else {
        digitalWrite(LED_BUILTIN, LOW); // Turn off LED if no USB power
    }

    // Display status on LCD
    lcd.clear();
    lcd.print("USB Power: ");
    lcd.print(usbPowerPresent ? "ON" : "OFF");
    lcd.setCursor(0, 1); // Move cursor to second line
    lcd.print("Configured: ");
    lcd.print(usbConfigured ? "YES" : "NO");
    lcd.setCursor(0, 2); // Move cursor to third line
    lcd.print("Connected: ");
    lcd.print(usbConnected ? "YES" : "NO");

    delay(500); // Update every 500 ms
}

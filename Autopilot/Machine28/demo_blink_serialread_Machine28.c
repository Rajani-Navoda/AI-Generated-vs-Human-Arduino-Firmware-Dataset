#include <tx_api.h>

// Define constants for the LED and thread
const int ledPin = 13;  // Pin for the LED
const uint32_t threadPriority = 1; // Thread priority
const uint32_t threadStackSize = 1024; // Stack size for the thread

// Thread Control Block
TX_THREAD blinkThread;

// Thread function prototype
void BlinkThreadEntry(ULONG thread_input);

// Setup function
void setup() {
    // Initialize the serial communication
    Serial.begin(115200);

    // Initialize the LED pin
    pinMode(ledPin, OUTPUT);
    
    // Create the Blink thread
    tx_thread_create(&blinkThread, "Blink Thread", BlinkThreadEntry, 0, // thread entry function
                     NULL, threadStackSize, threadPriority, threadPriority, // stack size and priorities
                     TX_AUTO_START); // auto start the thread
}

// Loop function
void loop() {
    // Read serial data if available
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n'); // Read until newline
        Serial.print("Received: ");
        Serial.println(input);
    }

    // Add a small delay to avoid overwhelming the serial output
    delay(100);
}

// Blink thread entry function
void BlinkThreadEntry(ULONG thread_input) {
    while (true) {
        digitalWrite(ledPin, HIGH); // Turn on the LED
        delay(500); // Wait for 500 milliseconds
        digitalWrite(ledPin, LOW); // Turn off the LED
        delay(500); // Wait for 500 milliseconds
    }
}

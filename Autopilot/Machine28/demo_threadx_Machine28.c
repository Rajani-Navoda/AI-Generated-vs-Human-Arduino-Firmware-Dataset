#include <tx_api.h>

// Define constants for the LED and thread
const int ledPin = 13;  // Pin for the LED
const uint32_t threadPriorityBlink = 1; // Priority for the Blink thread
const uint32_t threadPriorityRead = 2;  // Priority for the Read thread
const uint32_t threadStackSize = 1024;  // Stack size for the threads

// Thread Control Blocks
TX_THREAD blinkThread;
TX_THREAD readThread;

// Function prototypes
void BlinkThreadEntry(ULONG thread_input);
void ReadThreadEntry(ULONG thread_input);

void setup() {
    // Initialize the LED pin
    pinMode(ledPin, OUTPUT);

    // Create Blink thread
    tx_thread_create(&blinkThread, "Blink Thread", BlinkThreadEntry, 0, // Thread entry function
                     NULL, threadStackSize, threadPriorityBlink, threadPriorityBlink, // Stack size and priorities
                     TX_AUTO_START); // Auto start the thread

    // Create Read thread
    tx_thread_create(&readThread, "Read Thread", ReadThreadEntry, 0, // Thread entry function
                     NULL, threadStackSize, threadPriorityRead, threadPriorityRead, // Stack size and priorities
                     TX_AUTO_START); // Auto start the thread
}

void loop() {
    // Empty loop since all tasks are handled in threads
}

// Blink thread entry function
void BlinkThreadEntry(ULONG thread_input) {
    while (true) {
        digitalWrite(ledPin, HIGH); // Turn on the LED
        tx_thread_sleep(500);       // Sleep for 500 milliseconds
        digitalWrite(ledPin, LOW);  // Turn off the LED
        tx_thread_sleep(500);       // Sleep for 500 milliseconds
    }
}

// Read thread entry function
void ReadThreadEntry(ULONG thread_input) {
    while (true) {
        if (Serial.available() > 0) {
            String input = Serial.readStringUntil('\n'); // Read until newline
            Serial.print("Received: ");
            Serial.println(input);
        }
        tx_thread_sleep(100); // Sleep for 100 milliseconds to avoid overwhelming the serial
    }
}

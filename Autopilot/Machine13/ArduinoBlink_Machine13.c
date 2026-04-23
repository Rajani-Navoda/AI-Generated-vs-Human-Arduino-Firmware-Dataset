#include <Arduino.h>              // Standard Arduino library
#include <3bc_lang.h>             // Include the 3bc-lang library

// Define the pin for the LED (usually pin 13 for the built-in LED)
const int ledPin = 13;

// 3bc-lang interpreter object
bc_lang_t interpreter;

// Script for blinking the LED
const char blinkScript[] = R"(
    while (true) {
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
    }
)";

void setup() {
  // Initialize the LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Starting ArduinoBlink with 3bc-lang!");

  // Initialize the 3bc-lang interpreter
  bc_init(&interpreter);

  // Load the blink script into the interpreter
  if (bc_load(&interpreter, blinkScript) != BC_OK) {
    Serial.println("Failed to load script.");
  }
}

void loop() {
  // Execute the 3bc-lang script
  if (bc_exec(&interpreter) != BC_OK) {
    Serial.println("Script execution failed.");
  }
}

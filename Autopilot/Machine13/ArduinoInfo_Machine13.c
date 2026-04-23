#include <Arduino.h>              // Standard Arduino library
#include <3bc_lang.h>             // Include the 3bc-lang library

// 3bc-lang interpreter object
bc_lang_t interpreter;

// Script to print basic Arduino info using 3bc-lang
const char arduinoInfoScript[] = R"(
    // Arduino Info script
    Serial.print("Arduino Information:\n");
    Serial.print("Processor: ");
    Serial.print(ARDUINO_ARCH);     // Print the architecture
    Serial.print("\n");

    Serial.print("Flash memory size: ");
    Serial.print(FLASHEND);         // Print flash memory size
    Serial.print(" bytes\n");

    Serial.print("SRAM size: ");
    Serial.print(RAMEND);           // Print SRAM size
    Serial.print(" bytes\n");

    Serial.print("EEPROM size: ");
    Serial.print(E2END);            // Print EEPROM size
    Serial.print(" bytes\n");
)";

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  while (!Serial);  // Wait for the serial connection

  Serial.println("Starting ArduinoInfo with 3bc-lang!");

  // Initialize the 3bc-lang interpreter
  bc_init(&interpreter);

  // Load the Arduino info script into the interpreter
  if (bc_load(&interpreter, arduinoInfoScript) != BC_OK) {
    Serial.println("Failed to load script.");
  }
}

void loop() {
  // Execute the 3bc-lang script to print Arduino info
  if (bc_exec(&interpreter) != BC_OK) {
    Serial.println("Script execution failed.");
  }

  // Prevent continuous printing, so we'll stop after one execution
  while (true);
}

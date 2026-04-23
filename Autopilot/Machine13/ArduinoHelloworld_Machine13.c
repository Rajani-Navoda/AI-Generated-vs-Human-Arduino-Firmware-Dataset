#include <Arduino.h>              // Standard Arduino library
#include <3bc_lang.h>             // Include the 3bc-lang library

// 3bc-lang interpreter object
bc_lang_t interpreter;

// Script to print "Hello, World!" using 3bc-lang
const char helloWorldScript[] = R"(
    // Hello, World! script
    Serial.print("Hello, World!\n");
)";

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  while (!Serial);  // Wait for the serial connection

  Serial.println("Starting ArduinoHelloWorld with 3bc-lang!");

  // Initialize the 3bc-lang interpreter
  bc_init(&interpreter);

  // Load the Hello World script into the interpreter
  if (bc_load(&interpreter, helloWorldScript) != BC_OK) {
    Serial.println("Failed to load script.");
  }
}

void loop() {
  // Execute the 3bc-lang script to print "Hello, World!"
  if (bc_exec(&interpreter) != BC_OK) {
    Serial.println("Script execution failed.");
  }

  delay(1000);  // Add a delay to prevent spamming the message
}

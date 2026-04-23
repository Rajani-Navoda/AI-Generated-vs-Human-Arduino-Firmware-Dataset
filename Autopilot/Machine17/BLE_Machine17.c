// Libraries
#include <SPI.h>
#include "Adafruit_BLE_UART.h"
#include <aREST.h>

// Create an instance of the Adafruit_BLE_UART
Adafruit_BLE_UART bleUART;

// Create an instance of aREST
aREST rest = aREST();

// Function to be called when a command is received
void commandHandler(String command) {
  // Handle the command here
  if (command == "LED_ON") {
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the built-in LED
    rest.respond("LED is ON");
  } else if (command == "LED_OFF") {
    digitalWrite(LED_BUILTIN, LOW); // Turn off the built-in LED
    rest.respond("LED is OFF");
  } else {
    rest.respond("Unknown command");
  }
}

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the BLE UART
  bleUART.begin();
  
  // Initialize the aREST library
  rest.begin(bleUART);
  
  // Set the command handler
  rest.setCommandHandler(commandHandler);
  
  // Set the LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println("aREST and Adafruit BLE UART Example");
}

void loop() {
  // Check for incoming commands
  rest.handleClient();
  
  // Other code can go here (like sensor readings, etc.)
}

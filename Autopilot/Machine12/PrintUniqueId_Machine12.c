#include <Arduino.h>          // Standard Arduino library
#include <107-Arduino-UniqueId.h> // Include the 107-Arduino-UniqueId library

// Create a UniqueID object to access the unique identifier of the microcontroller
ArduinoUniqueID uniqueID;

void setup() {
  Serial.begin(9600);         // Initialize serial communication at 9600 baud
  while (!Serial);            // Wait for the serial port to open
  
  Serial.println("Device Unique ID:");
  
  // Print each byte of the unique ID in hexadecimal format
  for (size_t i = 0; i < uniqueID.size(); i++) {
    if (uniqueID[i] < 0x10) {
      Serial.print("0");       // Add leading zero for single digit hex values
    }
    Serial.print(uniqueID[i], HEX); // Print the byte in hexadecimal
  }
  Serial.println();            // Print a new line after the ID
}

void loop() {
  // No repeated actions needed in the loop
}

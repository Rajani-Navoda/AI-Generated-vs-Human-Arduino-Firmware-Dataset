/* 
 This example shows how to blink the three user LEDs
 on the A-Star 32U4.
*/

#include <AStar32U4.h>

// Define the LED pins
const int led1 = 13;  // User LED 1 (usually on pin 13)
const int led2 = 12;  // User LED 2 (usually on pin 12)
const int led3 = 11;  // User LED 3 (usually on pin 11)

// Function to blink the LEDs
void blinkLEDs() {
  digitalWrite(led1, HIGH);   // Turn on LED 1
  delay(1000);                 // Wait for 1 second
  digitalWrite(led1, LOW);    // Turn off LED 1
  delay(1000);                 // Wait for 1 second

  digitalWrite(led2, HIGH);   // Turn on LED 2
  delay(1000);                 // Wait for 1 second
  digitalWrite(led2, LOW);    // Turn off LED 2
  delay(1000);                 // Wait for 1 second

  digitalWrite(led3, HIGH);   // Turn on LED 3
  delay(1000);                 // Wait for 1 second
  digitalWrite(led3, LOW);    // Turn off LED 3
  delay(1000);                 // Wait for 1 second
}

void setup() {
  // Initialize the LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  blinkLEDs(); // Call the function to blink the LEDs
}

/* 
 This example demonstrates three different methods for
 detecting a button press and release. It blinks the green
 user LED each time button A is pressed and released.

 Note: This demo uses the standard button pins on the A-Star
 32U4 Prime and A-Star 32U4 Robot Controller. To avoid
 damage or improper operation, if you have shields or other
 electronics connected, make sure they do not use those pins
 in a conflicting way.
*/

#include <AStar32U4.h>

// Define the button pin and LED pin
const int buttonPin = 2;  // Button A is typically connected to pin 2
const int ledPin = 13;     // Green user LED pin

// Variables to hold the button state
int lastButtonState = LOW;  // Previous state of the button
int currentButtonState;      // Current state of the button
unsigned long lastDebounceTime = 0;  // Time of last debounce
unsigned long debounceDelay = 50;     // Debounce time

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
  pinMode(ledPin, OUTPUT);           // Set LED pin as output
  digitalWrite(ledPin, LOW);         // Turn off the LED initially
}

void loop() {
  // Read the current state of the button
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reset debounce timer
  }

  // Only consider the button pressed if the state has been stable for longer than debounceDelay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed and is now pressed
    if (reading == LOW && lastButtonState == HIGH) {
      // Button was pressed, blink the LED
      digitalWrite(ledPin, HIGH);   // Turn on the LED
      delay(100);                   // Wait for 100 milliseconds
      digitalWrite(ledPin, LOW);    // Turn off the LED
    }
  }

  // Save the current button state for the next loop iteration
  lastButtonState = reading;
}

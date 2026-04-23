#include <Keyboard.h>
#include <AStar32U4.h>

// Define button pins
const int buttonAPin = 2;  // Button A pin
const int buttonBPin = 3;  // Button B pin
const int buttonCPin = 4;  // Button C pin
const int buttonDPin = 12; // Optional button D pin

// Initialize button state variables
AStar32U4Button buttonA(buttonAPin);
AStar32U4Button buttonB(buttonBPin);
AStar32U4Button buttonC(buttonCPin);
AStar32U4Button buttonD(buttonDPin);

void setup() {
  // Start the keyboard
  Keyboard.begin();

  // Initialize buttons
  buttonA.begin();
  buttonB.begin();
  buttonC.begin();
  buttonD.begin();
}

void loop() {
  // Check for button presses
  if (buttonA.getSingleDebouncedPress()) {
    Keyboard.press('a');  // Send 'A'
    Keyboard.release('a');
  }

  if (buttonB.getSingleDebouncedPress()) {
    Keyboard.press('b');  // Send 'B'
    Keyboard.release('b');
  }

  if (buttonC.getSingleDebouncedPress()) {
    Keyboard.press('c');  // Send 'C'
    Keyboard.release('c');
  }

  if (buttonD.getSingleDebouncedPress()) {
    Keyboard.press('d');  // Send 'D'
    Keyboard.release('d');
  }

  // Add a short delay to prevent sending multiple keystrokes
  delay(50);
}
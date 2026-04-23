#include <AwesomeShield.h> // Include the Awesome Shield library

// Initialize the Awesome Shield
AwesomeShield shield;

// Pin definitions
#define POTENTIOMETER_PIN A0 // Potentiometer pin
#define BUTTON_PIN 2          // Button pin
#define RED_PIN 9            // Red pin for RGB LED
#define GREEN_PIN 10         // Green pin for RGB LED
#define BLUE_PIN 11          // Blue pin for RGB LED

int potValue; // Variable to store the potentiometer value
bool buttonPressed = false; // Flag to check if button is pressed

void setup() {
  // Initialize the Awesome Shield
  shield.begin();

  // Set pin modes
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button pin as input with pull-up
  pinMode(RED_PIN, OUTPUT);           // RGB LED pins as outputs
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Knob and Button Color Blender Initialized");
}

void loop() {
  // Read the potentiometer value (0-1023)
  potValue = analogRead(POTENTIOMETER_PIN);

  // Map the potentiometer value to 0-255 for RGB color values
  int redValue = map(potValue, 0, 1023, 0, 255);
  int greenValue = map(potValue, 0, 1023, 255, 0); // Inverse for green
  int blueValue = 128; // Fixed blue value (constant)

  // Set the RGB LED color based on potentiometer value
  setColor(redValue, greenValue, blueValue);

  // Check if the button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (!buttonPressed) { // Only act on the first press
      buttonPressed = true; // Set the flag to true
      // Print the RGB values to Serial Monitor
      Serial.print("RGB Values: R=");
      Serial.print(redValue);
      Serial.print(", G=");
      Serial.print(greenValue);
      Serial.print(", B=");
      Serial.println(blueValue);
    }
  } else {
    buttonPressed = false; // Reset the flag when button is released
  }

  delay(100); // Short delay to avoid flooding Serial Monitor
}

// Function to set the RGB LED color
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

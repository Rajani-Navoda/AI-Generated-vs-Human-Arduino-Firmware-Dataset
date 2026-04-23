#include <AwesomeShield.h> // Include the Awesome Shield library

// Initialize the Awesome Shield
AwesomeShield shield;

// Pin definitions
#define RED_PIN 9       // Pin connected to the Red LED
#define GREEN_PIN 10    // Pin connected to the Green LED
#define BLUE_PIN 11     // Pin connected to the Blue LED
#define RED_POT_PIN A0  // Pin for Red potentiometer
#define GREEN_POT_PIN A1 // Pin for Green potentiometer
#define BLUE_POT_PIN A2  // Pin for Blue potentiometer

void setup() {
  // Initialize the Awesome Shield
  shield.begin();
  
  // Set the RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Color Blender Initialized");
}

void loop() {
  // Read the potentiometer values (0-1023)
  int redValue = analogRead(RED_POT_PIN);
  int greenValue = analogRead(GREEN_POT_PIN);
  int blueValue = analogRead(BLUE_POT_PIN);

  // Map the potentiometer values to 0-255 for PWM
  redValue = map(redValue, 0, 1023, 0, 255);
  greenValue = map(greenValue, 0, 1023, 0, 255);
  blueValue = map(blueValue, 0, 1023, 0, 255);

  // Set the RGB LED color based on potentiometer values
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);

  // Print the RGB values to Serial Monitor for debugging
  Serial.print("R: ");
  Serial.print(redValue);
  Serial.print(" G: ");
  Serial.print(greenValue);
  Serial.print(" B: ");
  Serial.println(blueValue);

  delay(100); // Short delay to avoid flooding Serial Monitor
}

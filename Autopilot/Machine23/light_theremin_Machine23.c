#include <AwesomeShield.h> // Include the Awesome Shield library

// Initialize the Awesome Shield
AwesomeShield shield;

// Pin definitions
#define LIGHT_SENSOR_PIN A0 // Pin for the light sensor
#define BUZZER_PIN 9         // Pin for the buzzer

void setup() {
  // Initialize the Awesome Shield
  shield.begin();
  
  // Set the buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Start Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Light Theremin Initialized");
}

void loop() {
  // Read the light sensor value (0-1023)
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  
  // Print the light value to Serial Monitor for debugging
  Serial.print("Light Value: ");
  Serial.println(lightValue);

  // Map the light value to a frequency range (e.g., 200Hz to 2000Hz)
  int frequency = map(lightValue, 0, 1023, 200, 2000);

  // Generate the tone on the buzzer
  tone(BUZZER_PIN, frequency);

  // Add a short delay for better control
  delay(10);
}

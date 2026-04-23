#include <AwesomeShield.h> // Include the Awesome Shield library

// Initialize the Awesome Shield
AwesomeShield shield;

// Pin definition for the LED
#define LED_PIN 9  // Pin connected to the LED

void setup() {
  // Initialize the Awesome Shield
  shield.begin();
  
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
  
  // Start Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Candle Example Initialized");
}

void loop() {
  // Create a flickering candle effect
  flickerCandle();
}

// Function to create the flickering effect
void flickerCandle() {
  int flickerValue = random(180, 255); // Random brightness value (180-255)
  analogWrite(LED_PIN, flickerValue);  // Set LED brightness

  // Random delay to simulate flickering
  int delayTime = random(50, 150); // Random delay (50-150 ms)
  delay(delayTime);
}

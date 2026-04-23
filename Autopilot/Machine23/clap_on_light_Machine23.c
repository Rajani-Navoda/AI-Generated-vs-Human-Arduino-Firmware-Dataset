// Clap-On Light Project
// Detect claps using a microphone and toggle a light (LED) on or off

// Pin definitions
#define MIC_PIN A0     // Microphone sensor analog pin
#define LED_PIN 9      // LED connected to digital pin 9

// Variables to store the state of the light and claps
int ledState = LOW;
unsigned long clapTime = 0;
unsigned long lastClapTime = 0;
int clapThreshold = 600;  // Sensitivity threshold for the microphone (adjust as needed)
unsigned long debounceDelay = 500;  // Minimum time between claps in milliseconds

void setup() {
  // Initialize the microphone pin
  pinMode(MIC_PIN, INPUT);

  // Initialize the LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);

  // Start the serial communication for debugging
  Serial.begin(9600);
  Serial.println("Clap-On Light Project Initialized");
}

void loop() {
  // Read the sound level from the microphone sensor
  int soundLevel = analogRead(MIC_PIN);

  // Detect if a clap sound (loud sound) is detected
  if (soundLevel > clapThreshold && millis() - lastClapTime > debounceDelay) {
    // Save the current time as the time of the last clap
    lastClapTime = millis();

    // Toggle the LED state (on or off)
    ledState = !ledState;

    // Set the LED state
    digitalWrite(LED_PIN, ledState);

    // Print to Serial Monitor for debugging
    if (ledState == HIGH) {
      Serial.println("LED ON");
    } else {
      Serial.println("LED OFF");
    }
  }

  // Add a small delay to prevent overwhelming the sensor
  delay(50);
}

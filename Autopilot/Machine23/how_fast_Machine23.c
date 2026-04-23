#include <AwesomeShield.h> // Include the Awesome Shield library

// Initialize the Awesome Shield
AwesomeShield shield;

// Define the ultrasonic sensor pins
#define TRIG_PIN 9  // Trigger pin of the ultrasonic sensor
#define ECHO_PIN 10  // Echo pin of the ultrasonic sensor

long duration;    // Variable to hold the duration of the sound wave
float distance;   // Variable to hold the calculated distance
unsigned long lastMeasurementTime = 0; // Time of the last measurement
float speed;      // Variable to hold the calculated speed

void setup() {
  // Initialize the Awesome Shield
  shield.begin();

  // Set the ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Start Serial communication for debugging
  Serial.begin(9600);
  Serial.println("How Fast Project Initialized with Awesome Shield");
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm (Speed of sound is 34300 cm/s)
  distance = (duration / 2) * 0.0343;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Calculate speed if enough time has passed (e.g., 1 second)
  unsigned long currentTime = millis();
  if (currentTime - lastMeasurementTime >= 1000) {  // Every 1 second
    float timeInterval = (currentTime - lastMeasurementTime) / 1000.0; // Convert to seconds
    speed = distance / timeInterval; // Speed = distance/time
    lastMeasurementTime = currentTime; // Update last measurement time

    // Print speed to Serial Monitor
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" cm/s");
  }

  delay(100); // Short delay to avoid flooding the Serial Monitor
}

#include <107-Arduino-Servo-RP2040.h>

// Create a Servo object
Servo myServo;

// Define the pin where the servo is connected
const int servoPin = 9; // Change this to the pin you are using

void setup() {
    // Attach the servo to the specified pin
    myServo.attach(servoPin);
    Serial.begin(9600); // Initialize serial communication
    Serial.println("Servo control initialized.");
}

void loop() {
    // Move the servo to 0 degrees
    myServo.write(0);
    Serial.println("Servo moved to 0 degrees.");
    delay(1000); // Wait for 1 second

    // Move the servo to 90 degrees
    myServo.write(90);
    Serial.println("Servo moved to 90 degrees.");
    delay(1000); // Wait for 1 second

    // Move the servo to 180 degrees
    myServo.write(180);
    Serial.println("Servo moved to 180 degrees.");
    delay(1000); // Wait for 1 second
}

/* 
 This example drives each motor connected to the A-Star
 32U4 Robot Controller forward, then backward. The yellow
 user LED is on when a motor is set to a positive speed and
 off when a motor is set to a negative speed.
*/

#include <AStar32U4.h>

// Create an instance of the AStar32U4Motors class
AStar32U4Motors motors;

void setup() {
  // Initialize the motors
  motors.begin();
}

void loop() {
  // Drive motors forward
  motors.setSpeeds(100, 100); // Set both motors to full speed forward
  digitalWrite(LED_BUILTIN, HIGH); // Turn on yellow user LED
  delay(2000); // Drive forward for 2 seconds

  // Drive motors backward
  motors.setSpeeds(-100, -100); // Set both motors to full speed backward
  digitalWrite(LED_BUILTIN, LOW); // Turn off yellow user LED
  delay(2000); // Drive backward for 2 seconds

  // Stop motors
  motors.setSpeeds(0, 0); // Stop both motors
  delay(1000); // Wait for 1 second before repeating
}

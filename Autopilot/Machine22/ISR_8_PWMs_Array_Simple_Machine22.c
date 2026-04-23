// Include the ATmega_Slow_PWM library
#include "ATmega_Slow_PWM.h"

// Define pins for the first 8 PWM channels
#define PWM_PIN_1 3   // Channel 1 PWM pin
#define PWM_PIN_2 4   // Channel 2 PWM pin
#define PWM_PIN_3 5   // Channel 3 PWM pin
#define PWM_PIN_4 6   // Channel 4 PWM pin
#define PWM_PIN_5 7   // Channel 5 PWM pin
#define PWM_PIN_6 8   // Channel 6 PWM pin
#define PWM_PIN_7 9   // Channel 7 PWM pin
#define PWM_PIN_8 10  // Channel 8 PWM pin

// Create 8 PWM objects for ISR-based PWM channels
ATmega_Slow_PWM ISR_PWM1;
ATmega_Slow_PWM ISR_PWM2;
ATmega_Slow_PWM ISR_PWM3;
ATmega_Slow_PWM ISR_PWM4;
ATmega_Slow_PWM ISR_PWM5;
ATmega_Slow_PWM ISR_PWM6;
ATmega_Slow_PWM ISR_PWM7;
ATmega_Slow_PWM ISR_PWM8;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Starting ISR_8_PWMs_Array_Simple");

  // Set up 8 PWM channels with independent frequency and duty cycles
  ISR_PWM1.setPWM(PWM_PIN_1, 1000, 50);    // Channel 1: 1kHz, 50% duty cycle
  ISR_PWM2.setPWM(PWM_PIN_2, 500, 25);     // Channel 2: 500Hz, 25% duty cycle
  ISR_PWM3.setPWM(PWM_PIN_3, 250, 75);     // Channel 3: 250Hz, 75% duty cycle
  ISR_PWM4.setPWM(PWM_PIN_4, 2000, 10);    // Channel 4: 2kHz, 10% duty cycle
  ISR_PWM5.setPWM(PWM_PIN_5, 1500, 60);    // Channel 5: 1.5kHz, 60% duty cycle
  ISR_PWM6.setPWM(PWM_PIN_6, 3000, 90);    // Channel 6: 3kHz, 90% duty cycle
  ISR_PWM7.setPWM(PWM_PIN_7, 4000, 50);    // Channel 7: 4kHz, 50% duty cycle
  ISR_PWM8.setPWM(PWM_PIN_8, 6000, 40);    // Channel 8: 6kHz, 40% duty cycle
}

void loop() {
  // The ISR handles all PWM channels independently
  // Main loop is free for other tasks

  // Example: Dynamically change duty cycle of Channel 1 every 5 seconds
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 5000) {
    int newDutyCycle = random(10, 90); // Random duty cycle between 10% and 90%
    ISR_PWM1.setPWM(PWM_PIN_1, 1000, newDutyCycle);  // Update Channel 1 with new duty cycle
    Serial.print("Updated PWM1 Duty Cycle to: ");
    Serial.print(newDutyCycle);
    Serial.println("%");
    lastTime = millis();
  }

  delay(100);  // Short delay for Serial monitoring
}

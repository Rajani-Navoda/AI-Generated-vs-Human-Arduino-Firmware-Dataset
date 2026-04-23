// Include the ATmega_Slow_PWM library
#include "ATmega_Slow_PWM.h"

// Define pins for the PWM signals
#define PWM_PIN_1 9   // PWM signal output pin for Channel 1
#define PWM_PIN_2 10  // PWM signal output pin for Channel 2
// Add more pins as needed for the other PWM channels

// Define PWM frequencies and duty cycles for each channel
#define PWM_FREQ_1 1000  // Frequency for PWM Channel 1 (1 kHz)
#define PWM_FREQ_2 500   // Frequency for PWM Channel 2 (500 Hz)
// Add more frequencies for additional channels

#define PWM_DUTY_1 50    // Duty cycle for PWM Channel 1 (50%)
#define PWM_DUTY_2 75    // Duty cycle for PWM Channel 2 (75%)
// Add more duty cycles for additional channels

// Create PWM objects for each channel
ATmega_Slow_PWM ISR_PWM1;
ATmega_Slow_PWM ISR_PWM2;
// Add more PWM objects for additional channels (up to 16 channels)

void setup() {
  // Initialize the Serial Monitor for debugging
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Starting ISR_8_PWMs_Array");

  // Initialize PWM on Channel 1
  ISR_PWM1.setPWM(PWM_PIN_1, PWM_FREQ_1, PWM_DUTY_1);
  Serial.print("PWM1 => Freq: "); Serial.print(PWM_FREQ_1); 
  Serial.print(" Hz, Duty Cycle: "); Serial.print(PWM_DUTY_1); Serial.println("%");

  // Initialize PWM on Channel 2
  ISR_PWM2.setPWM(PWM_PIN_2, PWM_FREQ_2, PWM_DUTY_2);
  Serial.print("PWM2 => Freq: "); Serial.print(PWM_FREQ_2); 
  Serial.print(" Hz, Duty Cycle: "); Serial.print(PWM_DUTY_2); Serial.println("%");

  // Repeat for more channels if necessary
}

void loop() {
  // In the loop, the PWM signals are handled by the ISR
  // You can adjust frequency and duty cycle on the fly if needed

  // Example: Adjust duty cycle of Channel 1
  if (millis() % 5000 == 0) {
    int newDuty = random(10, 90); // Random duty cycle between 10% and 90%
    ISR_PWM1.setPWM(PWM_PIN_1, PWM_FREQ_1, newDuty);
    Serial.print("Updated PWM1 Duty Cycle to: "); Serial.print(newDuty); Serial.println("%");
  }

  delay(100);  // Short delay to reduce Serial output flooding
}

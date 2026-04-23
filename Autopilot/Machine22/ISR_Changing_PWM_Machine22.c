// Include the ATmega_Slow_PWM library
#include "ATmega_Slow_PWM.h"

// Define the pins for PWM channels
#define PWM_PIN_1 3   // PWM signal for Channel 1
#define PWM_PIN_2 4   // PWM signal for Channel 2

// Create PWM objects for the ISR-based PWM channels
ATmega_Slow_PWM ISR_PWM1;
ATmega_Slow_PWM ISR_PWM2;

// Variables for dynamic changes in frequency and duty cycle
unsigned long currentMillis;
unsigned long lastUpdateMillis = 0;
unsigned long updateInterval = 5000;  // Update every 5 seconds

int freq1 = 1000;   // Starting frequency for Channel 1
int duty1 = 50;     // Starting duty cycle for Channel 1 (50%)
int freq2 = 500;    // Starting frequency for Channel 2
int duty2 = 25;     // Starting duty cycle for Channel 2 (25%)

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Starting ISR_Changing_PWM");

  // Initialize PWM for two channels with initial values
  ISR_PWM1.setPWM(PWM_PIN_1, freq1, duty1);
  ISR_PWM2.setPWM(PWM_PIN_2, freq2, duty2);
}

void loop() {
  // Get the current time
  currentMillis = millis();

  // Check if it's time to update the PWM settings
  if (currentMillis - lastUpdateMillis >= updateInterval) {
    // Update frequency and duty cycle for Channel 1
    freq1 += 500;  // Increase frequency by 500 Hz
    if (freq1 > 5000) freq1 = 1000;  // Reset if it goes above 5000 Hz
    duty1 = random(10, 90);  // Randomize duty cycle between 10% and 90%
    ISR_PWM1.setPWM(PWM_PIN_1, freq1, duty1);  // Apply new settings

    // Update frequency and duty cycle for Channel 2
    freq2 += 200;  // Increase frequency by 200 Hz
    if (freq2 > 3000) freq2 = 500;  // Reset if it goes above 3000 Hz
    duty2 = random(10, 90);  // Randomize duty cycle between 10% and 90%
    ISR_PWM2.setPWM(PWM_PIN_2, freq2, duty2);  // Apply new settings

    // Print the updated PWM settings to Serial Monitor
    Serial.print("PWM1 => Freq: "); Serial.print(freq1); 
    Serial.print(" Hz, Duty Cycle: "); Serial.print(duty1); Serial.println("%");

    Serial.print("PWM2 => Freq: "); Serial.print(freq2); 
    Serial.print(" Hz, Duty Cycle: "); Serial.print(duty2); Serial.println("%");

    // Update the last time the PWM values were changed
    lastUpdateMillis = currentMillis;
  }
  
  delay(100);  // Short delay to prevent excessive serial output
}

// awasome.cpp - Implementation file for candle effect

#include "awasome.h"

// Constructor: Initialize with the pin number where the LED is connected
CandleEffect::CandleEffect(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);          // Set the pin as output for the LED
  _brightness = 0;                // Initialize brightness to 0
  _lastFlickerTime = 0;           // Initialize the last flicker time
  _flickerInterval = random(50, 150);  // Random flicker speed between 50ms and 150ms
}

// Flicker function to simulate candle effect
void CandleEffect::flicker() {
  unsigned long currentTime = millis();  // Get the current time in milliseconds

  // Check if it's time to update the flicker effect
  if (currentTime - _lastFlickerTime >= _flickerInterval) {
    // Generate a random brightness between 100 and 255
    _brightness = random(100, 255);

    // Apply the brightness to the LED using PWM
    analogWrite(_pin, _brightness);

    // Update the flicker interval to keep it random
    _flickerInterval = random(50, 150);

    // Update the last flicker time
    _lastFlickerTime = currentTime;
  }
}

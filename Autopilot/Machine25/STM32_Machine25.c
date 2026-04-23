#include <Joystick.h>
#include <AxisJoystick.h>

// Create an instance of the AxisJoystick class
AxisJoystick joystick;

// Calibration parameters
const int LOW_BOUND = 100;   // Default lower bound for joystick
const int HIGH_BOUND = 4095; // Adjust for STM32's ADC range
const int ADC_MIN = 0;       // Minimum value for STM32 ADC
const int ADC_MAX = 4095;    // Maximum value for STM32 ADC
const int DEVIATION = 100;    // Deviation from value’s axis range

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Axis Joystick Calibration for STM32");

    // Call the calibration method
    joystick.calibrate(LOW_BOUND, HIGH_BOUND); // Calibrate joystick values
}

void loop() {
    // Read joystick axes values
    int xValue = joystick.getXAxis(); // Read X axis value
    int yValue = joystick.getYAxis(); // Read Y axis value
    int buttonValue = joystick.getButton(); // Read button value

    // Display joystick values on the Serial Monitor
    Serial.print("X Axis: ");
    Serial.print(xValue);
    Serial.print("\tY Axis: ");
    Serial.print(yValue);
    Serial.print("\tButton: ");
    Serial.println(buttonValue == HIGH ? "Pressed" : "Released");

    // Add a delay for readability
    delay(500);
}
#include <Joystick.h>
#include <AxisJoystick.h>

// Create an instance of the AxisJoystick class
AxisJoystick joystick;

// Calibration parameters
const int LOW_BOUND = 100;   // Default lower bound for joystick
const int HIGH_BOUND = 4095; // Adjust for STM32's ADC range
const int ADC_MIN = 0;       // Minimum value for STM32 ADC
const int ADC_MAX = 4095;    // Maximum value for STM32 ADC
const int DEVIATION = 100;    // Deviation from value’s axis range

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Axis Joystick Calibration for STM32");

    // Call the calibration method
    joystick.calibrate(LOW_BOUND, HIGH_BOUND); // Calibrate joystick values
}

void loop() {
    // Read joystick axes values
    int xValue = joystick.getXAxis(); // Read X axis value
    int yValue = joystick.getYAxis(); // Read Y axis value
    int buttonValue = joystick.getButton(); // Read button value

    // Display joystick values on the Serial Monitor
    Serial.print("X Axis: ");
    Serial.print(xValue);
    Serial.print("\tY Axis: ");
    Serial.print(yValue);
    Serial.print("\tButton: ");
    Serial.println(buttonValue == HIGH ? "Pressed" : "Released");

    // Add a delay for readability
    delay(500);
}

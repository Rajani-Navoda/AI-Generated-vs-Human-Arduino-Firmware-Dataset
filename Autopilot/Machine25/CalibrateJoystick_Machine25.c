#include <Joystick.h>
#include <AxisJoystick.h>

// Create an instance of the AxisJoystick class
AxisJoystick joystick;

// Define lower and upper bounds for calibration
const int LOW_BOUND = 100;
const int HIGH_BOUND = 923;

// Define deviation from the value’s axis range
const int DEVIATION = 100;

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Joystick Calibration Example");

    // Calibrate the joystick
    joystick.calibrate(LOW_BOUND, HIGH_BOUND, ADC_MIN, ADC_MAX, DEVIATION);
}

void loop() {
    // Read joystick axes values
    int xValue = joystick.getXAxis(); // Read X axis value
    int yValue = joystick.getYAxis(); // Read Y axis value
    int buttonValue = joystick.getButton(); // Read button value

    // Display the joystick values on the Serial Monitor
    Serial.print("X Axis: ");
    Serial.print(xValue);
    Serial.print("\tY Axis: ");
    Serial.print(yValue);
    Serial.print("\tButton: ");
    Serial.println(buttonValue == HIGH ? "Pressed" : "Released");

    // Add a delay for readability
    delay(500);
}

#include <Joystick.h>
#include <AxisJoystick.h>
#include <XInverterJoystick.h>
#include <YInverterJoystick.h>

// Create instances for joystick and inverters
AxisJoystick joystick;
XInverterJoystick xInverter;
YInverterJoystick yInverter;

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Joystick Axis Inversion Example");

    // Optionally calibrate joystick if necessary
    // joystick.calibrate(100, 923, 0, 1023, 100);
}

void loop() {
    // Read joystick axes values
    int xValue = joystick.getXAxis(); // Read X axis value
    int yValue = joystick.getYAxis(); // Read Y axis value
    int buttonValue = joystick.getButton(); // Read button value

    // Invert the X and Y axis values if necessary
    int invertedXValue = xInverter.invert(xValue); // Inverted X axis
    int invertedYValue = yInverter.invert(yValue); // Inverted Y axis

    // Display the original and inverted joystick values on the Serial Monitor
    Serial.print("Original X Axis: ");
    Serial.print(xValue);
    Serial.print("\tInverted X Axis: ");
    Serial.print(invertedXValue);
    Serial.print("\tOriginal Y Axis: ");
    Serial.print(yValue);
    Serial.print("\tInverted Y Axis: ");
    Serial.println(invertedYValue);

    // Display the button state
    Serial.print("Button: ");
    Serial.println(buttonValue == HIGH ? "Pressed" : "Released");

    // Add a delay for readability
    delay(500);
}

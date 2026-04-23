#include <Joystick.h>
#include <AxisJoystick.h>

// Create an instance of the AxisJoystick class
AxisJoystick joystick;

// Function to replace and invert joystick axes
void readAndInvertJoystick() {
    // Read joystick axes values
    int xValue = joystick.getXAxis(); // Read X axis value
    int yValue = joystick.getYAxis(); // Read Y axis value
    int buttonValue = joystick.getButton(); // Read button value

    // Invert the X and Y axis values
    int invertedXValue = 1023 - xValue; // Inverting X axis
    int invertedYValue = 1023 - yValue; // Inverting Y axis

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
}

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Replace and Invert Joystick Axes Example");
}

void loop() {
    readAndInvertJoystick(); // Read and display joystick values
    delay(500); // Add a delay for readability
}

#include <Joystick.h>
#include <AxisJoystick.h>

// Create an instance of the AxisJoystick class
AxisJoystick joystick;

// Function to read and swap joystick axes
void readAndSwapJoystick() {
    // Read joystick axes values
    int xValue = joystick.getXAxis(); // Read X axis value
    int yValue = joystick.getYAxis(); // Read Y axis value
    int buttonValue = joystick.getButton(); // Read button value

    // Swap the X and Y axis values
    int swappedXValue = yValue; // Swapped X axis value
    int swappedYValue = xValue; // Swapped Y axis value

    // Display the original and swapped joystick values on the Serial Monitor
    Serial.print("Original X Axis: ");
    Serial.print(xValue);
    Serial.print("\tSwapped X Axis: ");
    Serial.print(swappedXValue);
    Serial.print("\tOriginal Y Axis: ");
    Serial.print(yValue);
    Serial.print("\tSwapped Y Axis: ");
    Serial.println(swappedYValue);

    // Display the button state
    Serial.print("Button: ");
    Serial.println(buttonValue == HIGH ? "Pressed" : "Released");
}

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Replace (Swap) Joystick Axes Example");
}

void loop() {
    readAndSwapJoystick(); // Read and display joystick values
    delay(500); // Add a delay for readability
}

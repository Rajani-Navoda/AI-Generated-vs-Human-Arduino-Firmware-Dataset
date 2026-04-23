#include <Joystick.h>
#include <AxisJoystick.h>

// Create an instance of the AxisJoystick class
AxisJoystick joystick;

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Joystick Serial Monitor Example");
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

    // Add a small delay for readability
    delay(100); // Adjust delay as needed
}

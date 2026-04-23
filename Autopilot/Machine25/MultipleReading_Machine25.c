#include <Joystick.h>
#include <AxisJoystick.h>

// Create an instance of the AxisJoystick class
AxisJoystick joystick;

// Define movement states for joystick
enum Move {
    PRESS,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    NOT
};

// Function to read the joystick state
Move readJoystick() {
    int xValue = joystick.getXAxis(); // Get X-axis value
    int yValue = joystick.getYAxis(); // Get Y-axis value

    // Define threshold for detecting joystick movement
    const int threshold = 100; // Adjust this threshold based on your joystick

    // Check if joystick is pressed
    if (joystick.getButton() == HIGH) {
        return PRESS; // Button is pressed
    }
    // Check for joystick movement
    else if (xValue < 512 - threshold) {
        return LEFT; // Joystick is pressed left
    }
    else if (xValue > 512 + threshold) {
        return RIGHT; // Joystick is pressed right
    }
    else if (yValue < 512 - threshold) {
        return UP; // Joystick is pressed up
    }
    else if (yValue > 512 + threshold) {
        return DOWN; // Joystick is pressed down
    }
    return NOT; // No movement detected
}

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Axis Joystick Multiple Reading Example");
}

void loop() {
    Move joystickState = readJoystick(); // Get joystick state

    // Display the joystick state on the Serial Monitor
    switch (joystickState) {
        case PRESS:
            Serial.println("Button Pressed");
            break;
        case UP:
            Serial.println("Joystick Moved Up");
            break;
        case DOWN:
            Serial.println("Joystick Moved Down");
            break;
        case RIGHT:
            Serial.println("Joystick Moved Right");
            break;
        case LEFT:
            Serial.println("Joystick Moved Left");
            break;
        case NOT:
            Serial.println("Joystick Not Pressed");
            break;
    }

    // Add a delay for readability
    delay(500);
}

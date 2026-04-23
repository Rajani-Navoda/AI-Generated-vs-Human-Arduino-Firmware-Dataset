#include <Joystick.h>
#include <AxisJoystick.h>

// Create an instance of the AxisJoystick class
AxisJoystick joystick;

// Enumeration for joystick movement states
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
    // Get the X and Y axis values
    int xValue = joystick.getXAxis();
    int yValue = joystick.getYAxis();
    
    // Check the button state
    int buttonValue = joystick.getButton();

    // Determine joystick movement
    if (buttonValue == HIGH) {
        return PRESS; // Button is pressed
    }
    if (yValue < 400) { // Adjust threshold for UP movement
        return UP;
    }
    if (yValue > 600) { // Adjust threshold for DOWN movement
        return DOWN;
    }
    if (xValue > 600) { // Adjust threshold for RIGHT movement
        return RIGHT;
    }
    if (xValue < 400) { // Adjust threshold for LEFT movement
        return LEFT;
    }
    
    return NOT; // No movement detected
}

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(9600);
    Serial.println("Single Reading Joystick Example");
}

void loop() {
    // Read the joystick state
    Move joystickState = readJoystick();

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
            Serial.println("No Movement Detected");
            break;
    }

    // Add a small delay for readability
    delay(200); // Adjust delay as needed
}
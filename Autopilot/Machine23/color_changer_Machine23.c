// Color Changer Project
// Change the color of an RGB LED with a button press

// Pin definitions
#define RED_PIN 9     // Red pin of RGB LED
#define GREEN_PIN 10  // Green pin of RGB LED
#define BLUE_PIN 11   // Blue pin of RGB LED
#define BUTTON_PIN 2  // Button pin

// Color definitions
enum Color { RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, OFF };
Color currentColor = OFF;  // Start with the LED turned off

void setup() {
  // Initialize RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Initialize button pin as input with pull-down resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Start Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Color Changer Project Initialized");
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Change the color when the button is pressed
    changeColor();
    
    // Wait for button release to avoid multiple changes
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(10); // Debounce delay
    }
    
    delay(200); // Delay to prevent multiple changes from one press
  }
}

// Function to change the color of the RGB LED
void changeColor() {
  currentColor = static_cast<Color>((currentColor + 1) % 8); // Cycle through colors

  // Set the RGB LED based on the current color
  switch (currentColor) {
    case RED:
      setColor(255, 0, 0);
      Serial.println("Color: RED");
      break;
    case GREEN:
      setColor(0, 255, 0);
      Serial.println("Color: GREEN");
      break;
    case BLUE:
      setColor(0, 0, 255);
      Serial.println("Color: BLUE");
      break;
    case YELLOW:
      setColor(255, 255, 0);
      Serial.println("Color: YELLOW");
      break;
    case CYAN:
      setColor(0, 255, 255);
      Serial.println("Color: CYAN");
      break;
    case MAGENTA:
      setColor(255, 0, 255);
      Serial.println("Color: MAGENTA");
      break;
    case WHITE:
      setColor(255, 255, 255);
      Serial.println("Color: WHITE");
      break;
    case OFF:
      setColor(0, 0, 0);
      Serial.println("Color: OFF");
      break;
  }
}

// Function to set the RGB LED color
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

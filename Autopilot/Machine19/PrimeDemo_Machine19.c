/* 
 This demo program shows many features of the
 A-Star 32U4 Prime.

 It uses the buttons, LCD, and buzzer to provide a user
 interface. It presents a menu to the user that lets the
 user select from several different demos.

 To use this demo program, you will need to have an LCD
 connected to the A-Star 32U4 Prime. If you cannot see any
 text on the LCD, try rotating the contrast potentiometer.

 Note: This demo uses the standard A-Star 32U4 Prime LCD
 pins, buzzer pin, button pins, microSD pins, and pin 4. To
 avoid damage or improper operation, if you have shields or
 other electronics connected, make sure they do not use those
 pins in a conflicting way.

 == microSD card considerations ==

 To use the microSD card portion of this program, you will
 need to install a jumper between GND and CS.

 (You will also need to have a version of the A-Star 32U4
 with a microSD card socket and you will need to insert a
 formatted microSD card into the socket.)

 Note: While the GND/CS jumper is installed, button A will
 not work.

 Note: If the GND/CS jumper is installed and the microSD card
 is not inserted, the state of the DO signal from the microSD
 card will be undefined. This could waste power and might
 also cause this program to detect spurious presses on button
 A.

 To avoid these issues, you can connect CS to pin 4 using a
 male-female jumper wire instead of connecting CS to GND.
 This demo drives pin 4 low whenever the microSD card is
 accessed and drives it high the rest of the time, allowing
 button A to work properly.
*/

// This demo assumes you are using the A-Star 32U4 Prime LV
// (ac03e version, blue). If not, then comment out the line
// "#define A_STAR_LV" below and uncomment the line that
// corresponds to your board.

// A-Star 32U4 Prime LV (ac03e)
#define A_STAR_LV

// A-Star 32U4 Prime LV (ac03b)
//#define A_STAR_LV_AC03B

// A-Star 32U4 Prime SV
//#define A_STAR_SV

// This demo drives pin 4 low whenever the SD card is being used.
const uint8_t chipSelect = 4;

#include <AStar32U4.h>
#include <SPI.h>
#include <SD.h>
#include <Keyboard.h>
#include <AStar32U4LCD.h>
#include <AStar32U4Buzzer.h>

// Create instances for LCD and Buzzer
AStar32U4LCD lcd;
AStar32U4Buzzer buzzer;

// Function prototypes
void displayMenu();
void runDemo(int demoNumber);
void demo1();
void demo2();
void demo3();

void setup() {
    // Initialize LCD
    lcd.begin();
    lcd.clear();
    lcd.print("A-Star Demo");

    // Initialize buzzer
    buzzer.begin();

    // Initialize Serial for debugging
    Serial.begin(9600);

    // Initialize SD card
    pinMode(chipSelect, OUTPUT);
    digitalWrite(chipSelect, HIGH); // Disable the SD card
    if (!SD.begin(chipSelect)) {
        lcd.print("SD init failed");
        Serial.println("SD init failed");
        return;
    }
    Serial.println("SD initialized");
    digitalWrite(chipSelect, LOW); // Enable the SD card
}

void loop() {
    displayMenu();
    
    // Wait for button A press
    while (!getButtonPress(BUTTON_A_PIN)) {
        // Do nothing until button A is pressed
    }

    int demoNumber = getSelectedDemo(); // Get the demo number from the menu
    runDemo(demoNumber); // Run the selected demo

    // Wait for button A release
    while (getButtonPress(BUTTON_A_PIN)) {
        // Do nothing until button A is released
    }
}

void displayMenu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Select Demo:");
    lcd.setCursor(0, 1);
    lcd.print("1: Demo 1");
    lcd.setCursor(0, 2);
    lcd.print("2: Demo 2");
    lcd.setCursor(0, 3);
    lcd.print("3: Demo 3");
}

void runDemo(int demoNumber) {
    switch (demoNumber) {
        case 1:
            demo1();
            break;
        case 2:
            demo2();
            break;
        case 3:
            demo3();
            break;
        default:
            lcd.print("Invalid demo");
            break;
    }
}

void demo1() {
    lcd.clear();
    lcd.print("Demo 1 Running");
    buzzer.playFrequency(440, 500); // Play A4 note
    delay(1000);
}

void demo2() {
    lcd.clear();
    lcd.print("Demo 2 Running");
    // Add functionality for demo 2
    delay(1000);
}

void demo3() {
    lcd.clear();
    lcd.print("Demo 3 Running");
    // Add functionality for demo 3
    delay(1000);
}

bool getButtonPress(uint8_t buttonPin) {
    return digitalRead(buttonPin) == HIGH;
}

int getSelectedDemo() {
    // In this simple example, we always select demo 1
    // Implement actual button handling logic here to choose different demos
    return 1;
}

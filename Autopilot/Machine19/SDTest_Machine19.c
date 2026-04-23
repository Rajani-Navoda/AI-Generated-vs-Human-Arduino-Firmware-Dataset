/* 
 This is a test program for the A-Star 32U4 Prime that
 tests to make sure the SD card, LCD, 3 user LEDs, and 3
 buttons can all be used at the same time even though they
 are sharing a lot of pins.

 It looks for a file named "test.txt" in the top-level
 directory on the SD card and opens it.  Every time one of
 the buttons is pressed, it reads 512 more bytes from the SD
 card just to make sure that any cached data in the SD
 libraries have been used up, and then it reads 8 more bytes
 from the file.  Those 8 characters are displayed on the LCD
 and printed to the serial monitor.

 Note: This demo uses the standard A-Star 32U4 Prime LCD
 pins, buzzer pin, button pins, microSD pins, and pin 4. To
 avoid damage or improper operation, if you have shields or
 other electronics connected, make sure they do not use those
 pins in a conflicting way.

 == microSD card considerations ==

 You will need to install a jumper between GND and CS to
 enable the microSD card.

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
 This program drives pin 4 low whenever the microSD card is
 accessed and drives it high the rest of the time, allowing
 button A to work properly.
*/

#include <AStar32U4.h>
#include <SPI.h>
#include <SD.h>

// Create instances for LCD, Buzzer, and Buttons
AStar32U4LCD lcd;
AStar32U4Buzzer buzzer;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;

const uint8_t chipSelect = 4; // Chip select pin for the SD card
File myFile; // File object for the SD card

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    
    // Initialize LCD
    lcd.begin();
    lcd.clear();
    lcd.print("Initializing...");

    // Initialize SD card
    pinMode(chipSelect, OUTPUT);
    digitalWrite(chipSelect, HIGH); // Disable the SD card
    if (!SD.begin(chipSelect)) {
        lcd.print("SD init failed");
        Serial.println("SD init failed");
        while (1); // Halt the program
    }
    Serial.println("SD initialized");

    // Open the file
    myFile = SD.open("test.txt");
    if (!myFile) {
        lcd.print("File open failed");
        Serial.println("File open failed");
        while (1); // Halt the program
    }
    lcd.print("File opened");
}

void loop() {
    // Check if button A is pressed
    if (buttonA.isPressed()) {
        readAndDisplayData();
    }
    // You can add checks for button B and button C here if needed
}

void readAndDisplayData() {
    // Read 512 bytes from the SD card to clear any cached data
    char buffer[512];
    myFile.read(buffer, 512);

    // Read 8 bytes from the file
    char data[9]; // 8 characters + null terminator
    int bytesRead = myFile.read(data, 8);
    data[bytesRead] = '\0'; // Null-terminate the string

    // Display the data on the LCD
    lcd.clear();
    lcd.print(data);
    
    // Print the data to the serial monitor
    Serial.print("Data: ");
    Serial.println(data);
}

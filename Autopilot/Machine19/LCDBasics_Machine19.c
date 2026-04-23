/* 
 This example demonstrates basic use of the A-Star 32U4
 Prime LCD. It prints the word "hi" on the first line of the
 LCD and prints the number 1234 on the second line.

 Note: This demo uses the standard A-Star 32U4 Prime LCD
 pins. To avoid damage or improper operation, if you have
 shields or other electronics connected, make sure they do
 not use those pins in a conflicting way.
*/

#include <AStar32U4.h>
#include <AStar32U4LCD.h> // Include the library for the A-Star 32U4 LCD

// Create an instance of the AStar32U4LCD class
AStar32U4LCD lcd;

void setup() {
  // Initialize the LCD
  lcd.begin();

  // Print "hi" on the first line
  lcd.print("hi");

  // Move to the second line
  lcd.setCursor(0, 1);

  // Print the number 1234 on the second line
  lcd.print(1234);
}

void loop() {
  // Nothing to do here
}

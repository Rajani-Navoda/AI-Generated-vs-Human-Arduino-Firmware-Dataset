
#include <AStar32U4.h>

AStar32U4LCD lcd;

void setup()
{

}

void loop()
{
  // Clear the screen
  lcd.clear();

  // Print a string
  lcd.print("hi");

  // Go to the next line
  lcd.gotoXY(0, 1);

  // Print a number
  lcd.print(1234);

  delay(1000);
}
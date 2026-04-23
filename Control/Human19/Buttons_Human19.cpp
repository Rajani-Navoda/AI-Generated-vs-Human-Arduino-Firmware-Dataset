#include <AStar32U4.h>

// These objects provide access to the A-Star's on-board
// buttons.  We will only use buttonA.
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;

void setup()
{

}

void loop()
{
  
  do
  {
    while (!buttonA.isPressed());  // wait for button to be pressed
    delay(10);                     // debounce the button press
  }
  while (!buttonA.isPressed());    // if button isn't still pressed, loop

  do
  {
    while (buttonA.isPressed());   // wait for button to be released
    delay(10);                     // debounce the button release
  }
  while (buttonA.isPressed());     // if button isn't still released, loop

  // blink LED
  ledGreen(1);
  delay(200);
  ledGreen(0);

 
  buttonA.waitForButton();

  // blink LED
  ledGreen(1);
  delay(200);
  ledGreen(0);

  while (1)
  {
    if (buttonA.getSingleDebouncedRelease())
    {
      // blink LED
      ledGreen(1);
      delay(200);
      ledGreen(0);
      break;
    }
  }
}

#include <Keyboard.h>
#include <AStar32U4.h>

// These objects provide access to the A-Star's on-board
// buttons:
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;
Pushbutton buttonD(12);

void setup() {
  Keyboard.begin();
}

void loop() {
  if (buttonA.getSingleDebouncedPress()) { Keyboard.press('a'); }
  if (!buttonA.isPressed()) { Keyboard.release('a'); }

  if (buttonB.getSingleDebouncedPress()) { Keyboard.press('b'); }
  if (!buttonB.isPressed()) { Keyboard.release('b'); }

  if (buttonC.getSingleDebouncedPress()) { Keyboard.press('c'); }
  if (!buttonC.isPressed()) { Keyboard.release('c'); }

  if (buttonD.getSingleDebouncedPress()) { Keyboard.press('d'); }
  if (!buttonD.isPressed()) { Keyboard.release('d'); }
}
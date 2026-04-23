/* 
 This example uses the AStar32U4Buzzer class to play a
 series of notes on the buzzer.

 This example demonstrates the use of the playFrequency(),
 playNote(), and playFromProgramSpace() functions, which play
 entirely in the background, requiring no further action from
 the user once the function is called. The CPU is then free
 to execute other code while the buzzer plays.

 This example also shows how to use the stopPlaying()
 function to stop the buzzer, and it shows how to use the
 isPlaying() function to tell whether the buzzer is still
 playing or not.

 For this example to work, you will need to have a buzzer
 soldered into the A-Star, and you will need to install a
 shorting block on the two pins near the buzzer, which will
 connect pin 6 to the buzzer.

 Note: This demo uses pin 6 to control the buzzer. To avoid
 damage or improper operation, if you have shields or other
 electronics connected, make sure they do not use that pin in
 a conflicting way.
*/

#include <AStar32U4.h>

// Create an instance of the AStar32U4Buzzer class
AStar32U4Buzzer buzzer;

// Define notes and their corresponding frequencies
const int noteC = 261; // C note frequency in Hz
const int noteD = 294; // D note frequency in Hz
const int noteE = 329; // E note frequency in Hz
const int noteF = 349; // F note frequency in Hz
const int noteG = 392; // G note frequency in Hz

void setup() {
  // Initialize the buzzer
  buzzer.begin();
  
  // Play a series of notes
  buzzer.playNote(noteC); // Play C note
  delay(500);              // Wait for half a second
  buzzer.playNote(noteD); // Play D note
  delay(500);              // Wait for half a second
  buzzer.playNote(noteE); // Play E note
  delay(500);              // Wait for half a second
  buzzer.playNote(noteF); // Play F note
  delay(500);              // Wait for half a second
  buzzer.playNote(noteG); // Play G note
  delay(500);              // Wait for half a second
  
  // Stop the buzzer after playing
  buzzer.stopPlaying();
}

void loop() {
  // You can check if the buzzer is still playing
  if (buzzer.isPlaying()) {
    // If still playing, do nothing
  } else {
    // If not playing, you could trigger another note or action
  }
}

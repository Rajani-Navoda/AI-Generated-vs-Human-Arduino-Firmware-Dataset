#include "74HC138.h"

// define the pins connected to the 74HC138
const int A0 = 2;
const int A1 = 3;
const int A2 = 4;
const int G1 = 5;   // active low enable pin
const int G2A = 6;  // active high enable pin
const int G2B = 7;  // active high enable pin

// define the buttons for "previous" and "next" actions
const int prevButton = 8; 
const int nextButton = 9;

// store the current output state
int currentOutput = 0;

// create an instance of the 74HC138 class
HC138 decoder(A0, A1, A2, G1, G2A, G2B);

void setup()
{
  // initialize the serial monitor
  Serial.begin(9600);
  
  // initialize the 74HC138 decoder
  decoder.begin();

  // set button pins as inputs
  pinMode(prevButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);

  // set initial output
  decoder.select(currentOutput);
  
  Serial.println("74HC138 Previous/Next Button Demo");
}

void loop()
{
  // check if "next" button is pressed
  if (digitalRead(nextButton) == LOW)
  {
    currentOutput++;
    
    // wrap around if we exceed the maximum output
    if (currentOutput > 7) currentOutput = 0;

    // select the next output
    decoder.select(currentOutput);

    Serial.print("Selected output: ");
    Serial.println(currentOutput);
    
    // simple debounce
    delay(250);
  }

  // check if "previous" button is pressed
  if (digitalRead(prevButton) == LOW)
  {
    currentOutput--;
    
    // wrap around if we go below 0
    if (currentOutput < 0) currentOutput = 7;

    // select the previous output
    decoder.select(currentOutput);

    Serial.print("Selected output: ");
    Serial.println(currentOutput);

    // simple debounce
    delay(250);
  }
}
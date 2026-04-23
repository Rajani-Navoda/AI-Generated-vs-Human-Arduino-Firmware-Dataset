#include "74HC138.h"

// define the pins connected to the 74HC138
const int A0 = 2;
const int A1 = 3;
const int A2 = 4;
const int G1 = 5;  // active low enable pin
const int G2A = 6; // active high enable pin
const int G2B = 7; // active high enable pin

// create an instance of the 74HC138 class
HC138 decoder(A0, A1, A2, G1, G2A, G2B);

void setup()
{
  Serial.begin(9600);
  
  // initialize the decoder
  decoder.begin();

  Serial.println("74HC138 Decoder Demo");
}

void loop()
{
  // loop through all 8 outputs
  for (int i = 0; i < 8; i++)
  {
    // set the output
    decoder.select(i);
    
    // print the current selection
    Serial.print("Selected output: ");
    Serial.println(i);
    
    // delay for visibility
    delay(1000);
  }
}
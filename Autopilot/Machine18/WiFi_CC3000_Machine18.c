/* 
  This is a simple example of the aREST UI Library for Arduino (Mega/Due)
  using the CC3000 WiFi chip. See the README file for more details.

  Written in 2014 by Marco Schwartz under a GPL license. 
*/

// Import required libraries
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include <CC3000_MDNS.h>
#include <aREST.h>
#include <aREST_UI.h>
#include <avr/wdt.h>

// Define your CC3000 credentials
#define CC3000_IRQ   3  // Define the IRQ pin for CC3000
#define CC3000_VBAT  5  // Define the battery pin for CC3000
#define CC3000_CS    10 // Define the chip select pin for CC3000

// Create an instance of CC3000
Adafruit_CC3000 cc3000 = Adafruit_CC3000(CC3000_CS, CC3000_IRQ, CC3000_VBAT);

// Create an instance of aREST
aREST rest = aREST();
aREST_UI ui = aREST_UI(); // Create an instance of the aREST UI

// LED pin configuration
const int ledPin = 13; // Change this to your desired pin for the LED

// Function to be called when a command is received
void commandHandler(String command) {
  if (command == "LED_ON") {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    rest.respond("LED is ON");
  } else if (command == "LED_OFF") {
    digitalWrite(ledPin, LOW); // Turn off the LED
    rest.respond("LED is OFF");
  } else {
    rest.respond("Unknown command");
  }
}

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  
  // Initialize the LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Initialize the CC3000 WiFi chip
  if (!cc3000.begin()) {
    Serial.println(F("CC3000 failed to initialize!"));
    while (1);
  }
  
  // Connect to WiFi network
  Serial.print(F("Connecting to WiFi..."));
  while (!cc3000.connectToAP("YOUR_SSID", "YOUR_PASSWORD", CC3000_AP_SEC_WPA2)) {
    delay(1000);
    Serial.print(F("."));
  }
  
  Serial.println(F("Connected to WiFi"));
  
  // Initialize the aREST library
  rest.begin();
  ui.begin();

  // Set the command handler
  rest.setCommandHandler(commandHandler);
  
  // Set up the UI for the LED control
  ui.addDevice("LED", ledPin);
  
  Serial.println(F("aREST UI Example for Arduino Mega/Due with CC3000"));
}

void loop() {
  // Check for incoming commands
  rest.handleClient();
  ui.handleClient();
}

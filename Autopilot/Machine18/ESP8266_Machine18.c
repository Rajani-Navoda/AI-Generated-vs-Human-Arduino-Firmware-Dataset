#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";          // Your WiFi SSID
const char* password = "YOUR_PASSWORD";  // Your WiFi Password

// Create an instance of aREST
aREST rest = aREST();
aREST_UI ui = aREST_UI(); // Create an instance of the aREST UI

// LED pin configuration
const int ledPin = 2; // Change this to your desired pin for the LED (D2 on NodeMCU)

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
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize the aREST library
  rest.begin();
  ui.begin();

  // Set the command handler
  rest.setCommandHandler(commandHandler);
  
  // Set up the UI for the LED control
  ui.addDevice("LED", ledPin);
  
  Serial.println("aREST UI Example for ESP8266");
}

void loop() {
  // Check for incoming commands
  rest.handleClient();
  ui.handleClient();
}

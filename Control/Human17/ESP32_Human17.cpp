#include <WiFi.h>
#include <aREST.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Create an instance of aREST
aREST rest = aREST();

// Function to be called when a command is received
void commandHandler(String command) {
  if (command == "LED_ON") {
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the built-in LED
    rest.respond("LED is ON");
  } else if (command == "LED_OFF") {
    digitalWrite(LED_BUILTIN, LOW); // Turn off the built-in LED
    rest.respond("LED is OFF");
  } else {
    rest.respond("Unknown command");
  }
}

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  
  // Initialize the LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  
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
  rest.begin(WiFi);
  
  // Set the command handler
  rest.setCommandHandler(commandHandler);
  
  Serial.println("aREST ESP32 Example");
}

void loop() {
  // Check for incoming commands
  rest.handleClient();
}

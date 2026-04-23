#include <ESP8266WiFi.h>
#include <aREST.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// aREST Cloud API key (replace with your aREST API key)
const char* api_key = "YOUR_API_KEY";

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
  
  // Set your aREST API key
  rest.setApiKey(api_key);
  
  // Set the command handler
  rest.setCommandHandler(commandHandler);
  
  Serial.println("aREST Cloud and Local Example for ESP8266");
}

void loop() {
  // Check for incoming commands
  rest.handleClient();
}

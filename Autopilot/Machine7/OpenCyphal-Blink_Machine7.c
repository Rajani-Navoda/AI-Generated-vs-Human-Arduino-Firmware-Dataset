#include <Arduino.h>
#include <OpenCyphal.h>  // Include the OpenCyphal library

// Create a CAN interface instance
OpenCyphal::CAN can;

// Define the built-in LED pin
const int ledPin = LED_BUILTIN;

// Heartbeat message configuration
const uint32_t heartbeatInterval = 1000;  // 1 second
unsigned long previousMillis = 0;

// LED state variable
bool ledState = false;

// OpenCyphal Node ID
const uint8_t nodeId = 59;

// Setup function
void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the CAN interface
  can.begin();

  // Set the LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Notify that the OpenCyphal node has started
  Serial.println("OpenCyphal Node Started");
}

// Loop function
void loop() {
  // Check for incoming messages
  can.update();

  // Handle LED control message
  if (can.receive(1620, 1)) {
    OpenCyphal::BitMessage msg;
    can.read(msg);

    // Update the LED state based on the received message
    ledState = msg.value;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    Serial.print("LED turned ");
    Serial.println(ledState ? "ON" : "OFF");
  }

  // Send a heartbeat message periodically
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= heartbeatInterval) {
    previousMillis = currentMillis;

    // Send heartbeat message
    OpenCyphal::HeartbeatMessage heartbeat;
    heartbeat.node_id = nodeId;
    heartbeat.uptime = millis();
    
    can.send(heartbeat);
    Serial.println("Heartbeat sent");
  }
}

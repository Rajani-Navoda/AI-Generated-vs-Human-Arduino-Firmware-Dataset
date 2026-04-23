#include <Arduino.h>
#include <OpenCyphal.h>  // Include the OpenCyphal library

// Create a CAN interface instance
OpenCyphal::CAN can;

// Define the heartbeat message interval
const uint32_t heartbeatInterval = 1000;  // 1 second
unsigned long previousMillis = 0;

// OpenCyphal Node ID
const uint8_t nodeId = 59;

// Setup function
void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the CAN interface
  can.begin();

  // Notify that the OpenCyphal node has started
  Serial.println("OpenCyphal Node Started");
}

// Loop function
void loop() {
  // Send a heartbeat message periodically
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= heartbeatInterval) {
    previousMillis = currentMillis;

    // Create a heartbeat message
    OpenCyphal::HeartbeatMessage heartbeat;
    heartbeat.node_id = nodeId;
    heartbeat.uptime = millis();  // Uptime in milliseconds

    // Send the heartbeat message
    can.send(heartbeat);
    Serial.println("Heartbeat sent");
  }

  // Handle incoming CAN messages
  can.update();
}

#include <Arduino.h>
#include <OpenCyphal.h>  // Include the OpenCyphal library

// Create a CAN interface instance
OpenCyphal::CAN can;

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
  // Check for incoming messages
  can.update();

  // Receive a heartbeat message
  if (can.receive(1620, 1)) {  // Assuming ID 1620 for heartbeat messages
    OpenCyphal::HeartbeatMessage heartbeat;
    can.read(heartbeat);

    // Print received heartbeat message details
    Serial.print("Received Heartbeat from Node ID: ");
    Serial.println(heartbeat.node_id);
    Serial.print("Uptime: ");
    Serial.print(heartbeat.uptime);
    Serial.println(" ms");
  }

  // Other processing can go here
}

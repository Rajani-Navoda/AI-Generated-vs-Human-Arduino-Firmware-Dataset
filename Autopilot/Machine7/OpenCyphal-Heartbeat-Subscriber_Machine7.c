#include <Arduino.h>
#include <OpenCyphal.h>  // Include the OpenCyphal library

// Create a CAN interface instance
OpenCyphal::CAN can;

// Define the expected heartbeat message ID
const uint32_t HEARTBEAT_MSG_ID = 1620;  // Replace with the appropriate message ID for heartbeat messages

// Setup function
void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the CAN interface
  can.begin();

  // Notify that the OpenCyphal node has started
  Serial.println("OpenCyphal Node Started. Listening for heartbeat messages...");
}

// Loop function
void loop() {
  // Check for incoming messages
  can.update();

  // Check for a received heartbeat message
  if (can.receive(HEARTBEAT_MSG_ID, 1)) {  // ID and priority level
    OpenCyphal::HeartbeatMessage heartbeat;
    can.read(heartbeat);  // Read the heartbeat message

    // Print the received heartbeat message details
    Serial.print("Received Heartbeat from Node ID: ");
    Serial.println(heartbeat.node_id);
    Serial.print("Uptime: ");
    Serial.print(heartbeat.uptime);
    Serial.println(" ms");
  }

  // Additional processing can be done here, if necessary
}

#include <Arduino.h>
#include <OpenCyphal.h>  // Include the OpenCyphal library

// Create a CAN interface instance
OpenCyphal::CAN can;

// Define the service request and response message IDs
const uint32_t SERVICE_REQUEST_ID = 2000;   // Replace with your service request ID
const uint32_t SERVICE_RESPONSE_ID = 2001;  // Replace with your service response ID

// Define the OpenCyphal node ID
const uint8_t nodeId = 59;

// Setup function
void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the CAN interface
  can.begin();

  // Notify that the OpenCyphal node has started
  Serial.println("OpenCyphal Service Server Started. Ready to respond to service requests...");
}

// Loop function
void loop() {
  // Check for incoming messages
  can.update();

  // Check for service requests
  if (can.receive(SERVICE_REQUEST_ID, 1)) {
    // Define a service request message
    OpenCyphal::ServiceRequestMessage request;
    can.read(request);  // Read the service request

    // Simulate performance metric calculation
    int performanceValue = calculatePerformance();

    // Create a service response message
    OpenCyphal::ServiceResponseMessage response;
    response.node_id = nodeId;  // Include the node ID in the response
    response.performance_value = performanceValue;  // Populate the performance value

    // Send the service response
    can.send(response);
    Serial.print("Service request received from Node ID: ");
    Serial.println(request.node_id);
    Serial.print("Responding with performance value: ");
    Serial.println(performanceValue);
  }

  // Additional processing can be done here, if necessary
}

// Function to simulate performance metric calculation
int calculatePerformance() {
  // For demonstration purposes, return a random performance value
  return random(1, 100);  // Simulate a performance value between 1 and 100
}

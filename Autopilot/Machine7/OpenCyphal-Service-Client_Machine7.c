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
  Serial.println("OpenCyphal Node Started. Ready to request service performance...");
}

// Loop function
void loop() {
  // Check for incoming messages
  can.update();

  // Check for a service response
  if (can.receive(SERVICE_RESPONSE_ID, 1)) {
    // Define a service response message
    OpenCyphal::ServiceResponseMessage response;
    can.read(response);  // Read the service response

    // Print the received performance metrics
    Serial.print("Received Performance Metrics from Node ID: ");
    Serial.println(response.node_id);
    Serial.print("Performance Value: ");
    Serial.println(response.performance_value);  // Assuming there's a field for performance value
  }

  // Request service performance periodically
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 5000) {  // Request every 5 seconds
    previousMillis = currentMillis;

    // Create and send a service request
    OpenCyphal::ServiceRequestMessage request;
    request.node_id = nodeId;  // Specify the target node
    request.service_type = 1;   // Assuming a service type ID of 1 (replace as necessary)

    // Send the service request
    can.send(request);
    Serial.println("Service request sent for performance metrics.");
  }

  // Additional processing can be done here, if necessary
}

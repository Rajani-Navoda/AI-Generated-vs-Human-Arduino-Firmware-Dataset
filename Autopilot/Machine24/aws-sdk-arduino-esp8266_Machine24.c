#include <WiFi.h>
#include <AmazonIOTClient.h>
#include "ESPAWSImplementations.h"

// Define your WiFi credentials and AWS IoT details
const char* ssid = "YOUR_SSID";                  // Your WiFi SSID
const char* password = "YOUR_PASSWORD";          // Your WiFi Password
const char* awsEndpoint = "YOUR_AWS_ENDPOINT";   // AWS IoT Endpoint
const char* awsCert = "YOUR_CERTIFICATE";        // AWS IoT Certificate
const char* awsPrivateKey = "YOUR_PRIVATE_KEY";  // AWS IoT Private Key
const char* awsTopic = "your/topic";              // Topic to publish

// Create an instance of the Amazon IOT Client
AmazonIOTClient iotClient;

void setup() {
    Serial.begin(115200);
  
    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");

    // Initialize AWS IoT client
    iotClient.setAWSEndpoint(awsEndpoint);
    iotClient.setAWSCert(awsCert);
    iotClient.setAWSPrivateKey(awsPrivateKey);
    
    if (iotClient.connect()) {
        Serial.println("Connected to AWS IoT");
    } else {
        Serial.println("AWS IoT connection failed");
    }
}

void loop() {
    // Simulate temperature data
    float temperature = random(20, 30) + random(0, 100) / 100.0; // Random temperature between 20.00 and 30.99
    Serial.print("Temperature: ");
    Serial.println(temperature);

    // Publish temperature data to AWS IoT
    String payload = String("{\"temperature\":") + temperature + "}";
    if (iotClient.publish(awsTopic, payload)) {
        Serial.println("Data sent to AWS IoT: " + payload);
    } else {
        Serial.println("Failed to send data to AWS IoT");
    }

    // Wait for 5 seconds before sending the next reading
    delay(5000);
}

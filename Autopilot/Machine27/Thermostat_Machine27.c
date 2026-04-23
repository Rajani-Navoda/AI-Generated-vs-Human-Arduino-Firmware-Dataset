#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <AzureIoTHubMQTTClient.h>

// WiFi credentials
const char* ssid = "your_SSID";         // Replace with your WiFi SSID
const char* password = "your_PASSWORD";  // Replace with your WiFi password

// Azure IoT Hub settings
const char* iotHubName = "yourIoTHubName";     // Replace with your Azure IoT Hub name
const char* deviceId = "yourDeviceId";         // Replace with your device ID
const char* deviceKey = "yourDeviceKey";       // Replace with your device key
const char* mqttServer = "yourIoTHubHostName"; // Replace with your IoT Hub host name (e.g., <yourIoTHubName>.azure-devices.net)

// Create an instance of the Azure IoT Hub MQTT client
AzureIoTHubMQTTClient client;

void setup() {
    // Start Serial communication
    Serial.begin(115200);
    
    // Connect to WiFi
    connectToWiFi();

    // Initialize Azure IoT Hub client
    client.begin(mqttServer, deviceId, deviceKey, iotHubName);
}

void loop() {
    // Read temperature from a sensor (simulated here)
    float temperature = readTemperature();

    // Prepare the JSON payload
    String payload = String("{\"temperature\":") + temperature + "}";

    // Send temperature data to Azure IoT Hub
    if (client.sendEvent(payload)) {
        Serial.println("Temperature sent to Azure: " + payload);
    } else {
        Serial.println("Failed to send temperature data to Azure.");
    }

    // Wait before sending the next reading
    delay(10000); // Send data every 10 seconds
}

// Function to connect to WiFi
void connectToWiFi() {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected!");
}

// Function to read temperature from a sensor
float readTemperature() {
    // Simulate reading from a temperature sensor
    // Replace with actual sensor reading code
    return random(20, 30); // Random temperature between 20 and 30 degrees Celsius
}

// Libraries
#include <SPI.h>
#include "Ethernet.h"
#include <PubSubClient.h>
#include <aREST.h>

// Enter a MAC address for your controller below.
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40 };

// Clients
EthernetClient ethClient;
PubSubClient client(ethClient);

// Create aREST instance
aREST rest = aREST(client);

// Variables to be exposed to the API
int temperature;
int humidity;

// ID to identify the device on the cloud (should be 6 characters long)
char* device_id = "unique_device_id";

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Set callback
  client.setCallback(callback);

  // Init variables and expose them to REST API
  temperature = 24;
  humidity = 40;
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);

  // Give name & ID to the device
  rest.set_id(device_id);
  rest.set_name("ethernet");

  // Start the Ethernet connection and the server
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }

}

void loop() {

  // Connect to the cloud
  rest.handle(client);

}

// Handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  rest.handle_callback(client, topic, payload, length);

}
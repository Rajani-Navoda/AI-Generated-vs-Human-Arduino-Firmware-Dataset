#include <Wire.h>
#include <Arduino_APDS9950.h>

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the APDS-9950 sensor
  if (!APDS.begin()) {
    Serial.println("Error: APDS-9950 not found!");
    while (1);
  }

  // Notify that the sensor was initialized
  Serial.println("APDS-9950 initialized!");
}

void loop() {
  // Variables to store the sensor data
  uint16_t proximity;
  uint16_t ambientLight;
  uint16_t red, green, blue;

  // Read proximity and light levels
  proximity = APDS.readProximity();
  ambientLight = APDS.readAmbientLight();
  APDS.readColor(red, green, blue);

  // Print the proximity and light data to the Serial Monitor
  Serial.print("Proximity: ");
  Serial.println(proximity);
  Serial.print("Ambient Light: ");
  Serial.println(ambientLight);
  Serial.print("Red: ");
  Serial.println(red);
  Serial.print("Green: ");
  Serial.println(green);
  Serial.print("Blue: ");
  Serial.println(blue);

  // Wait 500ms before the next reading
  delay(500);
}

#include <Wire.h>
#include <Arduino_APDS9950.h>  // Include the APDS-9950 library

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Initialize the APDS-9950 sensor
  if (!APDS.begin()) {
    Serial.println("Error: APDS-9950 not detected!");
    while (1);
  }

  // Notify that the sensor has been successfully initialized
  Serial.println("APDS-9950 sensor initialized!");
}

void loop() {
  // Variables to store sensor readings
  uint16_t proximity;
  uint16_t ambientLight;
  uint16_t red, green, blue;

  // Read proximity value
  proximity = APDS.readProximity();

  // Read ambient light value
  ambientLight = APDS.readAmbientLight();

  // Read RGB color values
  APDS.readColor(red, green, blue);

  // Print proximity value
  Serial.print("Proximity: ");
  Serial.println(proximity);

  // Print ambient light value
  Serial.print("Ambient Light: ");
  Serial.println(ambientLight);

  // Print RGB color values
  Serial.print("Red: ");
  Serial.println(red);
  Serial.print("Green: ");
  Serial.println(green);
  Serial.print("Blue: ");
  Serial.println(blue);

  // Wait for 500 milliseconds before next reading
  delay(500);
}
